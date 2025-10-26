/* utils.h -- Main Application
 *
 * Copyright (C) 2025 LazyPreview
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#ifndef UTILS_H
#define UTILS_H

#include <vitasdk.h>
extern int ret;
extern int left;

void DebugLog(const char *fmt, ...);
int getFileSize(const char *file);
int WriteFile(char *file, void *buf, int size);
int ReadFile(char *file, void *buf, int size);
int CopyFile(char *src, char *dst);

void apply(void);
void checker(void);
extern int miakiToolSpoof;
extern int miakiTestSpoof;
extern int miakiDexSpoof;
extern int miakiEnableDevMode;
extern int miakiDisableDevMode;
extern int miakiActivated;
extern int miakiActivation;
extern int miakiExpired;
extern int miakiEnableIDU;
extern int miakiClearIDU;


#endif
