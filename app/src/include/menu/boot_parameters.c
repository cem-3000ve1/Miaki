#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <vitasdk.h>
#include <taihen.h>

#include "../../miaki_user.h"

#include "../../ctrl.h"
#include "../../pup.h"
#include "boot_parameters.h"

#define printf psvDebugScreenPrintf

void boot_parameters(void) {
	int release = 0;
	int delete = 0;
    int devmode = 0;
	int back = 0;
        psvDebugScreenClear();
        psvDebugScreenPrintf("Boot Parameters:\n\n");
        psvDebugScreenPrintf("X: Enable DevMode\n");
        psvDebugScreenPrintf("O: Disable DevMode\n");
        sceKernelDelayThread(100000);
        switch(get_key(0)) {
            case SCE_CTRL_CROSS:
                devmode = 1;
                break;
            case SCE_CTRL_CIRCLE:
                release = 1;
                break;
            default:
                sceKernelExitProcess(0);
                break;
        }
		
        if (devmode)
        {
            DebugLog("Enable DevMode...");
            CopyFile("app0:/devmode.skprx", "ur0:tai/devmode.skprx");
            scePowerRequestColdReset();
        }

        if (release)
        {
            DebugLog("Disable DevMode...");
            sceIoRemove("ur0:tai/devmode.skprx");
            scePowerRequestColdReset();
        }
}
