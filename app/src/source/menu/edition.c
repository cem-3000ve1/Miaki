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

void menu_edition(void) {
    int running = 1;
    Menu menu;
    psvDebugScreenClear();
    menu_create(&menu, "ProductCode");
    miakiSelectToolSpoof ? sel_printf(&menu, "[*] Flash TOOL spoof") : sel_printf(&menu, "[] Flash TOOL spoof");
    miakiDexSpoof ? sel_printf(&menu, "[*] Flash DEX spoof") : sel_printf(&menu, "[] Flash DEX spoof");
    miakiTestSpoof ? sel_printf(&menu, "[*] Flash TEST spoof") : sel_printf(&menu, "[] Flash TEST spoof");
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
            if (menu_edition) {
                switch (menu.selected) {
                    case 0:
						miakiSelectToolSpoof = 1;
                        miakiDexSpoof = 0;
                        miakiTestSpoof = 0;
                        deeper();
                        menu_edition();
                        needs_refresh = 1;
                        break;
                    case 1:
						miakiDexSpoof = 1;
                        miakiToolSpoof = 0;
                        miakiTestSpoof = 0;
                        miakiSelectToolSpoof = 0;
                        menu_edition();
                        needs_refresh = 1;
                        break;
                    case 2:
						miakiTestSpoof = 1;
                        miakiToolSpoof = 0;
                        miakiSelectToolSpoof = 0;
                        miakiDexSpoof = 0;
                        menu_edition();
                        needs_refresh = 1;
                        break;
                }
            } 
        }
		if(key == SCE_CTRL_CIRCLE)
		{
            menu_destroy(&menu);
			main();
		}
        if (needs_refresh) {
            menu_draw(&menu);
        }
        sceKernelDelayThread(10000);
    }
        
}
