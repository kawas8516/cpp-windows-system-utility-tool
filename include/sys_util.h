#ifndef SYS_UTIL_H
#define SYS_UTIL_H

#include <string>
#include <windows.h>  // For Windows-specific file handling

using namespace std;

// System monitoring functions
void showCPUUsage();
void showMemoryUsage();
void listProcesses();

// File management functions
void searchFiles(const string &directory, const string &filePattern);
bool copyFile(const string &source, const string &destination);
bool deleteFile(const string &filepath);
void listDirectory(const string &directory);

#endif // SYS_UTIL_H
