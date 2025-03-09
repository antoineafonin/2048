#include <curses.h>
#include <stdbool.h>

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

    struct game game = {.board = {{'A', ' ', ' ', ' '},
                                  {'B', ' ', ' ', 'B'},
                                  {'C', 'C', 'C', ' '},
                                  {'D', 'D', 'D', 'D'}},
                        .score = 0};

    render(game);
    bool quit = false;
    while (!quit) {
        int ch = getch();

        switch (ch) {
            case KEY_UP:
                update(&game, -1, 0);
                break;
            case KEY_DOWN:
                update(&game, 1, 0);
                break;
            case KEY_LEFT:
                update(&game, 0, -1);
                break;
            case KEY_RIGHT:
                update(&game, 0, 1);
                break;
            case 'q':
            case 'Q':
                quit = true;
                break;
            default:
                break;
        }
        render(game);
    }

    endwin();
    return 0;
}
