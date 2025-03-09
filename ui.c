#include <curses.h>
#include <stdio.h>
#include <string.h>

#include "k.h"

// void render(const struct game game){
//     printf("score: %d\n", game.score);

//     for(int row = 0; row < SIZE; row++){
//         printf("+---+---+---+---+\n|");
//         for(int col = 0; col < SIZE; col++){
//             printf(" %c |", game.board[row][col]);
//         }
//         printf("\n");
//     }
//     printf("+---+---+---+---+\n");
// }

void render(const struct game game) {
    clear();

    char text[20];
    sprintf(text, "Score: %d", game.score);
    mvprintw(1, (COLS - (int)strlen(text)) / 2, "%s", text);

    int cell_width = 6;
    int cell_height = 3;
    int x_start = (COLS - cell_width * SIZE) / 2;
    int y_start = 3;

    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            int x = x_start + col * cell_width;
            int y = y_start + row * cell_height;

            if (game.board[row][col] == ' ')
                attrset(COLOR_PAIR(0));
            else if (game.board[row][col] < 'C')
                attrset(COLOR_PAIR(1));
            else if (game.board[row][col] < 'E')
                attrset(COLOR_PAIR(2));
            else if (game.board[row][col] < 'G')
                attrset(COLOR_PAIR(3));
            else if (game.board[row][col] < 'J')
                attrset(COLOR_PAIR(4));
            else
                attrset(COLOR_PAIR(5));

            mvprintw(y, x, "+-----+");
            mvprintw(y + 1, x, "|     |");
            mvprintw(y + 2, x, "|  %c  |", game.board[row][col]);
            mvprintw(y + 3, x, "|     |");
            mvprintw(y + 4, x, "+-----+");
        }
    }

    refresh();
}