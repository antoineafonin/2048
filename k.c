#include "k.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

void change_score(struct game *game, int row, int col);
char change_letter(char letter);
bool is_next_letter(const struct game *game, int row, int col);

bool update(struct game *game, int dy, int dx) {
    if (dy > 1 || dy < -1 || dx > 1 || dx < -1) return false;
    if (dy == 0 && dx == 0) return false;
    if (dx != 0 && dy != 0) return false;

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
                        game->board[row][next_col] = ' ';
                        next_col++;
                        moved = true;
                    }
                    if (next_col < SIZE - 1 &&
                        game->board[row][next_col + 1] ==
                            game->board[row][next_col] &&
                        !merged[row][next_col + 1]) {
                        game->board[row][next_col + 1] =
                            change_letter(game->board[row][next_col]);
                        game->board[row][next_col] = ' ';
                        merged[row][next_col + 1] = true;
                        moved = true;
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
                        game->board[row][next_col] = ' ';
                        next_col--;
                        moved = true;
                    }
                    if (next_col > 0 &&
                        game->board[row][next_col - 1] ==
                            game->board[row][next_col] &&
                        !merged[row][next_col - 1]) {
                        game->board[row][next_col - 1] =
                            change_letter(game->board[row][next_col]);
                        game->board[row][next_col] = ' ';
                        merged[row][next_col - 1] = true;
                        moved = true;
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
                        game->board[next_row][col] = ' ';
                        next_row++;
                        moved = true;
                    }
                    if (next_row < SIZE - 1 &&
                        game->board[next_row + 1][col] ==
                            game->board[next_row][col] &&
                        !merged[next_row + 1][col]) {
                        game->board[next_row + 1][col] =
                            change_letter(game->board[next_row][col]);
                        game->board[next_row][col] = ' ';
                        merged[next_row + 1][col] = true;
                        moved = true;
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
                        game->board[next_row - 1][col] =
                            game->board[next_row][col];
                        game->board[next_row][col] = ' ';
                        next_row--;
                        moved = true;
                    }
                    if (next_row > 0 &&
                        game->board[next_row - 1][col] ==
                            game->board[next_row][col] &&
                        !merged[next_row - 1][col]) {
                        game->board[next_row - 1][col] =
                            change_letter(game->board[next_row][col]);
                        game->board[next_row][col] = ' ';
                        merged[next_row - 1][col] = true;
                        moved = true;
                    }
                }
            }
        }
    }

    return moved;
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

            if (row < SIZE - 1 && letter == game.board[row + 1][col]) {
                return true;
            }
            if (row >= 1 && letter == game.board[row - 1][col]) {
                return true;
            }
            if (col < SIZE - 1 && letter == game.board[row][col + 1]) {
                return true;
            }
            if (col >= 1 && letter == game.board[row][col - 1]) {
                return true;
            }
        }
    }
    return false;
}

void move_tile_right(struct game *game, int dx, int row, int col) {
    while (col < SIZE - 1 && game->board[row][col + 1] == ' ') {
        game->board[row][col + 1] = game->board[row][col];
        game->board[row][col] = ' ';
        col++;
    }
}

void move_tile_left(struct game *game, int dx, int row, int col) {
    while (col > 0 && game->board[row][col - 1] == ' ') {
        game->board[row][col - 1] = game->board[row][col];
        game->board[row][col] = ' ';
        col--;
    }
}

void move_tile_up(struct game *game, int dx, int row, int col) {
    while (row > 0 && game->board[row - 1][col] == ' ') {
        game->board[row - 1][col] = game->board[row][col];
        game->board[row][col] = ' ';
        row--;
    }
}

void move_tile_down(struct game *game, int dx, int row, int col) {
    while (row < SIZE - 1 && game->board[row + 1][col] == ' ') {
        game->board[row + 1][col] = game->board[row][col];
        game->board[row][col] = ' ';
        row++;
    }
}

bool is_next_letter(const struct game *game, int row, int col) {
    return (game->board[row][col] >= 'A' && game->board[row][col] <= 'Z') ||
           (game->board[row][col] >= 'a' && game->board[row][col] <= 'z');
}

void change_score(struct game *game, int row, int col) {
    game->score += pow(2, game->board[row][col] - 'A' + 1);
}

char change_letter(char letter) {
    return (letter == 'Z' || letter == 'z') ? 'A' : letter + 1;
}
