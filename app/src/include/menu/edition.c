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
#include "../ui/ui.h"

#include "../../miaki_user.h"

#include "../../ctrl.h"
#include "../../pup.h"
#include "../utils.h"
#include "edition.h"

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
    sel_printf(&menu, "Flash TOOL spoof");
    sel_printf(&menu, "Flash DEX spoof");
    sel_printf(&menu, "Flash TEST spoof");
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
                        DebugLog("TOOL spoof");
                        CopyFile("app0:/dev_vita.skprx", "ur0:tai/testkit.skprx");
                        scePowerRequestColdReset();        
                        needs_refresh = 1;
                        break;
                    case 1:
                        DebugLog("DEX spoof");
                        CopyFile("app0:/testkit_vita.skprx", "ur0:tai/testkit.skprx");
                        scePowerRequestColdReset();
                        needs_refresh = 1;
                        break;
                    case 2:
                        DebugLog("TEST spoof");
                        CopyFile("app0:/pro_vita.skprx", "ur0:tai/testkit.skprx");
                        scePowerRequestColdReset();
                        needs_refresh = 1;
                        break;
                }
            } 
        }
        if (needs_refresh) {
            menu_draw(&menu);
        }
        sceKernelDelayThread(10000);
    }
        
}
