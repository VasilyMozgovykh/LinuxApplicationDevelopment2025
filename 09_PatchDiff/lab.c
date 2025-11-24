#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_INIT_RETRIES 100
#define NUM_RANDOM_PERMUTATIONS 6

#define WALL_CHAR ('#')
#define PASSAGE_CHAR ('.')

void spawn_initial_labirinth(char **labirinth, int is_new);

void fill_initial_labirinth(char *labirinth);

char *get_labirinth(void);

void print_labirinth(char *labirinth);

int main(void) {
    srand(time(NULL));

    char *labirinth = get_labirinth();
    if (labirinth == NULL) {
        fprintf(stderr, "Can't allocate memory for labirinth\n");
        return 1;
    }
    print_labirinth(labirinth);
    free(labirinth);
    return 0;
}

void fill_initial_labirinth(char *labirinth) {
    int str_size = 13;
    memset(labirinth, WALL_CHAR, str_size * str_size * sizeof(*labirinth));
    for (int i = 1; i < str_size; i += 2) {
        for (int j = 1; j < str_size; j += 2) {
            labirinth[i * str_size + j] = PASSAGE_CHAR;
        }
    }
}

void spawn_initial_labirinth(char **labirinth, int is_new) {
    int str_size = 13;
    if (is_new) {
        *labirinth = (char *) malloc(str_size * str_size * sizeof(*labirinth));
        if (*labirinth == NULL) {
            return;
        }
    }
    fill_initial_labirinth(*labirinth);
}

void print_labirinth(char *labirinth) {
    int str_size = 13;
    for (int i = 0; i < str_size; i++) {
        for (int j = 0; j < str_size; j++) {
            putchar(labirinth[i * str_size + j]);
        }
        putchar('\n');
    }
}

int find_random_not_visited_room(char *visited, int not_visited_cnt) {
    int size = 6;
    if (not_visited_cnt < 1) {
        return -1;
    }
    int room;
    int id = 1 + rand() % not_visited_cnt;
    for (room = 0; id > 0 && room < size * size; room++) {
        if (visited[room] == 0) {
            id--;
        }
    }
    return room - 1;
}

int visit_random_room(char *labirinth, char *visited, int start_room, int force, int *walls_num, int *not_visited_cnt) {
    int size = 6;
    int str_size = 2 * size + 1;
    int i = start_room / size, j = start_room % size;

    static int directions[4] = {0, 1, 2, 3};
    for (int step = 0; step < NUM_RANDOM_PERMUTATIONS; step++) {
        int id1 = rand() % 4, id2 = rand() % 4;
        if (id1 != id2) {
            int tmp = directions[id1];
            directions[id1] = directions[id2];
            directions[id2] = tmp;
        }
    }

    /* Choose any available direction or return -1 */
    for (int id = 0; id < 4; id++) {
        switch (directions[id]) {
            case 0:
                /* North */
                if (i > 0 && (force || !visited[start_room - size])) {
                    if (!visited[start_room - size]) {
                        (*not_visited_cnt)--; 
                        visited[start_room - size] = 1;
                    }
                    if (labirinth[(2 * i) * str_size + (2 * j + 1)] == WALL_CHAR) {
                        (*walls_num)--;
                        labirinth[(2 * i) * str_size + (2 * j + 1)] = PASSAGE_CHAR;
                    }
                    return start_room - size;
                }
                break;
            case 1:
                /* East */
                if (j < size - 1 && (force || !visited[start_room + 1])) {
                    if (!visited[start_room + 1]) {
                        (*not_visited_cnt)--;
                        visited[start_room + 1] = 1;
                    }
                    if (labirinth[(2 * i + 1) * str_size + (2 * j + 2)] == WALL_CHAR) {
                        (*walls_num)--;
                        labirinth[(2 * i + 1) * str_size + (2 * j + 2)] = PASSAGE_CHAR;
                    }
                    return start_room + 1;
                }
                break;
            case 2:
                /* South */
                if (i < size - 1) {
                    if (!visited[start_room + size]) {
                        (*not_visited_cnt)--;
                        visited[start_room + size] = 1;
                    }
                    if (labirinth[(2 * i + 2) * str_size + (2 * j + 1)] == WALL_CHAR) {
                        (*walls_num)--;
                        labirinth[(2 * i + 2) * str_size + (2 * j + 1)] = PASSAGE_CHAR;
                    }
                    return start_room + size;
                }
                break;
            case 3:
                /* West */
                if (j > 0) {
                    if (!visited[start_room - 1]) {
                        (*not_visited_cnt)--;
                        visited[start_room - 1] = 1;
                    }
                    if (labirinth[(2 * i + 1) * str_size + (2 * j)] == WALL_CHAR) {
                        (*walls_num)--;
                        labirinth[(2 * i + 1) * str_size + (2 * j)] = PASSAGE_CHAR;
                    }
                    return start_room - 1;
                }
                break;
            default:
                break;
        }
    }
    return -1;
}

int break_walls(char *labirinth, char *visited) {
    int size = 6;
    int walls_remaining = 2 * (size - 1) * size;
    int not_visited_cnt = size * size;
    while (not_visited_cnt > 0) {
        int start_room = find_random_not_visited_room(visited, not_visited_cnt);
        int next_room = visit_random_room(labirinth, visited, start_room, 1, &walls_remaining, &not_visited_cnt);
        while (next_room != -1) {
            start_room = next_room;
            next_room = visit_random_room(labirinth, visited, start_room, 0, &walls_remaining, &not_visited_cnt);
        }
    }
    return walls_remaining;
}

char *get_labirinth(void) {
    int size = 6;

    char *labirinth, *visited;
    spawn_initial_labirinth(&labirinth, 1);
    if (labirinth == NULL) {
        return NULL;
    }

    visited = (char *) malloc(size * size * sizeof(*visited));
    if (visited == NULL) {
        free(labirinth);
        return NULL;
    }
    memset(visited, 0, size * size * sizeof(*visited));

    int walls_total = 2 * size * (size - 1);
    int walls_remaining = break_walls(labirinth, visited);
    for (int retry = 0; walls_remaining < 0.15 * walls_total && retry < MAX_INIT_RETRIES; retry++) {
        memset(visited, 0, size * size * sizeof(*visited));
        walls_remaining = break_walls(labirinth, visited);
    }
    free(visited);
    return labirinth;
}
