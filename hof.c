#include "hof.h"

#include <stdio.h>

#define MAX_PLAYERS 10

int load(struct player list[]) {
    FILE* hf = fopen(HOF_FILE, "r");
    if (NULL == hf) return -1;

    int get_res;
    struct player player;
    int size = 0;

    while (size < MAX_PLAYERS &&
           (get_res = fscanf(hf, "%s %d", player.name, &player.score)) != EOF) {
        if (get_res != 2) {
            fclose(hf);
            return -1;
        }

        add_player(list, &size, player);
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
    int pos = 0;

    while (pos < *size && list[pos].score > player.score) {
        pos++;
    }

    while (pos < *size && list[pos].score == player.score) {
        pos++;
    }

    if (*size == 10 && pos == 10) {
        return false;
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