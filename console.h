#ifndef CONSOLE_H
#define CONSOLE_H

#define _WIN32_WINNT 0x0500
#include <windows.h>

class console
{
public:
    console();

    int get_row_amount();

    int get_collumn_amount();

    void draw_console(int width, int height);

    HANDLE get_handle();

    HWND get_hwnd();

private:
    HANDLE console_handle;
    HWND console_hwnd;
    RECT console_rect;
    CONSOLE_SCREEN_BUFFER_INFO console_buffer_info;
    CONSOLE_CURSOR_INFO cursor_info;
};

#endif // CONSOLE_H
