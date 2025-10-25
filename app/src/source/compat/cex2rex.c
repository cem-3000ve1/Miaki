/* cex2rex.c -- cex2rex-mode
 *
 * Copyright (C) 2025 LazyPreview
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <vitasdk.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define printf psvDebugScreenPrintf
#include "../../include/ui.h"
#include "../../include/ctrl.h"
#include "../../include/flasher.h"
#include "../../include/boot.h"
#include "../../include/crconfig.h"

char vercr[] = "Miaki cex2rex-mode";

bool isRexcr() {
    return true;
}


void cex2rexmain(void) {
    Menu menu;
    int miakiAllowUpgrade() {
        if(getFileSize("ux0:TOOL.PUP") > 0)
        {
            return 1;
            sceClibPrintf("[MIAKI]: AllowUpgrade\n");
        } else {
            return 0;
        }
    }
    int allow_upgrade = miakiAllowUpgrade();
    int running = 1;
    menu_create(&menu, vercr);
    if (allow_upgrade) {
        menu_draw(&menu);
        sel_printf(&menu, "Uninstall TestKit Firmware");
        sel_printf(&menu, "Upgrade to a DevTool Firmware");
        sel_printf(&menu, "Change Installation Type");
        sel_printf(&menu, "Exit");
    } else {
        menu_draw(&menu);
        sel_printf(&menu, "Uninstall TestKit Firmware");
        sel_printf(&menu, "Change Installation Type");
        sel_printf(&menu, "Exit");
    }
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
            if (allow_upgrade) {
                switch (menu.selected) {
                    case 0:
                        uninstall();
                        needs_refresh = 1;
                        break;
                    case 1:
                        upgrade();
                        needs_refresh = 1;
                        break;
                    case 2:
                        cex2rexconfig();
                        needs_refresh = 1;
                        break;
                    case 3:
                        sceKernelExitProcess(0);
                        needs_refresh = 1;
                        break;
                }
            } else {
                switch (menu.selected) {
                    case 0:
                        uninstall();
                        needs_refresh = 1;
                        break;
                    case 1:
                        cex2rexconfig();
                        needs_refresh = 1;
                        break;
                    case 2:
                        sceKernelExitProcess(0);
                        needs_refresh = 1;
                        break;
                }
            }
            sceKernelDelayThread(150000);
        }
        if (needs_refresh) {
            menu_draw(&menu);
        }
        sceKernelDelayThread(10000);
    }
    menu_destroy(&menu);
    psvDebugScreenClear(COLOR_BLACK);
    DebugLog("Exiting...\n");
    sceKernelDelayThread(1000000);
    sceKernelExitProcess(0);
    return 0;
}
