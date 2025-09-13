/* utils.c -- Main Application
 *
 * Copyright (C) 2025 LazyPreview
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <vitasdk.h>
#include <taihen.h>
#include <psp2/kernel/clib.h>

#include "../miaki_user.h"

#include "../ctrl.h"
#include "../pup.h"

#define printf psvDebugScreenPrintf
 
int ret;
int left = -1;

// Fixed by LazyPreview
void DebugLog(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
	va_start(args, fmt);
	sceClibVprintf(fmt, args);
	va_end(args);
}

int getFileSize(const char *file) {
	SceUID fd = sceIoOpen(file, SCE_O_RDONLY, 0);
	if (fd < 0)
		return fd;
	int fileSize = sceIoLseek(fd, 0, SCE_SEEK_END);
	sceIoClose(fd);
	return fileSize;
}

int WriteFile(char *file, void *buf, int size) {
	SceUID fd = sceIoOpen(file, SCE_O_RDWR | SCE_O_CREAT, 0777);
	if (fd < 0)
		return fd;

	int written = sceIoWrite(fd, buf, size);

	sceIoClose(fd);
	return written;
}

int ReadFile(char *file, void *buf, int size) {
	SceUID fd = sceIoOpen(file, SCE_O_RDONLY, 0777);
	if (fd < 0)
		return fd;

	int readed = sceIoRead(fd, buf, size);

	sceIoClose(fd);
	return readed;
}



int CopyFile(char *src, char *dst)
{
	int size = getFileSize(src);
	char *data = malloc(size);
	memset(data,0,size);
	ret = ReadFile(src,data,size);
	if(ret < 0){
			psvDebugScreenPrintf("ReadFile() failed. ret = 0x%x\n", ret);
			while(1){};
	}
	ret = WriteFile(dst,data,size);
	if(ret < 0){
			psvDebugScreenPrintf("WriteFile() failed. ret = 0x%x\n", ret);
	}
	return 0;
}
