/* boot_parameters.c -- Boot Parameters
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
#include "../../include/boot_parameters.h"

#define printf psvDebugScreenPrintf

void debugsettings(void) {
    int running = 1;
    Menu menu;
    psvDebugScreenClear();
    menu_create(&menu, "Advanced Settings");
    sel_printf(&menu, "Boot Parameters");
    sel_printf(&menu, "Activation");
    sel_printf(&menu, "ProductCode switcher");
    sel_printf(&menu, "IDU Mode Activator");
    sel_printf(&menu, "QAF Flasher");
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
            if (debugsettings) {
                switch (menu.selected) {
                    case 0:
                        boot_parameters();
                        needs_refresh = 1;
                        break;
                    case 1:
                        activator();
                        needs_refresh = 1;
                        break;
                    case 2:
                        menu_edition();
                        needs_refresh = 1;
                        break;
                    case 3:
                        idumenu();
                        needs_refresh = 1;
                        break;
                    case 4:
                        qafmenu();
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
