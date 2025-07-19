#ifndef UI_H
#define UI_H

void ui_init();
void ui_deinit();
void ui_clear();
void ui_draw_bar(int x, int y, int width, float percent, const char *label);
void ui_refresh();

#endif // UI_H
