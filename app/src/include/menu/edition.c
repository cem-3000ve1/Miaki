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
    psvDebugScreenPrintf("PSvita CID:\n\n");
    psvDebugScreenPrintf("X: PSvita DevKit\n");
    psvDebugScreenPrintf("O: PSvita TestKit\n");
    psvDebugScreenPrintf("[]: PSvita Prototype\n");

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
        psvDebugScreenPrintf("Switching to DevKit...");
        CopyFile("app0:/dev_vita.skprx", "ur0:tai/testkit.skprx");
        scePowerRequestColdReset();
    }

    if (test)
    {
        psvDebugScreenPrintf("Switching to TestKit...");
        CopyFile("app0:/testkit_vita.skprx", "ur0:tai/testkit.skprx");
        scePowerRequestColdReset();
    }

    if (pro)
    {
        psvDebugScreenPrintf("Switching to Prototype...");
        CopyFile("app0:/pro_vita.skprx", "ur0:tai/testkit.skprx");
        scePowerRequestColdReset();
    }
}