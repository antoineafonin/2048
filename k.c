#include "k.h"

#include <stdlib.h>

void add_random_tile(struct game *game) {
    int row, col;
    // find random, but empty tile
    do {
        row = rand() % SIZE;
        col = rand() % SIZE;
    } while (game->board[row][col] != ' ');

    // place to the random position 'A' or 'B' tile
    if (rand() % 2 == 0) {
        game->board[row][col] = 'A';
    } else {
        game->board[row][col] = 'B';
    }
}

bool is_game_won(const struct game game) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (game.board[i][j] == 'K') {
                return true;
            }
        }
    }

    return false;
}

bool is_move_possible(const struct game game) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            char letter = game.board[row][col];

            if (row % 2 != col % 2) continue;

            // check bottom
            if (letter == game.board[row + 1][col] && row < SIZE - 1) {
                return true;
            }

            // check top
            if (letter == game.board[row - 1][col] && row >= 1) {
                return true;
            }

            // check left to right
            if (letter == game.board[row][col + 1] && col < SIZE - 1) {
                return true;
            }

            // check right to left
            if (letter == game.board[row][col - 1] && col >= 1) {
                return true;
            }
        }
    }

    return false;
}