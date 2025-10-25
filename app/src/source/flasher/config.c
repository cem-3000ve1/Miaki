#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <vitasdk.h>
#include <taihen.h>

#include "../../include/miaki_user.h"

#include "../../include/ctrl.h"
#include "../../include/pup.h"
#include "../../include/flasher.h"
#include "../../include/utils.h"
#include "../../include/modules.h"
#define printf psvDebugScreenPrintf

void config(void)
{
    int spoofer = 0;
    int activator = 0;
	int running = 1;
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

    psvDebugScreenPrintf("X: Activated TOOL\n");
    psvDebugScreenPrintf("O: Expired TOOL\n");

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
          //  CopyFile("app0:/pstvConfig.txt","ur0:tai/boot_config.txt");
          //  CopyFile("app0:/testkit_pstv.skprx","ur0:tai/testkit.skprx");

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

void installconfig(void)
{
    int enso_less = 0;
    int enso = 0;
    psvDebugScreenClear();
    psvDebugScreenPrintf("X: Enso-less installation");
    psvDebugScreenPrintf("O: Enso installation");

    switch(get_key(0)) {
        case SCE_CTRL_CROSS:
            enso_less = 1;
            break;
        case SCE_CTRL_CIRCLE:
            enso = 1;
            break;
        default:
            sceKernelExitProcess(0);
            break;
    }

    if(enso_less)
    {
        sceIoMkdir("ur0:temp/miaki", 0777);
        sceIoMkdir("ur0:temp/miaki/cex", 0777);
        sceIoMkdir("ur0:temp/miaki/tool", 0777);
        CopyFile("vs0:vsh/shell/shell.self", "ur0:temp/miaki/cex");
        DebugLog("Enso less");
    }

    if(enso)
    {
        DebugLog("Enso");
    }
}