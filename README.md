# PS1 Suite Installer

This project is a C program designed to automate the installation and configuration of a PowerShell suite on Windows. It downloads and installs a specific version of PowerShell, sets up necessary configurations, and installs additional tools and settings.

## Features

- Downloads and installs a specified version of PowerShell.
- Configures PowerShell profile and settings.
- Downloads and installs additional PowerShell modules and settings.
- Configures Windows Terminal settings.
- Installs custom fonts for the terminal.

## Prerequisites

- Windows 11 (the installer is not compatible with Windows 10 or earlier versions).
- Internet connection to download necessary files.
- Administrator privileges to install software and modify system settings.

## Installation

1. Clone the repository or download the source code.
2. Open a terminal and navigate to the directory containing the source code.
3. Compile the source code using a C compiler (e.g., GCC).
4. Execute the .exe file created.
```sh
gcc -o ps1_suite_installer ps1_suite_installer.c
```
