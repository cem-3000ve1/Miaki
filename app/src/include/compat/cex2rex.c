/* cex2rex.c -- cex2rex-mode
 *
 * Copyright (C) 2025 LazyPreview
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <vitasdk.h>
#include <stdio.h>
#include <string.h>

#define printf psvDebugScreenPrintf
#include "../ui/ui.h"
#include "../../ctrl.h"
#include "../flasher.h"
#include "../flasher/boot.h"
#include "config.h"

char vercr[] = "Miaki cex2rex-mode";
int isRexcr() {
    return 1;
}

void cex2rexmain(void) {
    Menu menu;
    int is_rexcr = isRexcr();
    int running = 1;
    menu_create(&menu, vercr);
    if (is_rexcr) {
        sel_printf(&menu, "Uninstall TestKit Firmware");
        sel_printf(&menu, "Upgrade to a DevTool Firmware");
        sel_printf(&menu, "Change Installation Type");
        sel_printf(&menu, "Exit");
    } else {
        sel_printf(&menu, "Install TOOL Firmware");
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
            if (is_rexcr) {
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
                        install();
                        needs_refresh = 1;
                        break;
                    case 1:
                        running = 0;
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
