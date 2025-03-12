#include "k.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

void change_score(struct game *game, int row, int col);
char change_letter(char letter);
bool is_game_won(const struct game game);
bool is_move_possible(const struct game game);
bool is_before_tile_hor(const struct game *game);
bool is_before_tile_ver(const struct game *game);
void change_tile(struct game *game, int row, int col);

void add_random_tile(struct game *game) {
    int row, col;
    do {
        row = rand() % SIZE;
        col = rand() % SIZE;
    } while (game->board[row][col] != ' ');

    if (rand() % 2 == 0) {
        game->board[row][col] = 'A';
    } else {
        game->board[row][col] = 'B';
    }
}

bool update(struct game *game, int dy, int dx) {
    if (dy > 1 || dy < -1 || dx > 1 || dx < -1) return false;
    if (dy == 0 && dx == 0) return false;
    if (dx != 0 && dy != 0) return false;
    if (!is_move_possible(*game)) return false;

    bool moved = false;
    bool merged[SIZE][SIZE] = {{false}};

    if (dx == 1) {  // move right
        for (int row = 0; row < SIZE; row++) {
            for (int col = SIZE - 2; col >= 0; col--) {
                if (game->board[row][col] != ' ') {
                    int next_col = col;
                    while (next_col < SIZE - 1 &&
                           game->board[row][next_col + 1] == ' ') {
                        game->board[row][next_col + 1] =
                            game->board[row][next_col];
                        change_tile(game, row, next_col);
                        next_col++;
                        moved = true;
                    }
                    if (next_col < SIZE - 1 &&
                        game->board[row][next_col + 1] ==
                            game->board[row][next_col] &&
                        !merged[row][next_col + 1]) {
                        game->board[row][next_col + 1] =
                            change_letter(game->board[row][next_col]);
                        change_tile(game, row, next_col);
                        merged[row][next_col + 1] = true;
                        moved = true;
                        change_score(game, row, next_col + 1);
                    }
                }
            }
        }
    } else if (dx == -1) {  // move left
        for (int row = 0; row < SIZE; row++) {
            for (int col = 1; col < SIZE; col++) {
                if (game->board[row][col] != ' ') {
                    int next_col = col;
                    while (next_col > 0 &&
                           game->board[row][next_col - 1] == ' ') {
                        game->board[row][next_col - 1] =
                            game->board[row][next_col];
                        change_tile(game, row, next_col);
                        next_col--;
                        moved = true;
                    }
                    if (next_col > 0 &&
                        game->board[row][next_col - 1] ==
                            game->board[row][next_col] &&
                        !merged[row][next_col - 1]) {
                        game->board[row][next_col - 1] =
                            change_letter(game->board[row][next_col]);
                        change_tile(game, row, next_col);
                        merged[row][next_col - 1] = true;
                        moved = true;
                        change_score(game, row, next_col - 1);
                    }
                }
            }
        }
    } else if (dy == 1) {  // move down
        for (int col = 0; col < SIZE; col++) {
            for (int row = SIZE - 2; row >= 0; row--) {
                if (game->board[row][col] != ' ') {
                    int next_row = row;
                    while (next_row < SIZE - 1 &&
                           game->board[next_row + 1][col] == ' ') {
                        game->board[next_row + 1][col] =
                            game->board[next_row][col];
                        change_tile(game, next_row, col);
                        next_row++;
                        moved = true;
                    }
                    if (next_row < SIZE - 1 &&
                        game->board[next_row + 1][col] ==
                            game->board[next_row][col] &&
                        !merged[next_row + 1][col]) {
                        game->board[next_row + 1][col] =
                            change_letter(game->board[next_row][col]);
                        change_tile(game, next_row, col);
                        merged[next_row + 1][col] = true;
                        moved = true;
                        change_score(game, next_row + 1, col);
                    }
                }
            }
        }
    } else if (dy == -1) {  // move up
        for (int col = 0; col < SIZE; col++) {
            for (int row = 1; row < SIZE; row++) {
                if (game->board[row][col] != ' ') {
                    int next_row = row;
                    while (next_row > 0 &&
                           game->board[next_row - 1][col] == ' ') {
                        game->board[next_row - 1][col] = game->board[row][col];
                        change_tile(game, row, col);
                        next_row--;
                        moved = true;
                    }
                    if (next_row > 0 &&
                        game->board[next_row - 1][col] ==
                            game->board[next_row][col] &&
                        !merged[next_row - 1][col]) {
                        game->board[next_row - 1][col] =
                            change_letter(game->board[next_row][col]);
                        change_tile(game, next_row, col);
                        merged[next_row - 1][col] = true;
                        moved = true;
                        change_score(game, next_row - 1, col);
                    }
                }
            }
        }
    }

    if (is_game_won(*game)) {
        return true;
    }

    if (moved) {
        add_random_tile(game);
    }

    return moved;
}

char change_letter(char letter) {
    if (letter >= 'A' && letter < 'K') {
        return letter + 1;
    }
    return letter;
}

void change_score(struct game *game, int row, int col) {
    char letter = game->board[row][col];
    if (letter >= 'A' && letter <= 'K') {
        int value = 1 << (letter - 'A' + 1);
        game->score += value;
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

            if (letter == ' ') return true;

            if (col < SIZE - 1 && letter == game.board[row][col + 1]) {
                return true;
            }
            if (col > 0 && letter == game.board[row][col - 1]) {
                return true;
            }

            if (row < SIZE - 1 && letter == game.board[row + 1][col]) {
                return true;
            }
            if (row > 0 && letter == game.board[row - 1][col]) {
                return true;
            }
        }
    }
    return false;
}

bool is_before_tile_hor(const struct game *game) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 1; col < SIZE; col++) {
            if (game->board[row][col - 1] >= 'A' &&
                game->board[row][col - 1] <= 'Z') {
                return true;
            }
        }
    }
    return false;
}

bool is_before_tile_ver(const struct game *game) {
    for (int row = 1; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (game->board[row - 1][col] >= 'A' &&
                game->board[row - 1][col] <= 'Z') {
                return true;
            }
        }
    }
    return false;
}

void change_tile(struct game *game, int row, int col) {
    if (is_before_tile_hor(game) || is_before_tile_ver(game)) {
        game->board[row][col] = ' ';
    }
}