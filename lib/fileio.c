#include <stdio.h>
#include <windows.h>
#include <sys/stat.h>
#define MAX_PATH_EXT 1024

/**
 * @brief Checks recursively if a file exists at the given path.
 * @param filename The path to the file.
 * @example Usage:
 *      int exists = searchForFile("C:\\Users\\winuser\\Documents", "file.txt");
 * @param path The directory path to search in.
 * @return 1 if the file exists, 0 otherwise.
 */
int searchForFile(const char *path,const char *filename) {
    char pathbuffer[MAX_PATH_EXT];
    snprintf(pathbuffer,MAX_PATH_EXT,"%s\\*",path);
    // Windows API to search for the file
    WIN32_FIND_DATA findFileData;
    HANDLE hfind = FindFirstFile(pathbuffer, &findFileData);
    if (hfind == INVALID_HANDLE_VALUE){
        printf("Error finding files in pahth: %s\n", path);
        return 0; // File does not exist
    }
    do{
        int isdot = (strcmp(findFileData.cFileName,".") == 0);
        int isdotdot = (strcmp(findFileData.cFileName,"..")==0);
        if(isdot || isdotdot) continue; // Skip . and ..
        char retPath[MAX_PATH_EXT];
        snprintf(retPath,sizeof(retPath),"%s\\%s",path,findFileData.cFileName);
        if(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            searchForFile(retPath, filename);
        }else if (strcmp(findFileData.cFileName,filename) == 0) {
            // File found
            FindClose(hfind);
            return 1; // File exists
        }
    }while(FindNextFile(hfind, &findFileData));
    FindClose(hfind);
}

/**
 * @brief Checks if a file exists.
 * @example Usage:
 *      int exists = fileExists("C:\\Users\\winuser\\Documents\\file.txt");
 * @param filename The path to the file.
 * @return 1 if the file exists, 0 otherwise.
 */
int fileExists(const char *filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

/**
 * @brief Checks if a folder exists.
 * @example Usage:
 *      int exists = folderExists("C:\\Users\\winuser\\Documents");
 * @param filename The path to the file.
 * @return 1 if the folder exists, 0 otherwise.
 */
int folderExists(const char *path){
    struct stat buffer;
    int ret = stat(path,&buffer);
    return (ret == 0 && S_ISDIR(buffer.st_mode));
}

/**
 * @brief Checks recursively if a folder exists at the given path.
 * @param path The directory path to search in.
 * @param foldername The name of the folder to search for.
 * @example Usage:
 *      int exists = searchForFolder("C:\\Users\\winuser", "Documents");
 * @return 1 if the folder exists, 0 otherwise.
 */
int searchForFolder(const char *path, const char *foldername){
    char pathbuffer[MAX_PATH_EXT];
    snprintf(pathbuffer,MAX_PATH_EXT,"%s\\*",path);
    // Windows API to search for the folder
    WIN32_FIND_DATA findFileData;
    HANDLE hfind = FindFirstFile(pathbuffer, &findFileData);
    if (hfind == INVALID_HANDLE_VALUE) {
        return 0; // Folder does not exist
    }
    do {
        int isdot = (strcmp(findFileData.cFileName,".") == 0);
        int isdotdot = (strcmp(findFileData.cFileName,"..")==0);
        if (isdot || isdotdot) continue; // Skip . and ..
        char retPath[MAX_PATH_EXT];
        snprintf(retPath,sizeof(retPath),"%s\\%s",path,findFileData.cFileName);
        if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (strcmp(findFileData.cFileName,foldername) == 0) {
                // Folder found
                FindClose(hfind);
                return 1; // Folder exists
            }
            searchForFolder(retPath, foldername); // Recursively search in subfolders
        }
    } while (FindNextFile(hfind, &findFileData));
    FindClose(hfind);
    return 0; // Folder not found
}