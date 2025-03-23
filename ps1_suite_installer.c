/**
 * - Author: Solorzano, Juan Jose.
 * - Date: 01/01/2024
 * - Description:
 *      This project is a C program designed to automate the installation and configuration of a PowerShell
 *      suite on Windows. It downloads and installs a specific version of PowerShell, sets up necessary 
 *      configurations, and installs additional tools and settings.
 */
// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h> // folder exists
#include <windows.h> // sleep and time.h file
#include <time.h>
#include <string.h> // args manager.
#define SUITE_INSTALLATION "%HOMEPATH%\\.powershellsuite"
#define PS1_PROFILE_FILE "C:/LegacyApp/powershell/Microsoft.PowerShell_profile.ps1"
#define PS1_COMMAND "start %s"
#define TERMINAL_SETTINGS_PC "%LOCALAPPDATA%\\Packages\\Microsoft.WindowsTerminal_8wekyb3d8bbwe\\LocalState\\settings.json"
#define TERMINAL_SETTINGS "C:\\LegacyApp\\powershell\\PowerShell-master\\terminal_settings.json"
#define URL_API "https://github.com/PowerShell/PowerShell/releases/download/v%s/PowerShell-%s-win-x64.zip"
#define PWSH_SITE "https://github.com/JuanJoseSoloraznoCarrillo/PowerShell/archive/refs/heads/master.zip"
#define PS1_FOLDER_INSTALLATION "C:\\LegacyApp\\powershell"
const char *version = "7.4.7";
/**
 * help_panel - Display the help panel. 
 */
void help_panel(){
    printf("[?] Usage:\n");
    printf("\t\tps1Environment.exe [-v | -version | version | v] <version. eg: 7.4.7>\n");
}
/**
 * init_print - Display the initial print of the program.
 * @param version: const char* - The version of PowerShell.
 */
void init_print(const char *version){
    printf("***********************************************************************************************\n");
    printf("**                               PS1 Suite Configuration\n");
    printf("**                              PowerShell Version %s\n",version);
    printf("***********************************************************************************************\n");
}
/**
 * url_exists - Check if the given URL exists.
 * @param link: const char* - The URL to check.
 * @return int - 1 if the URL exists, 0 otherwise.
 */
int url_exists(const char *link){
    char command[512];
    char *cmd_request = "powershell -C \"try{$req=Invoke-WebRequest -Uri '%s' -UseBasicParsing -Method Head; exit 0} catch{exit 1}\"";
    sprintf(command,cmd_request,link);
    return system(command); // output 1 when the link requested does not exists.
}
/**
 * folder_exists - Check if the given folder exists.
 * @param path: char* - The path to check.
 * @return int - 1 if the folder exists, 0 otherwise.
 */
int folder_exists(char *path){
    struct stat st;
    int exists = stat(path,&st) == 0 && S_ISDIR(st.st_mode);
    return exists; // 1 when folder exists
}
/**
 * clear_buffer - Clear the buffer.
 * @param buffer: char* - The buffer to clear.
 */
void clear_buffer(char *buffer){
    buffer[0] = '\0';
}  
/**
 * unzip - Unzip the given file.
 * @param target: char* - The target file to unzip.
 * @param destination: char* - The destination to unzip the file.
 * @return int - 1 if the file was successfully unzipped, 0 otherwise.
 */
int unzip(char target[], char destination[]){
    printf("[+] Extracting file: %s ...\n",target);
    char cmd_buf[MAX_PATH];
    sprintf(cmd_buf,"C:/Windows/SysWOW64/tar.exe -xf \"%s\" -C \"%s\"2>NUL",target,destination);
    system(cmd_buf);
    printf("[+] Unzipped file: %s\n",destination);
}
/**
 * move_file - Move the given file to the destination.
 * @param target: char* - The target file to move.
 * @param destination: char* - The destination to move the file.
 * @return int - 1 if the file was successfully moved, 0 otherwise.
 */
int move_file(char target[], char destination[]){
    printf("[+] Moving file %s to %s\n",target,destination);
    char cmd_buf[MAX_PATH];
    sprintf(cmd_buf,"move %s %s",target,destination);
    system(cmd_buf);
    Sleep(2000);
    return 1;
}
/**
 * download_pwsh - Download the PowerShell zip file.
 * @param buffer: char* - The buffer to store the command.
 * @param url: char* - The URL to download the file from.
 * @return int - 1 if the download was successful, 0 otherwise.
 */
int download_pwsh(char *buffer,char *url){
    printf("[+] Downloading PowerShell-7.4.7-win-x64.zip ...\n");
    sprintf(buffer,PS1_COMMAND,url);
    system(buffer);
    clear_buffer(buffer);
    Sleep(25000); //waiting for downloaded file.
    return 1;
}
/**
 * create_folder - Create the installation folder.
 * @param buffer: char* - The buffer to store the command.
 * @return int - 1 if the folder was created, 0 otherwise.
 */
int create_folder(char *buffer){
    printf("[+] Creating installation folder: '%s'\n",PS1_FOLDER_INSTALLATION);
    sprintf(buffer,"mkdir %s",PS1_FOLDER_INSTALLATION);
    system(buffer);
    clear_buffer(buffer);
    return 1;
}
/**
 * install_pwsh - Install the PowerShell zip file.
 * @return int - 1 if the installation was successful, 0 otherwise.
 */
int install_pwsh(){
    move_file("%USERPROFILE%\\Downloads\\PowerShell-7.4.7-win-x64.zip","C:\\LegacyApp\\powershell\\");
    unzip("C:/LegacyApp/powershell/PowerShell-7.4.7-win-x64.zip","C:/LegacyApp/powershell/");
    printf("[*] PowerShell installation -> Done.\n");
    printf("===============================================================================================\n");
    return 1;
}
/**
 * download_pwsh_suite - Download the PowerShell suite.
 * @param buffer: char* - The buffer to store the command.
 * @param suitePathInstall: char* - The path to install the suite.
 */
void download_pwsh_suite(char *buffer,char *suitePathInstall){
    printf("[+] Downloading ps1 suite ...\n");
    if(folder_exists(suitePathInstall)==1){
        system("rmdir /s /q %USERPROFILE%\\.powershellsuite");
    }
    system("mkdir %USERPROFILE%\\.powershellsuite");
    sprintf(buffer,PS1_COMMAND,PWSH_SITE);
    system(buffer);
    clear_buffer(buffer);
    Sleep(5000);
    move_file("%USERPROFILE%\\Downloads\\PowerShell-master.zip",suitePathInstall);
    unzip("%USERPROFILE%/.powershellsuite/PowerShell-master.zip",suitePathInstall);
    system("rm %USERPROFILE%/.powershellsuite/PowerShell-master.zip");
}
/**
 * create_ps1_file - Create the PowerShell profile file.
 * @return int - 1 if the file was created, 0 otherwise.
 */
int create_ps1_file(){
    printf("[+] Creating ps1 file ...\n");
    FILE *file;
    file = fopen(PS1_PROFILE_FILE,"w");
    if(file==NULL){
        printf("[!] Error: Unable to create file.\n");
        return 1;
    }
    fprintf(file,"$profile_prompt = \"$home\\.powershellsuite\\PowerShell-master\\Profile.ps1\"\nImport-Module -Name $profile_prompt\n");
    fclose(file);
    return 0;
}
/**
 * main - Main function.
 * @param argc: int - The number of arguments.
 * @param argv: char* - The arguments.
 * @return int - 0 if the program ends successfully, 1 otherwise.
 */
int main(int argc,char *argv[]){
    char *arg_version = NULL;
    OSVERSIONINFO os_info;
    os_info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&os_info);//Get the windows version.
    if (os_info.dwMajorVersion == 10 && os_info.dwBuildNumber <= 22000){
        // Windows 11 is required. 
        printf("___________________________________________________\n");
        printf("  [!]    WINDOWS VERSION NOT COMPATIBLE!\n");
        printf("  [?]   THIS WORKS ONLY WITH WINDOWS 11 OS\n");
        printf("---------------------------------------------------\n");
        printf("Press any key ....\n");
        getchar();
        return 1;
    }
    if(argc>1){
        // Check the arguments given by the user.
        if(strcmp(argv[1],"-h")==0||strcmp(argv[1],"-help")==0||strcmp(argv[1],"help")==0||strcmp(argv[1],"-help")==0){
            help_panel();
            return 0;
        if(strcmp(argv[1],"version")==0||strcmp(argv[1],"-version")==0||strcmp(argv[1],"v")==0||strcmp(argv[1],"-v")==0){
            version = argv[2];
        }else{
        // print the help panel as a default.
            printf("Unknow argument: %s\n",argv[1]);
            help_panel();
        }
    }
    char profile[MAX_PATH];
    char fullPathProfile[MAX_PATH];
    GetEnvironmentVariable("USERPROFILE",profile,MAX_PATH);
    snprintf(fullPathProfile,MAX_PATH,"%s\\.powershellsuite",profile);
    char url_api[MAX_PATH];
    sprintf(url_api,URL_API,version,version);
    if(url_exists(url_api)==1){
        printf("[!] The version %s given does not exits!!!\n\n",version);
        return 1;
    }
    init_print(version);
    char cmd_buffer[MAX_PATH]; //Command string buffering.
    if(!download_pwsh(cmd_buffer,url_api)){
        // was not possible to download the 
        printf("[!] Error: while download the PowerShell-7.4.7-win-x64.zip");
        return 1;
    }
    if(!folder_exists(PS1_FOLDER_INSTALLATION)){
       create_folder(cmd_buffer);
    }else{
        printf("[*] PowerShell installation found, removing folder ...\n");
        sprintf(cmd_buffer,"rmdir /s /q %s",PS1_FOLDER_INSTALLATION);
        system(cmd_buffer);
        clear_buffer(cmd_buffer);
        create_folder(cmd_buffer);
    }
    if(!install_pwsh()){
        return 1;
    }
    download_pwsh_suite(cmd_buffer,fullPathProfile);
    if(create_ps1_file()==1){
        return 1;
    }
    clear_buffer(cmd_buffer);
    printf("[+] Moving Terminal-Icons module ...\n");
    clear_buffer(cmd_buffer);
    snprintf(cmd_buffer,MAX_PATH,"%s\\PowerShell-master\\Modules\\Terminal-Icons",fullPathProfile);
    move_file(cmd_buffer,"C:\\LegacyApp\\powershell\\Modules\\");
    printf("[+] Moving Terminal settings ...\n");
    clear_buffer(cmd_buffer);
    snprintf(cmd_buffer,MAX_PATH,"%s\\PowerShell-master\\terminal_settings.json",fullPathProfile);
    move_file(cmd_buffer,TERMINAL_SETTINGS_PC);
    printf("[+] Lilex Font Installation ...\n");
    system("start https://github.com/ryanoasis/nerd-fonts/releases/download/v3.3.0/Lilex.zip");
    system("mkdir \"%USERPROFILE%/Downloads/fonts\"");
    Sleep(5000);
    system("C:/Windows/SysWOW64/tar.exe -xf \"%USERPROFILE%/Downloads/Lilex.zip\" -C \"%USERPROFILE%/Downloads/fonts\"2>NUL");
    system("start %USERPROFILE%/Downloads/fonts/LilexNerdFontPropo-Regular.ttf");
    system("rm %USERPROFILE%/Downloads/Lilex.zip");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("+++                              INSTALLATION SUCCESS\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("Press any key to exit...\n");
    getchar();
    return 0;
}