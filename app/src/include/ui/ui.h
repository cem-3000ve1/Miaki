#ifndef UI_H
#define UI_H

#include <vitasdk.h>

#define COLOR_BLACK 0xFF000000
#define COLOR_WHITE 0xFFFFFFFF
#define COLOR_RED   0xFF0000FF
#define COLOR_GREEN 0xFF00FF00

typedef struct {
    const char *text;
} MenuOption;

typedef struct {
    const char *title;
    const char *version;
    MenuOption *options;
    int option_count;
    int selected;
    const char **static_lines;
    int static_line_count;
} Menu;

void menu_create(Menu *menu, const char *title);
void sel_printf(Menu *menu, const char *text);
void menu_printf(Menu *menu, const char *text);
void menu_draw(Menu *menu);
void menu_destroy(Menu *menu);

#endif