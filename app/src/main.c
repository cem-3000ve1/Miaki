#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <vitasdk.h>
#include <taihen.h>

#include "miaki_user.h"

#include "ctrl.h"
#include "debugScreen.h"
#include "pup.h"
#include "include/utils.h"
#include "include/menu/edition.h"
#include "include/menu/activation.h"
#include "include/menu/boot_parameters.h"
#include "include/modules.h"
#include "include/flasher.h"

#define printf psvDebugScreenPrintf
char ver[] = "Miaki v2.1.2";



int isRex()
{
	if(getFileSize("vs0:/app/NPXS10998/sce_sys/livearea/contents/bg0.png") > 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void copyappinfo() // Setup Epic "interlectural property notices" thing
{
	if(getFileSize("ux0:/psm/CEXR20202/RO/Application/app.info") != getFileSize("app0:/app.info"))
	{
		sceIoMkdir("ux0:/psm", 0777);
		sceIoMkdir("ux0:/psm/CEXR20202", 0777);
		sceIoMkdir("ux0:/psm/CEXR20202/RO", 0777);
		sceIoMkdir("ux0:/psm/CEXR20202/RO/Application", 0777);
		CopyFile("app0:/app.info","ux0:/psm/CEXR20202/RO/Application/app.info");
	}
}


int main() {
		copyappinfo();
		psvDebugScreenInit();
        psvDebugScreenClear(0);
        sceClibPrintf("\n");
        sceClibPrintf("-----MIAKI LOG-----\n");
        sceClibPrintf("Release: Public\n");
        sceClibPrintf("Version: %s\n", ver);
			
		int pup_type = 0;
		int fd = sceIoOpen("ux0:/DEX.PUP", SCE_O_RDONLY, 0777);
		if(fd > 0)
		{
			sceIoLseek(fd,0x3c,SCE_SEEK_SET);
			sceIoRead(fd,&pup_type, sizeof(int));
			sceIoClose(fd);
		}
		else
		{
			char version[16];
			SceKernelFwInfo data;
			data.size = sizeof(SceKernelFwInfo);
			_vshSblGetSystemSwVersion(&data);
			snprintf(version, 16, "%s", data.versionString);
			
			psvDebugScreenPrintf("ux0:/DEX.PUP NOT FOUND!\nPlease download the DEX %s firmware update file (.PUP)\nAnd place it in ux0:/DEX.PUP",version);
			while(1){};
		}
		
		
		if(isRex() == 0)
		{
            sceClibPrintf("DevKit fw: Not installed\n");
			psvDebugScreenPrintf("%s - Currently CEX\n", ver);
			psvDebugScreenPrintf("X: Install DevKit Firmware\n");
			
			sceKernelDelayThread(100000);
			while(1)
			{
				switch(get_key(0)) {
						case SCE_CTRL_CROSS:
							install();
							break;
						default:
							break;
						}
			}
		}
		else
		{
            sceClibPrintf("Devkit fw: Installed\n");
            if(getFileSize("ur0:tai/devmode.skprx") > 0)
            {
                sceClibPrintf("Release Mode: DevMode\n");
            }
            else
            {
                sceClibPrintf("Realese Mode: Release\n");
            }

            if(getFileSize("ur0:tai/kmspico.skprx") > 0)
            {
                sceClibPrintf("Activation status: Activated\n");
            }
            else
            {
                sceClibPrintf("Activation status: Expired\n");
            }

			psvDebugScreenPrintf("%s - Currently REX\n\n", ver);
			psvDebugScreenPrintf("X: Uninstall DevKit Firmware\n");
			psvDebugScreenPrintf("O: Change Activation\n");
			psvDebugScreenPrintf("[]: Change Edition\n");
			psvDebugScreenPrintf("/\\ : Boot Parameters\n");
			sceKernelDelayThread(100000);
			switch(get_key(0)) {
						case SCE_CTRL_CROSS:
                        sceClibPrintf("Starting uninstaller...\n");
							uninstall();
							break;
						case SCE_CTRL_CIRCLE:
                        sceClibPrintf("Activation menu\n");
							activator();
							break;
						case SCE_CTRL_SQUARE:
                        sceClibPrintf("Edition menu\n");
							menu_edition();
							break;
						case SCE_CTRL_TRIANGLE:
                        sceClibPrintf("Boot Parameters\n");
							boot_parameters();
							break;
						default:
							break;
						}
		}
    return 0;
}
