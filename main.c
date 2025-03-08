#include <stdio.h>
#include <string.h>

#include "k.h"

int main() {
    struct game game = {.board = {{'A', 'B', 'C', 'D'},
                                  {'E', 'F', 'G', 'H'},
                                  {'I', 'J', 'K', 'A'},
                                  {'B', 'C', 'D', 'E'}},
                        .score = 0};

    printf("is won: %d\n", is_game_won(game));

    return 0;
}