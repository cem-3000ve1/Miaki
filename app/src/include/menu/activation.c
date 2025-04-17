#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <vitasdk.h>
#include <taihen.h>

#include "../../miaki_user.h"

#include "../../ctrl.h"
#include "../../pup.h"
#include "../utils.h"
#include "activation.h"

#define printf psvDebugScreenPrintf

void activator(void) {
    int activated = 0;
    int expired = 0;
    int yellowmsg = 0;
    int lowactivation = 0;
    psvDebugScreenClear();
    psvDebugScreenPrintf("Miaki activation spoofer:\n");
    psvDebugScreenPrintf("ONLY DEX SPOOF!\n\n");
    psvDebugScreenPrintf("X: 12y Activation date\n");
    psvDebugScreenPrintf("O: Expired\n");
    psvDebugScreenPrintf("[]: Yellow message (1d act)\n");
    psvDebugScreenPrintf("/\\: 38d Activation date\n");
    sceKernelDelayThread(100000);
    switch(get_key(0)) {
            case SCE_CTRL_CROSS:
                activated = 1;
                break;
            case SCE_CTRL_CIRCLE:
                expired = 1; 
                break;
            case SCE_CTRL_SQUARE:
                yellowmsg = 1;
                break;
            case SCE_CTRL_TRIANGLE:
                lowactivation = 1;
                break;
            default:
                break;
            }
            
    if (yellowmsg)
    {
        psvDebugScreenClear();
        DebugLog("1d activated");
        CopyFile("app0:/ykmspico.skprx", "ur0:tai/kmspico.skprx");
        scePowerRequestColdReset();
    }

    if (lowactivation)
    {
        psvDebugScreenClear();
        DebugLog("38d activated");
        CopyFile("app0:/lowkmspico.skprx", "ur0:tai/kmspico.skprx");
        scePowerRequestColdReset();
    }

    if (activated)
    {
        psvDebugScreenClear();
        psvDebugScreenPrintf("Activated!");
        sceClibPrintf("Activated!\n");
        CopyFile("app0:/kmspico.skprx", "ur0:tai/kmspico.skprx");
        scePowerRequestColdReset();
    }

    if (expired)
    {
        psvDebugScreenClear();
        psvDebugScreenPrintf("Expired!");
        sceClibPrintf("Expired!\n");
        sceIoRemove("ur0:tai/kmspico.skprx");
        scePowerRequestColdReset();
    }
}
