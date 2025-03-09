#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <curses.h>

#include "k.h"
#include "ui.h"

int main() {
    initscr();            
    start_color();        
    use_default_colors(); 

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

    bool result = update(&game, 0, 1);
    render(game);
    printf("%d\n", result);

    getch(); 
    endwin(); 
    return 0;
}