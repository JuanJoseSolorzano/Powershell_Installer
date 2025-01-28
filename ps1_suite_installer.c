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

#define PS1_COMMAND "powershell -C start-process %s"
#define PS1_VERSION "7.4.7"
#define URL_API "https://github.com/PowerShell/PowerShell/releases/download/v%s/PowerShell-%s-win-x64.zip"
#define PWSH_SITE "https://github.com/JuanJoseSoloraznoCarrillo/PowerShell/archive/refs/heads/master.zip"
#define FOLDER_INST "C:\\LegacyApp\\powershell"

/**
 * 
 */
int url_request(const char *link){
    char command[512];
    char *cmd_request = "powershell -C \"try{$req=Invoke-WebRequest -Uri '%s' -UseBasicParsing -Method Head; exit 0} catch{exit 1}\"";
    sprintf(command,cmd_request,link);
    return system(command) == 0;
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
    printf("Extracting file: %s ...\n",target);
    char cmd_buf[MAX_PATH];
    sprintf(cmd_buf,"tar -xf \"%s\" -C \"%s\"",target,destination);
    system(cmd_buf);
    printf("Unziped file: %s\n",destination);
}
int move_file(char target[],char destination[]){
    printf("Moving file %s to %s\n",target,destination);
    char cmd_buf[MAX_PATH];
    sprintf(cmd_buf,"mv %s %s",target,destination);
    system(cmd_buf);
    Sleep(2000);
    return 1;
}
int download_pwsh(char *buffer){
    printf("Downloading PowerShell-7.4.7-win-x64.zip ...");
    sprintf(buffer,PS1_COMMAND,URL_API);
    system(buffer);
    clear_buffer(buffer);
    Sleep(13000); //waiting for downloaded file.
    return 1;
}
int create_folder(char *buffer){
    printf("Creating installatioin folder: '%s'\n",FOLDER_INST);
    sprintf(buffer,"mkdir %s",FOLDER_INST);
    system(buffer);
    clear_buffer(buffer);
    return 1;
}
int install_pwsh(){
    move_file("%USERPROFILE%\\Downloads\\PowerShell-7.4.7-win-x64.zip","C:\\LegacyApp\\powershell\\");
    unzip("C:/LegacyApp/powershell/PowerShell-7.4.7-win-x64.zip","C:/LegacyApp/powershell/");
    printf("Powershell installation -> Done.\n");
    return 1;
}
int download_pwsh_suite(char *buffer){
    sprintf(buffer,PS1_COMMAND,PWSH_SITE);
    system(buffer);
    clear_buffer(buffer);
    Sleep(5000);
    move_file("%USERPROFILE%\\Downloads\\PowerShell-master.zip","C:\\LegacyApp\\powershell\\");
    unzip("C:/LegacyApp/powershell/PowerShell-master.zip","C:/LegacyApp/powershell/");
}

/**
 * Main
 */
int main(int argc,char *argv[]){
    char *version = NULL;
    if(argc>1){
        if(strcmp(argv[1],"version")||strcmp(argv[1],"-version")||strcmp(argv[1],"v")||strcmp(argv[1],"-v")){
            version = argv[2];
        }else{
            printf("Unknow argument: %s\n",argv[1]);
            version = PS1_VERSION;
        }
    }
    char url_api[MAX_PATH];
    sprintf(url_api,URL_API,PS1_VERSION,PS1_VERSION);
    int exist = url_request(url_api);
    if(exist==1){
        printf("Url exist....\n");
    }else{
        printf("Url does not exists\n");
    }

    //char cmd_buffer[MAX_PATH]; //Command string buffering.
    //if(!download_pwsh(cmd_buffer)){
    //    // was not possible to download the 
    //    printf("[!] Error: while download the PowerShell-7.4.7-win-x64.zip");
    //    return 1;
    //}
    //if(!folder_exists(FOLDER_INST)){
    //   create_folder(cmd_buffer);
    //}else{
    //    printf("Powershell installation found, removing folder ...\n");
    //    sprintf(cmd_buffer,"rmdir /s /q %s",FOLDER_INST);
    //    system(cmd_buffer);
    //    clear_buffer(cmd_buffer);
    //    create_folder(cmd_buffer);
    //}
    //if(!install_pwsh()){
    //    return 1;
    //}
    //download_pwsh_suite(cmd_buffer);
}


//"$profile_prompt = C:/....Profile.ps1"
//"Import-Module -Name $profile"