/* ui.c -- User Interface 
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
#include <stdbool.h>
#include <taihen.h>
#include "../../include/ui.h"

#include "../../include/miaki_user.h"

#include "../../include/ctrl.h"
#include "../../include/pup.h"
#include "../../include/utils.h"
#include "../../include/activation.h"
#define printf psvDebugScreenPrintf

int debug = 0;
extern int coordX;
extern int coordY;
int vshSblAimgrIsCEX(void);
int vshSblAimgrIsDEX(void);
int vshSblAimgrIsTool(void);
int vshSblAimgrIsTest(void);

bool isKmsInstalled() {
    return getFileSize("ur0:tai/kmspico.skprx") > 0;
}

bool isDevmodeInstalled() {
    return getFileSize("ur0:tai/devmode.skprx") > 0;
}

static void initScreen() {
    psvDebugScreenInit();
    psvDebugScreenClear(COLOR_BLACK);
    psvDebugScreenSetFgColor(COLOR_WHITE);
}

void menu_create(Menu *menu, const char *title) {
    initScreen();
    menu->title = title;
    //menu->version = version;
    //menu->status = status;
    menu->options = 0;
    menu->option_count = 0;
    menu->selected = 0;
    menu->static_lines = NULL;
    menu->static_line_count = 0;
}

void sel_printf(Menu *menu, const char *text) {
    menu->options = realloc(menu->options, (menu->option_count + 1) *
    sizeof(MenuOption));
    if (!menu->options) {
        return;
    }
    menu->options[menu->option_count].text = text;
    menu->option_count++;
}

void menu_printf(Menu *menu, const char *text) {
    menu->static_lines = realloc(menu->static_lines, (menu->static_line_count + 1) * sizeof(const char *));
    if (!menu->static_lines) {
        return;
    }
    menu->static_lines[menu->static_line_count] = text;
    menu->static_line_count++;
}

void menu_draw(Menu *menu) {
    int release_check = isDevmodeInstalled();
    bool is_cex2rex = isCexRex();
    bool act_ui = isKmsInstalled();
    int cex = vshSblAimgrIsCEX();
    int dex = vshSblAimgrIsDEX();
    int test = vshSblAimgrIsTest();
    int tool = vshSblAimgrIsTool();
    psvDebugScreenClear(COLOR_BLACK);
    psvDebugScreenSetFgColor(COLOR_RED);
    printf("----- %s -----\n", menu->title);
    psvDebugScreenSetFgColor(COLOR_GREEN);
    psvDebugScreenSetFgColor(COLOR_WHITE);
    if (menu->static_line_count > 0) {
        printf("\n");
    }
    for (int i = 0; i < menu->option_count; i++) {
        printf("  %s %s\n", i == menu->selected ? "--> " : "  ", menu->options[i].text);
    }
    psvDebugScreenSetFgColor(COLOR_GREEN);
    printf("\nUse UP/DOWN to navigate, CROSS to select\n");
    psvDebugScreenSetFgColor(COLOR_PURPLE);
    if (debug) {
    printf("System information: \n\n");
    if (tool == 1)
    {
        printf("ProductCode: TOOL\n");
    }
    if (dex == 1)
    {
        printf("ProductCode: DEX\n");
    }
    if (test == 1)
    {
        printf("ProductCode: TEST\n");
    }

     act_ui ? printf("Activation: Activated\n") : printf("Activation: Expired\n");
     release_check ? printf("ReleaseCheckMode: Development Mode") : printf("ReleaseCheckMode: Release Mode");
  }
    psvDebugScreenSetFgColor(COLOR_WHITE);
}


void menu_destroy(Menu *menu) {
    if (menu->options) {
        free(menu->options);
        menu->options = NULL;
    }
    if (menu->static_lines) {
        free(menu->static_lines);
        menu->static_lines = NULL;
    }
    menu->option_count = 0;
    menu->static_line_count = 0;
}
