/* edition.c -- CID Changer
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
#include "../../include/ui.h"

#include "../../include/miaki_user.h"

#include "../../include/ctrl.h"
#include "../../include/pup.h"
#include "../../include/utils.h"
#include "../../include/edition.h"
#include "../../include/deeper.h"

#define printf psvDebugScreenPrintf

/*

TOOL = DevKit
DEX = Testkit
TEST = Prototype

*/

void deeper(void) {
    int running = 1;
    Menu menu;
    psvDebugScreenClear();
    menu_create(&menu, "DeeperSpoof");
    miakiDeeperToolSpoof ? sel_printf(&menu, "[*] Flash TOOL DeeperSpoof") : sel_printf(&menu, "[] Flash TOOL DeeperSpoof");
    miakiToolSpoof ? sel_printf(&menu, "[*] Flash TOOL ProductCode") : sel_printf(&menu, "[] Flash TOOL ProductCode");
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
            if (deeper) {
                switch (menu.selected) {
                    case 0:
                        sceClibPrintf("TEST");
						miakiDeeperToolSpoof = 1;
                        miakiToolSpoof = 0;
                        deeper();
                        needs_refresh = 1;
                        break;
                    case 1:
                        miakiToolSpoof = 1;
                        miakiDeeperToolSpoof = 0;
                        deeper();
                        needs_refresh = 1;
                        break;
                }
            } 
        }
		if(key == SCE_CTRL_CIRCLE)
		{
            menu_destroy(&menu);
			menu_edition();
		}
        if (needs_refresh) {
            menu_draw(&menu);
        }
        sceKernelDelayThread(10000);
    }
        
}
