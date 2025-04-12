#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <vitasdk.h>
#include <taihen.h>

#include "../../miaki_user.h"

#include "../../ctrl.h"
#include "../../pup.h"
#include "activation.h"

#define printf psvDebugScreenPrintf

void activator(void) {
    int activated = 0;
    int expired = 0;
    psvDebugScreenClear();
    psvDebugScreenPrintf("Miaki activation spoofer:\n\n");
    psvDebugScreenPrintf("X: Activated\n");
    psvDebugScreenPrintf("O: Expired\n");
    sceKernelDelayThread(100000);
    switch(get_key(0)) {
            case SCE_CTRL_CROSS:
                activated = 1;
                break;
            case SCE_CTRL_CIRCLE:
                expired = 1; 
                break;
            default:
                break;
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
