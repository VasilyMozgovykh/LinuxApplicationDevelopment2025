#include <libgen.h>
#include <libintl.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

#define _(STRING) gettext(STRING)

int main(void) {
    setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, LOCALE_PATH);
    textdomain(PACKAGE);

    int low = 1, high = 100, guess;
    char input[10];

    printf(_("Guess a number from 1 to 100.\n"));
    getchar();

    while (low < high) {
        guess = (low + high) / 2;
        printf(_("Is your number greater than %d? (Yes/No): "), guess);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            fprintf(stderr, _("Input/Output error. Terminating...\n"));
            return 1;
        }

        if (strncmp(input, "Yes", 3) == 0) {
            low = guess + 1;
        } else if (strncmp(input, "No", 2) == 0) {
            high = guess;
        } else {
            printf(_("Please answer 'Yes' or 'No'\n"));
        }
    }

    printf(_("Your guessed number is %d!\n"), (low + high) / 2);
    return 0;
}
