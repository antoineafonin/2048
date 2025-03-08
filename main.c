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

    struct game game1 = {.board = {{'A', 'A', 'C', 'D'},
                                   {'A', 'F', 'G', 'H'},
                                   {'I', 'J', 'J', 'A'},
                                   {'B', 'C', 'D', 'E'}},
                         .score = 0};

    printf("is move possible: %d\n", is_move_possible(game1));
    // stdout: 1

    struct game gam2 = {
        .board = {
            {'A', 'B', 'C', 'D'},
            {'E', 'F', 'G', 'H'},
            {'I', 'J', 'K', 'A'},
            {'B', 'C', 'D', 'E'}
        },
        .score = 0
    };
    
    printf("is move possible: %d\n", is_move_possible(gam2));
    // stdout: 0

    return 0;
}