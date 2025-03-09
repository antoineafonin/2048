#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "k.h"
#include "ui.h"

int main() {
    // move right
    struct game game = {.board = {{'A', ' ', ' ', ' '},
                                  {'B', ' ', ' ', 'B'},
                                  {'C', 'C', 'C', ' '},
                                  {'D', 'D', 'D', 'D'}},
                        .score = 0};

    bool result = update(&game, 0, 1);
    /*
    game = {
        .board = {
            {' ', ' ', ' ', 'A'},
            {' ', ' ', ' ', 'C'},
            {' ', ' ', 'C', 'D'},
            {' ', ' ', 'E', 'E'}
        },
        .score = 88
    };
    result = true;
    */

    render(game);

    printf("%d\n", result);
    return 0;
}