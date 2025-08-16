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
#include <taihen.h>
#include "../ui/ui.h"

#include "../../miaki_user.h"

#include "../../ctrl.h"
#include "../../pup.h"
#include "../utils.h"
#include "../menu/activation.h"
#include "../../debugScreen.h"
#define printf psvDebugScreenPrintf

extern int coordX;
extern int coordY;


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
    menu->options = realloc(menu->options, (menu->option_count + 1) * sizeof(MenuOption));
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
    psvDebugScreenClear(COLOR_BLACK);
    psvDebugScreenSetFgColor(COLOR_RED);
    printf("----- %s -----\n", menu->title);
    psvDebugScreenSetFgColor(COLOR_GREEN);
    psvDebugScreenSetFgColor(COLOR_WHITE);
    if (menu->static_line_count > 0) {
        printf("\n");
    }
    for (int i = 0; i < menu->option_count; i++) {
        printf("  %s %s\n", i == menu->selected ? "> " : "  ", menu->options[i].text);
    }
    psvDebugScreenSetFgColor(COLOR_GREEN);
    printf("\nUse UP/DOWN to navigate, CROSS to select\n");
    psvDebugScreenSetFgColor(COLOR_WHITE);
}


void psvDebugScreenSetXY(int x, int y) {
    coordX = x;
    coordY = y;
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