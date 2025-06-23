#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "headers/fileio.h"

void repChar(char *chr, int times){
    for(int i = 0; i < times; i++){
        putchar(*chr);
    }
    putchar('\n'); // Print a newline after repeating the character
}

int createPwshProfile(){
    if(folderExists("C:\\LegacyApp\\powershell") == 1) {
        printf("_> Creating PowerShell profile...\n");
        char command[1024];
        char *pwshProfileName = "C:/LegacyApp/powershell/Microsoft.PowerShell_profile.ps1";
        char *pwshProfileContent = "Import-Module -Name C:\\LegacyApp\\Powershell_Suite\\Profile.ps1";
        snprintf(command,sizeof(command),"powershell -C Write-Output '%s' > %s",pwshProfileContent,pwshProfileName);
        //printf("_> PowerShell profile content: %s\n", command);
        system(command);
        return 1; // Return success
    }else{
        repChar("!", 70); // Print a line of equal signs
        printf("[!] WARNING: PowerShell installation path does not exist. Please install PowerShell first\n");
        return 0; // Return failure
    }
}

int getLatestRelease(const char *target,const char *installationPath,const char *pattern,const char *output,const char *folderName) {
    char command[1024];
    const char *tempFile = "release.json";
    snprintf(command,sizeof(command),"curl.exe -s %s > %s",target,tempFile);
    system(command);
    FILE *file = fopen(tempFile,"r"); // open the file in read mode, holds the content of the file.
    if(file == NULL){
        perror("Error opening release.json");
        return 0;
    }
    char lineBuffer[1024];
    char urlBuffer[1024] = {0};
    char *mainPattern = "browser_download_url";
    command[0] = '\0'; // Clear the command buffer
    // fgets reads the file and stores each line in lineBuffer. 
    while(fgets(lineBuffer,sizeof(lineBuffer),file)){
        // strstr searches for the substrings
        char *downloadLink = strstr(lineBuffer,mainPattern);
        char *pattern_match = NULL;
        if(pattern != NULL){
            pattern_match = strstr(lineBuffer,pattern);
        }
        if(downloadLink && pattern_match) {
            char *quote = strchr(lineBuffer, ':');
            char *urlLink = quote + 1; // Move past the colon
            snprintf(command,sizeof(command),"curl.exe -L -o %s\\%s %s",installationPath,output,urlLink);
            system(command);
            command[0] = '\0'; // Clear the command buffer
            if(folderName != NULL) {
                snprintf(command,sizeof(command),"mkdir %s\\%s",installationPath,folderName);
                system(command);
                command[0] = '\0'; // Clear the command buffer
                snprintf(command,sizeof(command),"powershell -C \"Expand-Archive -Path '%s\\%s' -DestinationPath '%s\\%s'\" -Force",installationPath,output,installationPath,folderName);
            }else{
                snprintf(command,sizeof(command),"powershell -C \"Expand-Archive -Path '%s\\%s' -DestinationPath '%s'\" -Force",installationPath,output,installationPath);
            }
            system(command);
            repChar("-", 70); // Print a line of equal signs           
            printf("_> PowerShell Installed at: %s\\%s\n", installationPath,output);
            fclose(file); // Close the file after reading
            command[0] = '\0';
            snprintf(command,sizeof(command),"del %s", tempFile); // Delete the temporary file
            system(command);
            command[0] = '\0'; // Clear the command buffer
            snprintf(command,sizeof(command),"del %s\\%s",installationPath,output); // Delete the temporary file
            system(command);
            return 1; // Return success
        }
    }
    repChar("!", 70); // Print a line of equal signs
    printf("[!] WARNING: No download link found for the specified pattern: %s\n%s\n", pattern,mainPattern);
    fclose(file); // Close the file after reading
    return 0; // Return failure if no download link found
}

int moveIconsFolder(){
    if(folderExists("C:\\LegacyApp\\PowerShell_Suite\\Modules\\Terminal-Icons") == 1) {
        printf("_> Moving Terminal-Icons folder...\n");
        char command[1024];
        snprintf(command,sizeof(command),"move C:\\LegacyApp\\PowerShell_Suite\\Modules\\Terminal-Icons C:\\LegacyApp\\powershell\\Modules");
        return !system(command);
    }else{
        repChar("!", 70); // Print a line of equal signs
        printf("[!] WARNING: Terminal-Icons folder does not exist. Please install PowerShell Suite first\n");
        return 0; // Return failure
    }
}

int installLilexFont(){
    printf("_> Installing Lilex font...\n");
    char command[1024];
    snprintf(command, sizeof(command), "curl.exe -L -o lilex.zip https://github.com/ryanoasis/nerd-fonts/releases/download/v3.3.0/Lilex.zip");
    if(system(command) != 0) {
        repChar("!", 70); // Print a line of equal signs
        printf("[!] WARNING: Failed to download Lilex font.\n");
        return 0; // Return failure
    }
    command[0] = '\0'; // Clear the command buffer
    snprintf(command, sizeof(command), "powershell -C \"Expand-Archive -Path 'lilex.zip' -DestinationPath '.\\lilexfont'\" -Force");
    if(system(command) != 0) {
        repChar("!", 70); // Print a line of equal signs
        printf("[!] WARNING: Failed to extract Lilex font.\n");
        return 0; // Return failure
    }
    command[0] = '\0';
    printf("[!] INSTALL THE FONT AND CLOSE THE WINDOW TO CONTINUE ...");
    snprintf(command, sizeof(command), "start /Wait lilexfont\\LilexNerdFontPropo-Regular.ttf");
    if(system(command) != 0) {
        repChar("!", 70); // Print a line of equal signs
        printf("[!] WARNING: Failed to install Lilex font.\n");
        return 0; // Return failure
    }
    system("del lilex.zip");
    system("rmdir /S /Q lilexfont");
    return 1; // Return success
}

int setTerminalSettings() {
    printf("_> Configuring terminal settings...\n");
    char settingsPath[] = "%LOCALAPPDATA%\\Packages\\Microsoft.WindowsTerminal_8wekyb3d8bbwe\\LocalState\\settings.json";
    char command[1024];
    snprintf(command, sizeof(command), "move C:\\LegacyApp\\PowerShell_Suite\\terminal_settings.json %s", settingsPath);
    if(system(command) != 0) {
        repChar("!", 70); // Print a line of equal signs
        printf("[!] WARNING: Failed to configure terminal settings.\n");
        return 0; // Return failure
    }
    return 1; // Return success
}