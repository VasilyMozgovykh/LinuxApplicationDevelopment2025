#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int from = 0, to = 1, step = 1;

    if (argc == 1) {
        printf("help\n");
        fprintf(stderr, "Usage: ./range [from [to [step]]]\n");
        return 0;
    } else if (argc == 2) {
        to = strtol(argv[1], NULL, 10);
    } else if (argc == 3) {
        from = strtol(argv[1], NULL, 10);
        to = strtol(argv[2], NULL, 10);
    } else if (argc == 4) {
        from = strtol(argv[1], NULL, 10);
        to = strtol(argv[2], NULL, 10);
        step = strtol(argv[3], NULL, 10);
    } else {
        fprintf(stderr, "Usage: ./range [from [to [step]]]\n");
        return 1;
    }

    if (
        step == 0
        || (
            step > 0
            && from > to
        )
        || (
            step < 0
            && from < to
        )
    ) {
        fprintf(stderr, "Bad parameters\n");
        return 1;
    }

    if (step > 0) {
        for (int i = from; i < to; i += step) {
            printf("%d\n", i);
        }
    } else {
        for (int i = from; i > to; i += step) {
            printf("%d\n", i);
        }
    }

    return 0;
}
