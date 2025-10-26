/* idu.c -- IDU Activator
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
#include "../../include/idu.h"

#define printf psvDebugScreenPrintf

void idumenu(void) {
    Menu menu;
    int running = 1;
    psvDebugScreenClear();
    menu_create(&menu, "IDU Menu");
    miakiEnableIDU ? sel_printf(&menu, "[*] Enable IDU mode") : sel_printf(&menu, "[] Enable IDU mode");
    miakiClearIDU ? sel_printf(&menu, "[*] Disable IDU mode") : sel_printf(&menu, "[] Disable IDU mode");
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
            if (idumenu) {
                switch (menu.selected) {
                    case 0:
						miakiEnableIDU = 1;
                        miakiClearIDU = 0;
                        idumenu();
                        needs_refresh = 1;
						break;
                    case 1:
						miakiClearIDU = 1;
                        miakiEnableIDU = 0;
                        idumenu();
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
