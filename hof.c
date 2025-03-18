#include "hof.h"

#include <stdio.h>
#include <string.h>

#define MAX_PLAYERS 10

int load(struct player list[]) {
    FILE* hf = fopen(HOF_FILE, "r");
    if (hf == NULL) return -1;

    int size = 0;
    struct player player;

    while (size < MAX_PLAYERS) {
        int get_res = fscanf(hf, "%31s %d", player.name, &player.score);

        if (get_res == 2) {
            add_player(list, &size, player);
        } else if (get_res == EOF) {
            break;
        } else {
            fclose(hf);
            return -1;
        }
    }

    fclose(hf);
    return size;
}

bool save(const struct player list[], const int size) {
    FILE* hf = fopen(HOF_FILE, "w");

    if (NULL == hf) return false;

    for (int i = 0; i < size; i++) {
        fprintf(hf, "%s %d\n", list[i].name, list[i].score);
    }

    fclose(hf);

    return true;
}

bool add_player(struct player list[], int* size, const struct player player) {
    if (*size == 10 && list[9].score > player.score) {
        return false;
    }

    int pos = 0;

    while (pos < *size) {
        if (list[pos].score < player.score) {
            break;
        } else if (list[pos].score == player.score) {
            if (strcmp(player.name, list[pos].name) < 0) {
                break;
            }
        }
        pos++;
    }

    if (*size < 10) {
        (*size)++;
    }

    for (int i = *size - 1; i > pos; i--) {
        list[i] = list[i - 1];
    }

    list[pos] = player;

    return true;
}

