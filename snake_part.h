#ifndef SNAKE_PART_H
#define SNAKE_PART_H

#include <windows.h>

class snake_part
{
public:
    snake_part(HANDLE console_handle);
    void set_position(COORD new_position);
    void set_position(COORD * new_position);
    COORD * get_position();
    int draw();
private:
    COORD * snake_part_position;
    HANDLE console_handle;
};

#endif // SNAKE_PART_H
