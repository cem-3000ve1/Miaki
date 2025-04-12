#ifndef UTILS_H
#define UTILS_H

#include <vitasdk.h>
extern int ret;
extern int left;

int getFileSize(const char *file);
int WriteFile(char *file, void *buf, int size);
int ReadFile(char *file, void *buf, int size);
int CopyFile(char *src, char *dst);

#endif
