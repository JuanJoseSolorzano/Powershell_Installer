#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <windows.h>
#include <time.h>

#define PS1_COMMAND "powershell -C start-process %s"
#define URL_API "https://github.com/PowerShell/PowerShell/releases/download/v7.4.7/PowerShell-7.4.7-win-x64.zip"
#define PWSH_SITE "https://github.com/JuanJoseSoloraznoCarrillo/PowerShell/archive/refs/heads/master.zip"
#define FOLDER_INST "C:\\LegacyApp\\powershell"

/**
 * 
 */
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

int main(int argc,char *argv[]){
    char cmd_buffer[MAX_PATH];
    if(!download_pwsh(cmd_buffer)){
        printf("[!] Error: while download the PowerShell-7.4.7-win-x64.zip");
        return 1;
    }
    if(!folder_exists(FOLDER_INST)){
       create_folder(cmd_buffer);
    }else{
        printf("Powershell installation found, removing folder ...\n");
        sprintf(cmd_buffer,"rmdir /s /q %s",FOLDER_INST);
        system(cmd_buffer);
        clear_buffer(cmd_buffer);
        create_folder(cmd_buffer);
    }
    if(!install_pwsh()){
        return 1;
    }
    download_pwsh_suite(cmd_buffer);
}


//"$profile_prompt = C:/....Profile.ps1"
//"Import-Module -Name $profile"