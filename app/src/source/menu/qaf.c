/* qaf.c -- QAF Flasher
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
#include "../../include/qaf.h"
#include "../../include/debugsettings.h"

#define printf psvDebugScreenPrintf


void qafmenu(void) {
    int running = 1;
    Menu menu;
    psvDebugScreenClear();
    menu_create(&menu, "QA Flags");
    miakiAllowSceShellFlags ? sel_printf(&menu, "[*] Flash SceShell Flags") : sel_printf(&menu, "[] Flash SceShell Flags");
    miakiAllowDebugFlags ? sel_printf(&menu, "[*] Flash Debug Flags") : sel_printf(&menu, "[] Flash Debug Flags");
    miakiEnableQafQaTeamFullE ? sel_printf(&menu, "[*] Flash QA Flags") : sel_printf(&menu, "[] Flash QA Flags");
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
						miakiAllowSceShellFlags = 1;
                        miakiAllowDebugFlags = 0;
                        miakiEnableQafQaTeamFullE = 0;
                        qafmenu();
                        needs_refresh = 1;
                        break;
                    case 1:
						miakiAllowDebugFlags = 1;
                        miakiAllowSceShellFlags = 0;
                        miakiEnableQafQaTeamFullE = 0;
                        qafmenu();
                        needs_refresh = 1;
                        break;
                    case 2:
						miakiEnableQafQaTeamFullE = 1;
                        miakiAllowSceShellFlags = 0;
                        miakiAllowDebugFlags = 0;
                        qafmenu();
                        needs_refresh = 1;
                        break;
                }
            } 
        }
		if(key == SCE_CTRL_CIRCLE)
		{
            menu_destroy(&menu);
			debugsettings();
		}
        if (needs_refresh) {
            menu_draw(&menu);
        }
        sceKernelDelayThread(10000);
    }
        
}
