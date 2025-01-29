/**
 * Author: Solorzano, Juan Jose.
 * Data: 01/01/2024
 * Information: ...
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h> // folder exists
#include <windows.h> // sleep and time.h file
#include <time.h>
#include <string.h> // args manager.
#define PS1_PROFILE_FILE "C:/LegacyApp/powershell/Microsoft.PowerShell_profile.ps1"
#define PS1_COMMAND "powershell -C start-process %s"
#define TERMINAL_SETTINGS "%LOCALAPPDATA%\\Packages\\Microsoft.WindowsTerminal_8wekyb3d8bbwe\\LocalState\\settings.json"
#define OWN_TERMINAL "C:\\LegacyApp\\powershell\\PowerShell-master\\terminal_settings.json"
#define URL_API "https://github.com/PowerShell/PowerShell/releases/download/v%s/PowerShell-%s-win-x64.zip"
#define PWSH_SITE "https://github.com/JuanJoseSoloraznoCarrillo/PowerShell/archive/refs/heads/master.zip"
#define FOLDER_INST "C:\\LegacyApp\\powershell"
const char *version = "7.4.7";

/**
 * 
 */
void help_panel(){
    printf("[?] Usage:\n");
    printf("\t\tps1Environment.exe [-v | -version | version | v] <version. eg: 7.4.7>\n");
}
void init_print(const char *version){
    printf("***********************************************************************************************\n");
    printf("**                               PS1 Suite Configuration\n");
    printf("**                              PowerShell Version %s\n",version);
    printf("***********************************************************************************************\n");

}
int url_exists(const char *link){
    char command[512];
    char *cmd_request = "powershell -C \"try{$req=Invoke-WebRequest -Uri '%s' -UseBasicParsing -Method Head; exit 0} catch{exit 1}\"";
    sprintf(command,cmd_request,link);
    return system(command); // output 1 when the link requested does not exists.
}
int folder_exists(char *path){
    struct stat st;
    int exists = stat(path,&st) == 0 && S_ISDIR(st.st_mode);
    return exists;
}
void clear_buffer(char *buffer){
    buffer[0] = '\0';
}
int unzip(char target[],char destination[]){
    printf("[+] Extracting file: %s ...\n",target);
    char cmd_buf[MAX_PATH];
    sprintf(cmd_buf,"tar -xf \"%s\" -C \"%s\"",target,destination);
    system(cmd_buf);
    printf("[+] Unziped file: %s\n",destination);
}
int move_file(char target[],char destination[]){
    printf("[+] Moving file %s to %s\n",target,destination);
    char cmd_buf[MAX_PATH];
    sprintf(cmd_buf,"move %s %s",target,destination);
    system(cmd_buf);
    Sleep(2000);
    return 1;
}
int download_pwsh(char *buffer,char *url){
    printf("[+] Downloading PowerShell-7.4.7-win-x64.zip ...\n");
    sprintf(buffer,PS1_COMMAND,url);
    system(buffer);
    clear_buffer(buffer);
    Sleep(25000); //waiting for downloaded file.
    return 1;
}
int create_folder(char *buffer){
    printf("[+] Creating installatioin folder: '%s'\n",FOLDER_INST);
    sprintf(buffer,"mkdir %s",FOLDER_INST);
    system(buffer);
    clear_buffer(buffer);
    return 1;
}
int install_pwsh(){
    move_file("%USERPROFILE%\\Downloads\\PowerShell-7.4.7-win-x64.zip","C:\\LegacyApp\\powershell\\");
    unzip("C:/LegacyApp/powershell/PowerShell-7.4.7-win-x64.zip","C:/LegacyApp/powershell/");
    printf("[*] Powershell installation -> Done.\n");
    printf("===============================================================================================\n");
    return 1;
}
int download_pwsh_suite(char *buffer){
    printf("[+] Downloading ps1 suite ...\n");
    sprintf(buffer,PS1_COMMAND,PWSH_SITE);
    system(buffer);
    clear_buffer(buffer);
    Sleep(5000);
    move_file("%USERPROFILE%\\Downloads\\PowerShell-master.zip","C:\\LegacyApp\\powershell\\");
    unzip("C:/LegacyApp/powershell/PowerShell-master.zip","C:/LegacyApp/powershell/");

}
int create_ps1_file(){
    printf("[+] Creating ps1 file ...\n");
    FILE *file;
    file = fopen(PS1_PROFILE_FILE,"w");
    if(file==NULL){
        printf("[!] Error: Unable to create file.\n");
        return 1;
    }
    fprintf(file,"$profile_prompt = \"C:\\LegacyApp\\powershell\\PowerShell-master\\Profile.ps1\"\nImport-Module -Name $profile_prompt\n");
    fclose(file);
    return 0;
}

/**
 * Main
 */
int main(int argc,char *argv[]){
    char *arg_version = NULL;
    OSVERSIONINFO os_info;
    os_info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&os_info);
    if (os_info.dwMajorVersion == 10 && os_info.dwBuildNumber >= 22000){
        printf("___________________________________________________");
        printf("  [!]    WINDOWS VERSION NOT COMPATIBLE!");
        printf("  [?]   THIS WORKS ONLY WITH WINDOWS 11 OS");
        printf("---------------------------------------------------");
        return 1;
    }
    if(argc>1){
        if(strcmp(argv[1],"version")==0||strcmp(argv[1],"-version")==0||strcmp(argv[1],"v")==0||strcmp(argv[1],"-v")==0){
            version = argv[2];
        }else{
            printf("Unknow argument: %s\n",argv[1]);
            help_panel();
        }
    }
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
    if(!folder_exists(FOLDER_INST)){
       create_folder(cmd_buffer);
    }else{
        printf("[*] Powershell installation found, removing folder ...\n");
        sprintf(cmd_buffer,"rmdir /s /q %s",FOLDER_INST);
        system(cmd_buffer);
        clear_buffer(cmd_buffer);
        create_folder(cmd_buffer);
    }
    if(!install_pwsh()){
        return 1;
    }
    download_pwsh_suite(cmd_buffer);
    if(create_ps1_file()==1){
        return 1;
    }
    printf("[+] Moving Terminal-Icons module ...\n");
    rename("C:\\LegacyApp\\powershell\\PowerShell-master\\Modules\\Terminal-Icons","C:\\LegacyApp\\powershell\\Modules\\Terminal-Icons");
    printf("[+] Moving Terminal settings ...\n");
    move_file(OWN_TERMINAL,TERMINAL_SETTINGS);
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("+++                              INSTALLATION SUCCESS\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("Press any key to exit...\n");
    getchar();
    return 0;
}