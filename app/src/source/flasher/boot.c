#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <vitasdk.h>
#include <taihen.h>

#include "../../include/miaki_user.h"

#include "../../include/ctrl.h"
#include "../../include/pup.h"
#include "../../include/flasher.h"
#include "../../include/utils.h"
#include "../../include/modules.h"
#include "../../include/ui.h"
#define printf psvDebugScreenPrintf

void fixboot(void)
{
	int running = 1;
	Menu menu;
	psvDebugScreenClear();
	menu_create(&menu, "Are you sure?");
	sel_printf(&menu, "Yes");
	sel_printf(&menu, "No");
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
			if (fixboot) {
				switch (menu.selected) {
					case 0:
						fixbootyes();
						needs_refresh = 1;
						break;
					case 1:
						main();
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

void fixbootyes()
{
	psvDebugScreenClear();
	DebugLog("Fixing the boot configuration...");
	CopyFile("app0:/testkit_vita.skprx", "ur0:tai/testkit.skprx");
	CopyFile("app0:/vitaConfig.txt", "ur0:tai/boot_config.txt");
	scePowerRequestColdReset();
}
