#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <vitasdk.h>
#include <taihen.h>

#include "../../miaki_user.h"

#include "../../ctrl.h"
#include "../../pup.h"
#include "edition.h"

#define printf psvDebugScreenPrintf


void menu_edition(void) {
    int pro = 0;
    int dev = 0;
    int test = 0;
    sceKernelDelayThread(100000);
    psvDebugScreenClear(0);
    psvDebugScreenPrintf("Product Code Spoof:\n\n");
    psvDebugScreenPrintf("X: Switch TOOL spoof\n");
    psvDebugScreenPrintf("O: Switch DEX spoof\n");
    psvDebugScreenPrintf("[]: Switch PRO spoof\n");

    sceKernelDelayThread(100000);
    switch(get_key(0)) {
        case SCE_CTRL_CROSS:
            dev = 1;
            break;
        case SCE_CTRL_CIRCLE:
            test = 1;
            break;
        case SCE_CTRL_SQUARE:
            pro = 1;
            break;
        default:
            sceKernelExitProcess(0);
            break;
    }

    if (dev)
    {
        DebugLog("Switching to TOOL");
        CopyFile("app0:/dev_vita.skprx", "ur0:tai/testkit.skprx");
        scePowerRequestColdReset();
    }

    if (test)
    {
        DebugLog("Switching to DEX");
        CopyFile("app0:/testkit_vita.skprx", "ur0:tai/testkit.skprx");
        scePowerRequestColdReset();
    }

    if (pro)
    {
        DebugLog("Switching to PRO");
        CopyFile("app0:/pro_vita.skprx", "ur0:tai/testkit.skprx");
        scePowerRequestColdReset();
    }
}
