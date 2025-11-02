/* main.c -- Main Application
 *
 * Copyright (C) 2025 LazyPreview
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <vitasdk.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define printf psvDebugScreenPrintf
#include "include/debugScreen.h"
#include "include/ui.h"
#include "include/ctrl.h"
#include "include/activation.h"
#include "include/boot_parameters.h"
#include "include/flasher.h"
#include "include/debugsettings.h"
#include "include/boot.h"
#include "include/cex2rex.h"
char ver[] = "Miaki v4.0-dev";

int vshSblAimgrIsCEX(void);
int vshSblAimgrIsDEX(void);
int vshSblAimgrIsTool(void);
int vshSblAimgrIsTest(void);

bool isCexRex() {
    sceClibPrintf("[MIAKI]: Starting Checker phase 1\n");
    int dex = vshSblAimgrIsDEX();
    int spoof = getFileSize("ur0:tai/testkit.skprx") > 0;
    int c2r = getFileSize("ux0:app/CEX2REX20/eboot.bin") > 0;
    int apphome = getFileSize("vs0:app/NPXS10098/sce_sys/param.sfo") > 0;
    if (dex == 1 && spoof && c2r && !apphome)
    {
        return 1;
    } else {
        return 0;
    }
}

bool isRex() {
    sceClibPrintf("[MIAKI]: Starting Checker phase 2\n");

    bool is_cex2rex = isCexRex();
    int apphome = getFileSize("vs0:/app/NPXS10098/sce_sys/param.sfo") > 0;
	int cex = vshSblAimgrIsCEX();
    int dex = vshSblAimgrIsDEX();
	int test = vshSblAimgrIsTest();
	int tool = vshSblAimgrIsTool();
	if(cex)
	{
		return false;
	}

	if(dex)
	{
		if(getFileSize("ur0:tai/testkit.skprx") > 0)
		{
			return 1;
            sceClibPrintf("[MIAKI]: ur0:tai/testkit.skprx isDEX\n");
		}
		else
		{
			return 0;
		} 

        if (isCexRex)
        {
            cex2rexmain();
        }
	}

	if (test || tool)
	{
		return getFileSize("ur0:tai/testkit.skprx") > 0;
	}

	return false;
}

int main() {
    Menu menu;
    bool is_rex = isRex();
    bool is_cexrex = isCexRex();
    if (is_cexrex)
    {
        sceClibPrintf("[MIAKI]: isCEX2REX\n");
        cex2rexmain();
        return 0;
    }
    int running = 1;
    menu_create(&menu, ver);
     if (is_rex) {
        sceClibPrintf("[MIAKI]: isRex\n");
        sel_printf(&menu, "Uninstall TOOL Firmware");
        sel_printf(&menu, "Debug Settings");
        sel_printf(&menu, "Fix the boot configuration");
		sel_printf(&menu, "Apply configuration");
        sel_printf(&menu, "Exit");
    } else {
        sceClibPrintf("[MIAKI]: noTool vsh detected");
        menu_draw(&menu);
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
            if (is_rex) {
                switch (menu.selected) {
                    case 0:
                        uninstall();
                        needs_refresh = 1;
                        break;
                    case 1:
                        debugsettings();
                        needs_refresh = 1;
                        break;
                    case 2:
                        fixboot();
                        needs_refresh = 1;
                        break;
                    case 3:
						checker();
                        apply();
                        needs_refresh = 1;
                        break;
                    case 4:
                        needs_refresh = 0;
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
