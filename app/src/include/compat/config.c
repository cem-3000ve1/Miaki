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

void cex2rexconfig(void)
{
	int spoofer = 0;
	int activator = 0;
	int pstv = sceKernelIsPSVitaTV();
configMenuStart:
	psvDebugScreenClear(0);
	
	psvDebugScreenPrintf("Installation Type\n\n");
	psvDebugScreenPrintf("Please confirm: ");
	if(pstv)
		psvDebugScreenPrintf("(PlayStation Vita TV)\n");
	else
		psvDebugScreenPrintf("(PlayStation Vita Handheld)\n");
	psvDebugScreenPrintf("If you use the wrong config you have to reinstall firmware!\n\n");
	
	psvDebugScreenPrintf("X: Full Install (spoofer + activator + testkit vsh)\n");
	psvDebugScreenPrintf("O: Warning Message Install (spoofer + testkit vsh)\n");
	psvDebugScreenPrintf("[]: Enso-less Install (testkit vsh)\n");
	psvDebugScreenPrintf("/\\: Switch machine type (VITA <-> PSTV)\n");
	
	sceKernelDelayThread(100000);

	switch(get_key(0)) {
			case SCE_CTRL_CROSS:
				activator = 1;
				spoofer = 1;
                scePowerRequestColdReset();
				break;
			case SCE_CTRL_CIRCLE:
				spoofer = 1;
                scePowerRequestColdReset();
				break;
			case SCE_CTRL_TRIANGLE:
				pstv = !pstv;
				goto configMenuStart;
                scePowerRequestColdReset();
				break;
			case SCE_CTRL_SQUARE:
                scePowerRequestColdReset();
				break;
			default:
				sceKernelExitProcess(0);
				break;
			}
	
	
	psvDebugScreenClear();
	sceIoRemove("ur0:tai/testkit.skprx");
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
