#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include "console.h"
#include "snake_part.h"

//overloading the == operator
//for the COORD so that STD::find
//works correctly

bool operator==(COORD a, COORD b)
{
    return a.X == b.X && a.Y == b.Y;
}

void end_game(int score, int collumn_amount, int row_amount)
{
    system("CLS");

    std::string text = "Score: " + std::to_string(score);

    console console_window;

    COORD middle_coordinates;

    middle_coordinates.X = console_window.get_collumn_amount() / 2 - text.size() / 2;

    middle_coordinates.Y = console_window.get_row_amount() / 2;

    //the cursor is set in the middle of the screen
    SetConsoleCursorPosition(console_window.get_handle(), middle_coordinates);

    std::cout << text;

    getch();

    exit(0);
}

int main()
{
    //setting up and opening window
    const int console_width = 500;

    const int console_height = 500;

    const int fps = 30;

    console console_window;

    HANDLE console_handle = console_window.get_handle();

    console_window.draw_console(console_width, console_height);

    const int collumn_amount = console_window.get_collumn_amount();

    const int row_amount = console_window.get_row_amount();

    //game loop

    bool game = true;

    COORD head_coordinates;

    head_coordinates.X = collumn_amount / 2;

    head_coordinates.Y = row_amount / 2;

    //default direction is up

    SHORT * direction = &head_coordinates.Y;

    int increase_by = -1;

    //the game starts with 5 body parts
    int body_part_amount = 5;

    std::vector<COORD> head_positions;

    COORD food_coordinates;

    food_coordinates.X = rand() % collumn_amount;

    food_coordinates.Y = rand() % row_amount;

    while (game)
    {
        const int impalpable_body_parts = 3;
        //the first 3 body parts are impossible to touch
        if
            (
                //checks if you touch the barriers
                (
                    head_coordinates.X < 0 || head_coordinates.Y < 0
                )

                ||

                (
                    head_coordinates.X >= console_window.get_collumn_amount()
                    ||
                    head_coordinates.Y >= console_window.get_row_amount()
                )
            )
        {
            //..the game ends
            end_game(body_part_amount, collumn_amount, row_amount);
        }

        //drawing snake head

        snake_part head(&console_handle);

        head.set_position(&head_coordinates);

        std::cout << "Score: " << head_positions.size() << " -BOUNDARY-\n";

        *direction += increase_by;

        head_positions.insert(head_positions.begin(), head_coordinates);

        if (head_positions.size() > body_part_amount)
        {
            head_positions.erase(head_positions.end() - 1);
        }

        for (int iter = head_positions.size() - 1; iter > 0; iter--)
        {
            snake_part newest_snake_part(&console_handle);

            newest_snake_part.set_position(&head_positions[iter]);

            //if the snake touches itself, the game ends
            if (head_positions[iter] == head_coordinates)
            {
                end_game(body_part_amount, collumn_amount, row_amount);
            }

            newest_snake_part.draw();
        }

        head.draw();

        //snake controls

        if (kbhit())
        {
                switch(getch())
                {
                case 'w':
                    if (!(*direction == head_coordinates.Y))
                    {
                        direction = &head_coordinates.Y;
                        increase_by = -1;
                    }
                    break;
                case 's':
                    if (!(*direction == head_coordinates.Y))
                    {
                        direction = &head_coordinates.Y;
                        increase_by = 1;
                    }
                    break;
                case 'a':
                    if (!(*direction == head_coordinates.X))
                    {
                        direction = &head_coordinates.X;
                        increase_by = -1;
                    }
                    break;
                case 'd':
                    if (!(*direction == head_coordinates.X))
                    {
                        direction = &head_coordinates.X;
                        increase_by = 1;
                    }
                    break;
                case 'p':

                    while (getch() != 'p');

                    break;
                }
        }
        //drawing food

        long unsigned garbage = 0;
        WriteConsoleOutputCharacter
        (
            console_handle,
            "O",
            1,
            food_coordinates,
            &garbage
        );

        //redrawing food in case the player eats it

        if (head_coordinates == food_coordinates)
        {
            body_part_amount++;
            food_coordinates.X = rand() % collumn_amount;
            food_coordinates.Y = rand() % row_amount;
        }



        const int one_second = 1000;

        Sleep(one_second/fps);

        system("CLS");
    }

    getchar();

    return 0;
}
