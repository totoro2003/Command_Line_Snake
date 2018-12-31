#include "console.h"

console::console()
{
    console_hwnd = GetConsoleWindow();

    console_handle = GetStdHandle(STD_OUTPUT_HANDLE);

    GetWindowRect(console_hwnd, &console_rect);

    GetConsoleCursorInfo(console_handle, &cursor_info);
}

int console::get_row_amount()
{
    GetConsoleScreenBufferInfo(console_handle, &console_buffer_info);

    return console_buffer_info.srWindow.Bottom - console_buffer_info.srWindow.Top + 1;
}

int console::get_collumn_amount()
{
    GetConsoleScreenBufferInfo(console_handle, &console_buffer_info);

    return console_buffer_info.dwSize.X;
}

void console::draw_console(int width, int height)
{
    MoveWindow(console_hwnd, console_rect.left, console_rect.top, width, height, true);
}

HANDLE console::get_handle()
{
    return console_handle;
}

HWND console::get_hwnd()
{
    return console_hwnd;
}
