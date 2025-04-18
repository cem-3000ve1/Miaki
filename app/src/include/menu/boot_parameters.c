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
    sel_printf(&menu, "Development Mode");
    sel_printf(&menu, "Release Mode");
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
                        DebugLog("Development Mode");
                        CopyFile("app0:/devmode.skprx", "ur0:tai/devmode.skprx");
                        scePowerRequestColdReset();        
                        needs_refresh = 1;
                        break;
                    case 1:
                        DebugLog("Release Mode");
                        sceIoRemove("ur0:tai/devmode.skprx");
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
