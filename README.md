C++ System Utility Tool
# System Utility Tool

A command-line system utility tool built in C++ for Windows, offering features such as system monitoring (CPU and memory usage), process listing, file management (search, copy, delete files), and directory listing. This tool is designed to be user-friendly, with both interactive and command-line modes for ease of use.

## Features

### System Monitoring:
- Display CPU usage.
- Display memory usage (total, used, available).

### Process Management:
- List all active processes along with their PIDs and names.

### File Management:
- Search for files in a specified directory by pattern.
- Copy files from one location to another.
- Delete files with a user confirmation prompt.

### Directory Listing:
- List the contents of a directory, including file size, type, and last modification date.

### Interactive Mode:
- Provides a menu-driven interface for beginners, making it easy to use without needing command-line arguments.

## Getting Started

### Prerequisites
- **Compiler:** This project requires `g++` from MinGW or any C++ compiler with Windows API support.
- **Windows:** This tool uses Windows-specific functions, so it is only compatible with Windows OS.

### Installation

#### Clone the Repository:
```bash
git clone https://github.com/yourusername/system-utility-tool.git
cd system-utility-tool
```

#### Build the Project:
Open a Command Prompt in the project directory and use the following command to compile the code:
```cmd
g++ src\main.cpp src\sys_util.cpp -o sys_util.exe -Iinclude -lpsapi
```
- `-Iinclude` specifies the path to the header files.
- `-lpsapi` links the psapi library, needed for process management functions.

#### Run the Executable:

For interactive mode:
```cmd
sys_util.exe
```
For command-line mode, follow the usage examples below.

## Usage

The tool can be used in two modes:

### Interactive Mode:
Run without arguments to enter an interactive menu.
```cmd
sys_util.exe
```

### Command-Line Mode:
Run with specific commands and options.

#### Command-Line Options

**Monitor CPU Usage:**
```cmd
sys_util.exe monitor-cpu
```

**Monitor Memory Usage:**
```cmd
sys_util.exe monitor-mem
```

**List Active Processes:**
```cmd
sys_util.exe list-processes
```

**Search for Files:**
```cmd
sys_util.exe search "C:\path\to\directory" "*.txt"
```

**Copy a File:**
```cmd
sys_util.exe copy "source.txt" "destination.txt"
```

**Delete a File:**
```cmd
sys_util.exe delete "file.txt"
```

**List Directory Contents:**
```cmd
sys_util.exe list-dir "C:\path\to\directory"
```

## Example Output

Here are some example outputs from running various commands:

**Example: Monitor CPU Usage**
```plaintext
CPU Usage: 15.27%
```

**Example: List Active Processes**
```plaintext
Active Processes:
    PID: 1234 - notepad.exe
    PID: 5678 - explorer.exe
```

**Example: Search for Files**
```plaintext
Files matching pattern '*.txt' in directory 'C:\example':
    example1.txt
    notes.txt
```

## Error Handling
- **Invalid Paths:** Provides clear error messages if a specified path or file is not found.
- **Confirmation Prompts:** Prompts before deleting files to avoid accidental deletions.
- **User Guidance:** Shows a help message with usage instructions if an invalid command is entered.

## Contributing

Contributions are welcome! If you’d like to contribute to this project, please follow these steps:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Commit your changes (`git commit -m 'Add new feature'`).
4. Push to the branch (`git push origin feature-branch`).
5. Open a Pull Request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.