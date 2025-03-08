#include "k.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

void change_score(struct game *game, int row, int col);
char change_letter(char letter);
void move_tile_down(struct game *game, int dx, int row, int col);
void move_tile_up(struct game *game, int dx, int row, int col);
void move_tile_left(struct game *game, int dx, int row, int col);
void move_tile_right(struct game *game, int dx, int row, int col);
bool is_next_letter(const struct game *game, int row, int col);

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

bool update(struct game *game, int dy, int dx) {
    if (dy > 1 || dy < -1 || dx > 1 || dx < -1) return false;
    if (dy == 0 && dx == 0) return false;
    if (dx != 0 && dy != 0) return 0;

    bool horizontal_move = dx != 0;
    // bool vertical_move = dy != 0;

    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (horizontal_move) {
                // move right
                if (dx == 1) {
                    move_tile_right(game, dx, row, col);
                }
                // move left
                if (dx == -1) {
                    move_tile_left(game, dx, row, col);
                }
                // move up
                if (dy == 1) {
                    move_tile_up(game, dx, row, col);
                }
                // move down
                if (dy == 1) {
                    move_tile_down(game, dx, row, col);
                }
            }
        }
    }

    return true;
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
            if (game.board[row][col] == ' ') return true;

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

void move_tile_right(struct game *game, int dx, int row, int col) {
    const struct game temp_game = *game;

    char board[SIZE][SIZE];
    memcpy(board, temp_game.board, sizeof(board));

    if (is_move_possible(temp_game)) {
        while (col != SIZE - 1) {
            game->board[row][col + 1] = game->board[row][col];

            if (is_next_letter(game, row, col + 1)) {
                change_letter(game->board[row][col]);
                change_score(game, row, col);
            }

            game->board[row][col] = ' ';
        }
    }
}

void move_tile_left(struct game *game, int dx, int row, int col) {
    const struct game temp_game = *game;

    char board[SIZE][SIZE];
    memcpy(board, temp_game.board, sizeof(board));

    if (is_move_possible(temp_game)) {
        while (col != SIZE - 1) {
            game->board[row][col - 1] = game->board[row][col];

            if (is_next_letter(game, row, col - 1)) {
                change_letter(game->board[row][col]);
                change_score(game, row, col);
            }

            game->board[row][col] = ' ';
        }
    }
}

void move_tile_up(struct game *game, int dx, int row, int col) {
    const struct game temp_game = *game;

    char board[SIZE][SIZE];
    memcpy(board, temp_game.board, sizeof(board));

    if (is_move_possible(temp_game)) {
        while (col != SIZE - 1) {
            game->board[row + 1][col] = game->board[row][col];

            if (is_next_letter(game, row + 1, col)) {
                change_letter(game->board[row][col]);
                change_score(game, row, col);
            }

            game->board[row][col] = ' ';
        }
    }
}

void move_tile_down(struct game *game, int dx, int row, int col) {
    const struct game temp_game = *game;

    char board[SIZE][SIZE];
    memcpy(board, temp_game.board, sizeof(board));

    if (is_move_possible(temp_game)) {
        while (col != SIZE - 1) {
            game->board[row - 1][col] = game->board[row][col];

            if (is_next_letter(game, row - 1, col)) {
                change_letter(game->board[row][col]);
                change_score(game, row, col);
            }

            game->board[row][col] = ' ';
        }
    }
}

bool is_next_letter(const struct game *game, int row, int col) {
    if (game->board[row][col] >= 'A' && game->board[row - 1][col] <= 'Z') {
        return true;
    }
    if (game->board[row][col] >= 'a' && game->board[row - 1][col] <= 'z') {
        return true;
    }

    return false;
}

void change_score(struct game *game, int row, int col) {
    if (game->board[row][col] == 'A') {
        game->score += 2;
    }
    if (game->board[row][col] == 'B') {
        game->score += pow(2, 2);
    }
    if (game->board[row][col] == 'C') {
        game->score += pow(2, 3);
    }
    if (game->board[row][col] == 'D') {
        game->score += pow(2, 4);
    }
    if (game->board[row][col] == 'E') {
        game->score += pow(2, 5);
    }
    if (game->board[row][col] == 'F') {
        game->score += pow(2, 6);
    }
    if (game->board[row][col] == 'G') {
        game->score += pow(2, 7);
    }
    if (game->board[row][col] == 'H') {
        game->score += pow(2, 8);
    }
    if (game->board[row][col] == 'I') {
        game->score += pow(2, 9);
    }
    if (game->board[row][col] == 'J') {
        game->score += pow(2, 10);
    }
    if (game->board[row][col] == 'K') {
        game->score += pow(2, 11);
    }
}

char change_letter(char letter) {
    if (letter == 'Z') {
        return 'A';
    } else if (letter == 'z') {
        return 'a';
    } else {
        return letter + 1;
    }
}
