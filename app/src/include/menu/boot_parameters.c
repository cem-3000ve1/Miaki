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
#include "../ui/ui.h"

#include "../../miaki_user.h"

#include "../../ctrl.h"
#include "../../pup.h"
#include "../utils.h"
#include "boot_parameters.h"

#define printf psvDebugScreenPrintf

void boot_parameters(void) {
    int running = 1;
    Menu menu;
    psvDebugScreenClear();
    menu_create(&menu, "Release Check Mode");
    if (devmodeii)
    {
        sel_printf(&menu, "[*] Development Mode");
    }
    else
    {
        sel_printf(&menu, "[] Development Mode");
    }

    if (ReleaseMode)
    {
        sel_printf(&menu, "[*] Release Mode");
    }
    else
    {
        sel_printf(&menu, "[] Release Mode");
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
            if (boot_parameters) {
                switch (menu.selected) {
                    case 0:
						devmodeii = 1;
                        ReleaseMode = 0;
                        boot_parameters();
                        needs_refresh = 1;
                        break;
                    case 1:
						ReleaseMode = 1;
                        devmodeii = 0;
                        boot_parameters();
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
