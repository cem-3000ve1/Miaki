/* activation.c -- Activator Menu
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
#include "../ui/ui.h"

#include "../../miaki_user.h"

#include "../../ctrl.h"
#include "../../pup.h"
#include "../utils.h"
#include "activation.h"

#define printf psvDebugScreenPrintf

void activator(void) {
    Menu menu;
    int running = 1;
    int activated = 0;
    int expired = 0;
    //int yellowmsg = 0;
    int lowactivation = 0;
    psvDebugScreenClear();
    /*
    
    Henkaku on an activated kit can have issues. I recommend using Red-Msg-Del (by Princess of Sleeping) with TOOL CID.
    https://github.com/Princess-of-Sleeping/Red-Msg-Delete/releases/tag/v1.1

    */
    menu_create(&menu, "Miaki Activation Spoofer");
    menu_printf(&menu, "Miaki activation spoofer:");
    menu_printf(&menu, "ONLY DEX SPOOF!");
    sel_printf(&menu, "No expiration Date");
	sel_printf(&menu, "Expiration Date!");
    sel_printf(&menu, "Expired");
    menu_draw(&menu);
    while (running) {
        uint32_t key = get_key(0);
        int needs_refresh = 0;
        if (key == SCE_CTRL_UP) {
            if (menu.selected > 0) {
                menu.selected--;
                needs_refresh = 1;
            }
            sceKernelDelayThread(150000);
        }
        if (key == SCE_CTRL_DOWN) {
            if (menu.selected < menu.option_count - 1) {
                menu.selected++;
                needs_refresh = 1;
            }
            sceKernelDelayThread(150000);
        }
        if (key == SCE_CTRL_CROSS) {
            if (activator) {
                switch (menu.selected) {
                    case 0:
                        psvDebugScreenClear();
                        psvDebugScreenPrintf("Activated!");
                        sceClibPrintf("Activated!\n");
                        CopyFile("app0:/kmspico.skprx", "ur0:tai/kmspico.skprx");
                        scePowerRequestColdReset();
                        needs_refresh = 1;
                        break;
                    case 1:
                        psvDebugScreenClear();
                        psvDebugScreenPrintf("Activated!");
                        sceClibPrintf("Activated!\n");
                        CopyFile("app0:/dkmspico.skprx", "ur0:tai/kmspico.skprx");
                        scePowerRequestColdReset();
                        needs_refresh = 1;
                    case 2:
                        psvDebugScreenClear();
                        psvDebugScreenPrintf("Expired!");
                        sceClibPrintf("Expired!\n");
                        sceIoRemove("ur0:tai/kmspico.skprx");
                        scePowerRequestColdReset();
                        needs_refresh = 1;
                        break;
                    case 4:
                        running = 0;
                        break;
                }
            } 
        }
		if(key == SCE_CTRL_CIRCLE)
		{
			main();
		}

        if (needs_refresh) {
            menu_draw(&menu);
        }
        sceKernelDelayThread(10000);
    }
        
}
