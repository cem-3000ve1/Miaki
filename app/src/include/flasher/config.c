#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <vitasdk.h>
#include <taihen.h>

#include "../../miaki_user.h"

#include "../../ctrl.h"
#include "../../pup.h"
#include "../flasher.h"
#include "../utils.h"
#include "../modules.h"
#define printf psvDebugScreenPrintf

void config(void)
{
    int spoofer = 0;
    int activator = 0;
    int pstv = sceKernelIsPSVitaTV();
    configMenuStart:
    psvDebugScreenClear(0);

    psvDebugScreenPrintf("Installation Type\n\n");
    psvDebugScreenPrintf("Please confirm: ");
    if(pstv)
    {
        psvDebugScreenPrintf("PSTV is not supported...\n");
        sceKernelExitProcess(0);
    } else {
        psvDebugScreenPrintf("(PlayStation Vita Handheld)\n");
        psvDebugScreenPrintf("If you use the wrong config you have to reinstall firmware!\n\n");
    }

    psvDebugScreenPrintf("X: Activated DevKit\n");
    psvDebugScreenPrintf("O: Expired DevKit\n");

    sceKernelDelayThread(100000);

    switch(get_key(0)) {
        case SCE_CTRL_CROSS:
            activator = 1;
            spoofer = 1;
            break;
        case SCE_CTRL_CIRCLE:
            spoofer = 1;
            break;
        default:
            sceKernelExitProcess(0);
            break;
    }


    psvDebugScreenClear();
    sceIoRemove("ur0:tai/testkit.skprx");
    CopyFile("app0:/reF00D.skprx", "ur0:tai/reF00D.skprx");
    sceIoRemove("ur0:tai/kmspico.skprx");

    if(spoofer)
    {
        psvDebugScreenPrintf("Writing testkit.skprx");

        //int pstv = vshSblAimgrIsGenuineDolce(); - my PSTV was not genuine :'( I need to buy a product key for it..
        //In the meantime, sceKernelIsPSVitaTV() it is!

        if(pstv)
        {
            CopyFile("app0:/pstvConfig.txt","ur0:tai/boot_config.txt");
            CopyFile("app0:/testkit_pstv.skprx","ur0:tai/testkit.skprx");

        }
        else
        {
            CopyFile("app0:/vitaConfig.txt","ur0:tai/boot_config.txt");
            CopyFile("app0:/testkit_vita.skprx","ur0:tai/testkit.skprx");
        }
    }

    if(activator)
    {
        psvDebugScreenPrintf("Writing kmspico.skprx");
        CopyFile("app0:/kmspico.skprx","ur0:tai/kmspico.skprx");
    }
}
