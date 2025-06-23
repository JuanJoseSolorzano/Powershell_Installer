#ifndef FILEIO_H
#define FILEIO_H

#define MAX_PATH_EXT 1024
#define INSTALLATION_PATH "C:\\LegacyApp\\powershell"

int fileExists(const char *filename);
int searchForFile(const char *path, const char *filename);
int folderExists(const char *path);
int searchForFolder(const char *path, const char *foldername);

#endif // FILEIO_H
