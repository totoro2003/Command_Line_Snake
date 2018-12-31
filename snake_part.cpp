#include "snake_part.h"

snake_part::snake_part(HANDLE console_handle)
{
    this->console_handle = console_handle;
}

void snake_part::set_position(COORD new_position)
{
    snake_part_position = &new_position;
}

void snake_part::set_position(COORD * new_position)
{
    snake_part_position = new_position;
}

COORD * snake_part::get_position()
{
    return snake_part_position;
}

int snake_part::draw()
{
    long unsigned garbage = 0;
    return WriteConsoleOutputCharacter
    (
         console_handle,
         "X",
         1,
         *snake_part_position,
         &garbage
    );
}
