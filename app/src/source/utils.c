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

#include "../include/miaki_user.h"

#include "../include/ctrl.h"
#include "../include/pup.h"


#define printf psvDebugScreenPrintf
 
int ret;
int left = -1;

// Spoofer variables
int rool_spoof = 0;
int rtu_spoof = 0;
int rex_spoof = 0;
int iduset = 0;
int iduclear = 0;

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
int CheckerIDU = 0;
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

static int CheckerListIDU()
{
	int iduenabled = vshSysconIduModeSet();
	int idudisabled = vshSysconIduModeClear();

	if (iduset)
	{
		if (iduenabled == 1)
		{
			return 0;
		}
		else
		{
			return 1;
		}
   	}

	if (iduclear)
	{
		if (idudisabled == 1)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
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
CheckerIDU = CheckerListIDU();
CheckerCID = CheckerListCid();
CheckerBoot = CheckerListBoot();
}

void apply()
{
	// Base
	checker();
	DebugLog("\n[MIAKI]: Starting ProcessList...\n");
	int activity = 0;
	int iduactivity = 0;
	// ProcessList 
	if (CheckerCID)
		{
			// Spoofer
			if (rool_spoof)
			{
				activity = 1;
				DebugLog("[MIAKI]: Loaded TOOL spoof\n");
				CopyFile("app0:/dev_vita.skprx", "ur0:tai/testkit.skprx");
			}
			else if (rtu_spoof)
			{
				activity = 1;
				DebugLog("[MIAKI]: Loaded TEST spoof\n");
				CopyFile("app0:/pro_vita.skprx", "ur0:tai/testkit.skprx");
			}
			else if (rex_spoof)
			{
				activity = 1;
				DebugLog("[MIAKI]: Loaded DEX spoof\n");
				CopyFile("app0:/testkit_vita.skprx", "ur0:tai/testkit.skprx");
			}
		}

		if (CheckerIDU)
		{
			if (iduset)
			{
				iduactivity = 1;
				ret = vshSysconIduModeSet();
			}

			if (iduclear)
			{
				iduactivity = 1;
				ret = vshSysconIduModeClear();
			}
		}
		
		if (CheckerBoot)
		{
			// ReleaseCheckMode
			if (ReleaseMode)
			{
				activity = 1;
				DebugLog("[MIAKI]: Change to Release Mode\n");
				sceIoRemove("ur0:tai/devmode.skprx");
			}
			else if (devmodeii)
			{
				activity = 1;
				DebugLog("[MIAKI]: Change to Development Mode\n");
				CopyFile("app0:/devmode.skprx", "ur0:tai/devmode.skprx");
			}
		}
		// Activator
		if (ActivatedNoDate)
		{
			activity = 1;
			DebugLog("[MIAKI]: Activated for ever\n");
			CopyFile("app0:/kmspico.skprx", "ur0:tai/kmspico.skprx");
		}
		else if (ActivatedWithDate)
		{
			activity = 1;
			DebugLog("[MIAKI]: Activated with date\n");
			CopyFile("app0:/dkmspico.skprx", "ur0:tai/kmspico.skprx");
		}
		else if (Expired)
		{
			activity = 1;
			DebugLog("[MIAKI]: Expired\n");
			sceIoRemove("ur0:tai/kmspico.skprx");
		}

		if (iduactivity)
		{
			psvDebugScreenPrintf("IDU detected. To enable/disable IDU mode, turn off your console and then turn it back on. Miaki will close in 6 seconds.\n");
			sceClibPrintf("[MIAKI]: IDU detected. manual reboot required.\n");
			sceKernelDelayThread(6000000);
			sceKernelExitProcess(0);
			
		}
		else if (activity)
		{
			DebugLog("[MIAKI]: The console while reboot in 3s...\n");
			sceKernelDelayThread(3000000);
			scePowerRequestColdReset();
		}
		else
		{
			DebugLog("[MIAKI]: Nothing to do...\n");
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
