#include <stdio.h>
#include <windows.h>
#include "lib/headers/fileio.h"  // Adjust path if needed
#include "lib/headers/helpers.h"
// Macros and constants
#define POWERSHELL_INSTALLATION_PATH "C:\\LegacyApp\\powershell"
#define POWERSHELL_LINK "https://api.github.com/repos/PowerShell/PowerShell/releases/latest"
#define PWSHSUITE_LINK "https://api.github.com/repos/JuanJoseSolorzano/Powershell_Suite/releases/latest"

int main(int argc, char *argv[]) {
    system("cls");
    repChar("=", 70);
    printf("    Welcome to the PowerShell Suite Installer!\n");
    repChar("=", 70);
    if(folderExists(POWERSHELL_INSTALLATION_PATH) == 1) {
        printf("_> PowerShell Suite already installed at %s\n", POWERSHELL_INSTALLATION_PATH);
        printf("_> Overwriting installation...\n");
        system("rmdir /s /q powershell");
        system("rmdir /s /q Powershell_Suite");
        system("del C:\\Users\\juanj\\AppData\\Local\\Packages\\Microsoft.WindowsTerminal_8wekyb3d8bbwe\\LocalState\\settings.json");
    }
    if(getLatestRelease(POWERSHELL_LINK,"C:\\LegacyApp","win-x64.zip","powershell.zip","powershell") == 1)
        printf("_> PowerShell Suite installation complete.\n");
    repChar("=", 70);
    if(getLatestRelease(PWSHSUITE_LINK,"C:\\LegacyApp",".zip","pwshsuite.zip",NULL) == 1) {
        printf("_> PowerShell Suite downloaded successfully.\n");
    } else {
        printf("_> Failed to download PowerShell Suite.\n");
    }
    repChar("-", 70);
    if(createPwshProfile()){
        printf("_> PowerShell profile created successfully.\n");
    } else {
        printf("_> Failed to create PowerShell profile.\n");
    }
    repChar("-", 70);
    if(moveIconsFolder() == 1){
        printf("_> Icons folder moved successfully.\n");
    } else {
        printf("_> Failed to move icons folder.\n");
    }
    repChar("-", 70);
    if(installLilexFont()){
        printf("_> Lilex font installed successfully.\n");
    } else {
        printf("_> Failed to install Lilex font.\n");
    }
    repChar("-", 70);
    if(setTerminalSettings() == 1) {
        printf("_> Terminal settings configured successfully.\n");
    } else {
        printf("_> Failed to configure terminal settings.\n");
    }
    repChar("+",70);
    printf(" [+] POWERSHELL INSTALLED SUCCESSFULY\n");
    repChar("=",70);
    system("pause");
    system("wt");
    return 0;
}
