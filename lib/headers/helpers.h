#ifndef HELPERS_H
#define HELPERS_H
int getLatestRelease(const char *target,const char *installationPath,const char *pattern,const char *output,const char *folderName);
int createPwshProfile();
int moveIconsFolder();
int installLilexFont();
int setTerminalSettings();
void repChar(char *chr, int times);
#endif // HELPERS_H