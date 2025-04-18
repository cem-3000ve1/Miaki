#include <vitasdk.h>
#include <stdio.h>
#include <string.h>

#define printf psvDebugScreenPrintf
#include "debugScreen.h"

#include "ctrl.h"
#include "include/menu/activation.h"
#include "include/menu/boot_parameters.h"
#include "include/flasher.h"

#define COLOR_BLACK 0xFF000000
#define COLOR_WHITE 0xFFFFFFFF
#define COLOR_RED   0xFF0000FF
#define COLOR_GREEN 0xFF00FF00

char ver[] = "Miaki v3.0";

int isRex() {
    return 1;
}

void initScreen() {
    psvDebugScreenInit();
    psvDebugScreenClear(COLOR_BLACK);
    psvDebugScreenSetFgColor(COLOR_WHITE);
}

void drawMenu(int is_rex, int selected) {
    psvDebugScreenClear(COLOR_BLACK);

    psvDebugScreenSetFgColor(COLOR_RED);
    printf("----- MYAPP LOG -----\n");
    psvDebugScreenSetFgColor(COLOR_GREEN);
    printf("Release: Public\n");
    printf("Version: %s\n\n", ver);

    psvDebugScreenSetFgColor(COLOR_WHITE);
    if (is_rex) {
        printf("DevKit fw: Installed\n");
        printf("Release Mode: DevMode\n");
        printf("Activation status: Activated\n");
        printf("%s - Currently REX\n\n", ver);
        printf("  %s Uninstall DevKit Firmware\n", selected == 0 ? "> " : "  ");
        printf("  %s Activation\n", selected == 1 ? "> " : "  ");
        printf("  %s Change ProductCode\n", selected == 2 ? "> " : "  ");
        printf("  %s Release Check Mode\n", selected == 3 ? "> " : "  ");
        printf("  %s Exit\n", selected == 4 ? "> " : "  ");
    } else {
        printf("DevKit fw: Not installed\n");
        printf("%s - Currently CEX\n\n", ver);
        printf("NOTE: Do not install a testkit firmware!\n\n");
        printf("  %s Install DevKit Firmware\n", selected == 0 ? "> " : "  ");
        printf("  %s Exit\n", selected == 1 ? "> " : "  ");
    }

    psvDebugScreenSetFgColor(COLOR_GREEN);
    printf("\nUse UP/DOWN to navigate, CROSS to select\n");
}

int main() {
    initScreen();

    int is_rex = isRex();
    int selected = 0;
    int running = 1;

    drawMenu(is_rex, selected);

    while (running) {
        uint32_t key = get_key(0);

        int needs_refresh = 0;

        if (key == SCE_CTRL_UP) {
            if (selected > 0) {
                selected--;
                needs_refresh = 1;
            }
            sceKernelDelayThread(150000);
        }
        if (key == SCE_CTRL_DOWN) {
            if (is_rex && selected < 4) {
                selected++;
                needs_refresh = 1;
            } else if (!is_rex && selected < 1) {
                selected++;
                needs_refresh = 1;
            }
            sceKernelDelayThread(150000);
        }

        if (key == SCE_CTRL_CROSS) {
            if (is_rex) {
                switch (selected) {
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
                switch (selected) {
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
            drawMenu(is_rex, selected);
        }

        sceKernelDelayThread(10000);
    }

    psvDebugScreenClear(COLOR_BLACK);
    printf("Exiting...\n");
    sceKernelDelayThread(1000000);
    sceKernelExitProcess(0);
    return 0;
}