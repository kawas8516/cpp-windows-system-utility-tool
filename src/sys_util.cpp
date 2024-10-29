#include "sys_util.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <psapi.h>
#include <windows.h>

using namespace std;

void showCPUUsage() {
    FILETIME idleTime, kernelTime, userTime;

    if (GetSystemTimes(&idleTime, &kernelTime, &userTime)) {
        static ULONGLONG lastIdleTime = 0, lastKernelTime = 0, lastUserTime = 0;

        ULONGLONG currIdleTime = ((ULONGLONG)idleTime.dwHighDateTime << 32) | idleTime.dwLowDateTime;
        ULONGLONG currKernelTime = ((ULONGLONG)kernelTime.dwHighDateTime << 32) | kernelTime.dwLowDateTime;
        ULONGLONG currUserTime = ((ULONGLONG)userTime.dwHighDateTime << 32) | userTime.dwLowDateTime;

        ULONGLONG idleDiff = currIdleTime - lastIdleTime;
        ULONGLONG kernelDiff = currKernelTime - lastKernelTime;
        ULONGLONG userDiff = currUserTime - lastUserTime;

        lastIdleTime = currIdleTime;
        lastKernelTime = currKernelTime;
        lastUserTime = currUserTime;

        ULONGLONG total = kernelDiff + userDiff;
        double cpuUsage = (total - idleDiff) * 100.0 / total;

        cout << "CPU Usage: " << fixed << setprecision(2) << cpuUsage << "%" << endl;
    } else {
        cerr << "Error: Unable to retrieve CPU usage. Please ensure the system allows access." << endl;
    }
}

void showMemoryUsage() {
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(memInfo);

    if (GlobalMemoryStatusEx(&memInfo)) {
        DWORDLONG totalMemory = memInfo.ullTotalPhys / (1024 * 1024);
        DWORDLONG usedMemory = (memInfo.ullTotalPhys - memInfo.ullAvailPhys) / (1024 * 1024);

        cout << "Total Memory: " << totalMemory << " MB" << endl;
        cout << "Used Memory: " << usedMemory << " MB" << endl;
        cout << "Available Memory: " << totalMemory - usedMemory << " MB" << endl;
    } else {
        cerr << "Error: Unable to retrieve memory information." << endl;
    }
}

void listProcesses() {
    DWORD processes[1024], bytesNeeded, numProcesses;
    if (!EnumProcesses(processes, sizeof(processes), &bytesNeeded)) {
        cerr << "Error: Unable to list processes." << endl;
        return;
    }

    numProcesses = bytesNeeded / sizeof(DWORD);
    cout << "Active Processes:" << endl;

    for (unsigned int i = 0; i < numProcesses; i++) {
        if (processes[i] != 0) {
            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processes[i]);
            if (hProcess) {
                TCHAR processName[MAX_PATH] = TEXT("<unknown>");
                HMODULE hMod;
                DWORD cbNeeded;

                if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
                    GetModuleBaseName(hProcess, hMod, processName, sizeof(processName) / sizeof(TCHAR));
                }

                wcout << L"  PID: " << processes[i] << L" - " << processName << endl;
                CloseHandle(hProcess);
            } else {
                cerr << "Warning: Unable to open process with PID " << processes[i] << "." << endl;
            }
        }
    }
}

void searchFiles(const string &directory, const string &filePattern) {
    wstring searchPath = wstring(directory.begin(), directory.end()) + L"\\" + wstring(filePattern.begin(), filePattern.end());
    WIN32_FIND_DATAW findFileData;
    HANDLE hFind = FindFirstFileW(searchPath.c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        cerr << "No files found matching the pattern in the specified directory." << endl;
        return;
    }

    cout << "Files matching pattern '" << filePattern << "' in directory '" << directory << "':" << endl;
    do {
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            wcout << L"  " << findFileData.cFileName << endl;
        }
    } while (FindNextFileW(hFind, &findFileData) != 0);

    FindClose(hFind);
}

bool copyFile(const string &source, const string &destination) {
    wstring wSource(source.begin(), source.end());
    wstring wDestination(destination.begin(), destination.end());
    if (CopyFileW(wSource.c_str(), wDestination.c_str(), FALSE)) {
        cout << "File copied successfully from " << source << " to " << destination << "." << endl;
        return true;
    } else {
        cerr << "Error: Could not copy file. Please check that both paths are correct." << endl;
        return false;
    }
}

bool deleteFile(const string &filepath) {
    wstring wFilepath(filepath.begin(), filepath.end());
    cout << "Are you sure you want to delete " << filepath << "? (y/n): ";
    char confirm;
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        if (DeleteFileW(wFilepath.c_str())) {
            cout << "File deleted successfully: " << filepath << endl;
            return true;
        } else {
            cerr << "Error: Could not delete file. Please check that the file exists and try again." << endl;
            return false;
        }
    } else {
        cout << "File deletion canceled by user." << endl;
        return false;
    }
}

void listDirectory(const string &directory) {
    wstring searchPath = wstring(directory.begin(), directory.end()) + L"\\*";
    WIN32_FIND_DATAW findFileData;
    HANDLE hFind = FindFirstFileW(searchPath.c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        cerr << "Error: Could not open directory. Please check the directory path and try again." << endl;
        return;
    }

    cout << "Contents of directory '" << directory << "':" << endl;
    do {
        wstring wsFileName = findFileData.cFileName;
        string fileName(wsFileName.begin(), wsFileName.end());
        if (fileName == "." || fileName == "..") continue;

        bool isDirectory = (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
        SYSTEMTIME st;
        FileTimeToSystemTime(&findFileData.ftLastWriteTime, &st);

        if (isDirectory) {
            cout << "[DIR]  ";
        } else {
            LARGE_INTEGER fileSize;
            fileSize.LowPart = findFileData.nFileSizeLow;
            fileSize.HighPart = findFileData.nFileSizeHigh;
            cout << "[FILE] ";
            cout << setw(10) << fileSize.QuadPart << " bytes  ";
        }

        cout << fileName << "  Last modified: " << st.wDay << "/" << st.wMonth << "/" << st.wYear << endl;
    } while (FindNextFileW(hFind, &findFileData) != 0);

    FindClose(hFind);
}
