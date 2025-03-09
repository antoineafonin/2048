#include <curses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "k.h"
#include "ui.h"

int main() {
    initscr();
    start_color();
    use_default_colors();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    init_pair(0, -1, -1);
    init_pair(1, COLOR_RED, -1);
    init_pair(2, COLOR_GREEN, -1);
    init_pair(3, COLOR_YELLOW, -1);
    init_pair(4, COLOR_BLUE, -1);
    init_pair(5, COLOR_MAGENTA, -1);
    init_pair(6, COLOR_CYAN, -1);

    struct game game = {.board = {{' ', ' ', ' ', ' '},
                                  {' ', ' ', ' ', ' '},
                                  {' ', ' ', ' ', ' '},
                                  {' ', ' ', ' ', ' '}},
                        .score = 0};

    add_random_tile(&game);
    add_random_tile(&game);

    render(game);

    bool quit = false;
    while (!is_game_won(game) && !quit) {
        int ch = getch();

        bool moved = false;

        switch (ch) {
            case KEY_UP:
                moved = update(&game, -1, 0);
                break;
            case KEY_DOWN:
                moved = update(&game, 1, 0);
                break;
            case KEY_LEFT:
                moved = update(&game, 0, -1);
                break;
            case KEY_RIGHT:
                moved = update(&game, 0, 1);
                break;
            case 'q':
            case 'Q':
                quit = true;
                break;
            default:
                break;
        }

        if (moved) {
            add_random_tile(&game);
        }

        if (!is_move_possible(game)) {
            quit = true;
            mvprintw(LINES / 2, COLS / 2 - 5, "Game Over!");
            refresh();
            getch();
        }

        render(game);
    }

    endwin();
    return 0;
}
