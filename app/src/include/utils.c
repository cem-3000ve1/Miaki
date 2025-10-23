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

// Spoofer variables
int rool_spoof = 0;
int rtu_spoof = 0;
int rex_spoof = 0;

// Boot Parameters
int devmodeii = 0;
int ReleaseMode = 0;

// Activator 
int ActivatedNoDate = 0;
int ActivatedWithDate = 0;
int Expired = 0;

// Checker
int CheckerCID = 0;
int CheckerBoot = 0;
int CheckerAct = 0;

int vshSblAimgrIsCEX(void);
int vshSblAimgrIsDEX(void);
int vshSblAimgrIsTool(void);
int vshSblAimgrIsTest(void);

// Fixed by LazyPreview
void DebugLog(const char *fmt, ...)
{
	va_list args1, args2;

	va_start(args1, fmt);
	va_copy(args2, args1);

	psvDebugScreenPrintf(fmt, args1);
	sceClibVprintf(fmt, args2);

	va_end(args1);
	va_end(args2);
}

static int CheckerListBoot()
{
	if (ReleaseMode)
	return getFileSize("ur0:tai/devmode.skprx") > 0 ? 1 : 0;

	if (devmodeii)
	return getFileSize("ur0:tai/devmode.skprx") <= 0 ? 1 : 0;

	return 0;
}

static int CheckerListCid()
{
	int cex = vshSblAimgrIsCEX();
	int dex = vshSblAimgrIsDEX();
	int test = vshSblAimgrIsTest();
	int tool = vshSblAimgrIsTool();

	if (rtu_spoof && !test)
	return 1;

	if (rex_spoof && !dex)
	return 1;

	if (rool_spoof && !tool)
	return 1;

	return 0;
}

void checker()
{
CheckerCID = CheckerListCid();
CheckerBoot = CheckerListBoot();
}

void apply()
{
	// Base
	checker();
	DebugLog("Starting ProcessList...\n");
	int activity = 0;
	// ProcessList 
	if (CheckerCID)
		{
			// Spoofer
			if (rool_spoof)
			{
				activity = 1;
				DebugLog("TOOL spoof\n");
				CopyFile("app0:/dev_vita.skprx", "ur0:tai/testkit.skprx");
			}
			else if (rtu_spoof)
			{
				activity = 1;
				DebugLog("TEST spoof\n");
				CopyFile("app0:/pro_vita.skprx", "ur0:tai/testkit.skprx");
			}
			else if (rex_spoof)
			{
				activity = 1;
				DebugLog("DEX spoof\n");
				CopyFile("app0:/testkit_vita.skprx", "ur0:tai/testkit.skprx");
			}
		}

		
		if (CheckerBoot)
		{
			// ReleaseCheckMode
			if (ReleaseMode)
			{
				activity = 1;
				DebugLog("Release Mode\n");
				sceIoRemove("ur0:tai/devmode.skprx");
			}
			else if (devmodeii)
			{
				activity = 1;
				DebugLog("Development Mode\n");
				CopyFile("app0:/devmode.skprx", "ur0:tai/devmode.skprx");
			}
		}
		// Activator
		if (ActivatedNoDate)
		{
			activity = 1;
			DebugLog("ActivatedNoDate\n");
			CopyFile("app0:/kmspico.skprx", "ur0:tai/kmspico.skprx");
		}
		else if (ActivatedWithDate)
		{
			activity = 1;
			DebugLog("ActivatedWithDate\n");
			CopyFile("app0:/dkmspico.skprx", "ur0:tai/kmspico.skprx");
		}
		else if (Expired)
		{
			activity = 1;
			DebugLog("Expired\n");
			sceIoRemove("ur0:tai/kmspico.skprx");
		}

		if (activity)
		{
			DebugLog("Rebooting in 3s...\n");
			sceKernelDelayThread(3000000);
			scePowerRequestColdReset();
		}
		else
		{
			DebugLog("Nothing to do...\n");
			sceKernelDelayThread(3000000);
			sceKernelExitProcess(0);
		}

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
