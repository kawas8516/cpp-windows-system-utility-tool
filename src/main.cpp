#include "sys_util.h"
#include <iostream>
#include <string>

using namespace std;

void printHelp() {
    cout << "\nUsage: sys_util [command] [options]\n"
         << "Commands:\n"
         << "  monitor-cpu             Display CPU usage\n"
         << "  monitor-mem             Display memory usage\n"
         << "  list-processes          Display active processes\n"
         << "  search <dir> <pattern>  Search for files in directory\n"
         << "  copy <src> <dest>       Copy file from source to destination\n"
         << "  delete <file>           Delete specified file\n"
         << "  list-dir <dir>          List contents of specified directory\n"
         << "If no arguments are provided, the program will start in interactive mode.\n";
}

void showMenu() {
    cout << "\nSystem Utility Tool - Interactive Mode\n";
    cout << "Please select an option:\n";
    cout << "1. Monitor CPU Usage\n";
    cout << "2. Monitor Memory Usage\n";
    cout << "3. List Active Processes\n";
    cout << "4. Search for Files\n";
    cout << "5. Copy a File\n";
    cout << "6. Delete a File\n";
    cout << "7. List Directory Contents\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

void interactiveMode() {
    int choice;
    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                showCPUUsage();
                break;
            case 2:
                showMemoryUsage();
                break;
            case 3:
                listProcesses();
                break;
            case 4: {
                string directory, pattern;
                cout << "Enter directory path: ";
                cin >> directory;
                cout << "Enter file pattern (e.g., *.txt): ";
                cin >> pattern;
                searchFiles(directory, pattern);
                break;
            }
            case 5: {
                string src, dest;
                cout << "Enter source file path: ";
                cin >> src;
                cout << "Enter destination file path: ";
                cin >> dest;
                copyFile(src, dest);
                break;
            }
            case 6: {
                string filepath;
                cout << "Enter file path to delete: ";
                cin >> filepath;
                deleteFile(filepath);
                break;
            }
            case 7: {
                string directory;
                cout << "Enter directory path: ";
                cin >> directory;
                listDirectory(directory);
                break;
            }
            case 0:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please select a valid option.\n";
        }
    } while (choice != 0);
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        // No arguments provided, so start interactive mode
        interactiveMode();
    } else {
        // Command-line mode
        string command = argv[1];

        if (command == "monitor-cpu") {
            showCPUUsage();
        } else if (command == "monitor-mem") {
            showMemoryUsage();
        } else if (command == "list-processes") {
            listProcesses();
        } else if (command == "search" && argc == 4) {
            string directory = argv[2];
            string pattern = argv[3];
            searchFiles(directory, pattern);
        } else if (command == "copy" && argc == 4) {
            string src = argv[2];
            string dest = argv[3];
            copyFile(src, dest);
        } else if (command == "delete" && argc == 3) {
            string filepath = argv[2];
            deleteFile(filepath);
        } else if (command == "list-dir" && argc == 3) {
            string directory = argv[2];
            listDirectory(directory);
        } else {
            cout << "Invalid command or arguments.\n";
            printHelp();
        }
    }

    return 0;
}
