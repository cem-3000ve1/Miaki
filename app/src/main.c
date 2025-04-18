#include <vitasdk.h>
#include <stdio.h>
#include <string.h>

#define printf psvDebugScreenPrintf
#include "debugScreen.h"
#include "include/ui/ui.h"
#include "ctrl.h"
#include "include/menu/activation.h"
#include "include/menu/boot_parameters.h"
#include "include/flasher.h"

char ver[] = "Miaki v3.0.0-internal";

int isRex() {
    return 1;
}

int main() {
    Menu menu;
    int is_rex = isRex();
    int running = 1;
    menu_create(&menu, ver);
    if (is_rex) {
		menu_printf(&menu, "Test very sigma");
        sel_printf(&menu, "Uninstall DevKit Firmware");
        sel_printf(&menu, "Activation");
        sel_printf(&menu, "Change ProductCode");
        sel_printf(&menu, "Release Check Mode");
        sel_printf(&menu, "Exit");
    } else {
        sel_printf(&menu, "Install DevKit Firmware");
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
                        activator();
                        needs_refresh = 1;
                        break;
                    case 2:
                        menu_edition();
                        needs_refresh = 1;
                        break;
                    case 3:
                        boot_parameters();
                        needs_refresh = 1;
                        break;
                    case 4:
                        running = 0;
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
    printf("Exiting...\n");
    sceKernelDelayThread(1000000);
    sceKernelExitProcess(0);
    return 0;
}