#include <libgen.h>
#include <libintl.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

#define _(STRING) gettext(STRING)

/* Roman numbers support */
typedef struct RomanNumeralPair {
    const char *roman;
    int numeral;
} RomanNumeralPair;

RomanNumeralPair RomanNumeralMap[] = {
    {"C", 100}, {"XC", 90}, {"L", 50},
    {"XL", 40},{"X", 10}, {"IX", 9},
    {"V", 5}, {"IV", 4}, {"I", 1}
};

char *numeral_to_roman(int numeral) {
    static char roman[10];
    char *roman_ptr = roman;
    for (int i = 0; i < 9; i++) {
        int div = numeral / RomanNumeralMap[i].numeral;
        for (int k = 0; k < div; k++) {
            for (int c = 0; c < strlen(RomanNumeralMap[i].roman); c++, roman_ptr++) {
                *roman_ptr = RomanNumeralMap[i].roman[c];
            }
        }
        numeral %= RomanNumeralMap[i].numeral;
        if (numeral == 0) {
            break;
        }
    }
    *roman_ptr = '\0';
    return roman;
}

int roman_to_numeral(const char *roman) {
    int numeral = 0, max_iterations = 10;
    for (int iter_num = 0; iter_num < max_iterations && *roman != '\0'; iter_num++) {
        for (int i = 0; i < 9; i++) {
            if (strstr(roman, RomanNumeralMap[i].roman) == roman) {
                numeral += RomanNumeralMap[i].numeral;
                roman += strlen(RomanNumeralMap[i].roman);
                break;
            }
        }
    }
    return numeral;
}
/* ===================== */

int main(int argc, char **argv) {
    setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, LOCALE_PATH);
    textdomain(PACKAGE);

    char roman_mode = (argc > 1 && strcmp(argv[1], "-r") == 0);

    int low = 1, high = 100, guess;
    char input[10];

    if (roman_mode) {
        printf(_("Guess a number from I to C.\n"));
    } else {
        printf(_("Guess a number from 1 to 100.\n"));
    }
    getchar();

    while (low < high) {
        guess = (low + high) / 2;
        if (roman_mode) {
            printf(_("Is your number greater than %s? (Yes/No): "), numeral_to_roman(guess));
        } else {
            printf(_("Is your number greater than %d? (Yes/No): "), guess);
        }

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

    if (roman_mode) {
        printf(_("Your guessed number is %s!\n"), numeral_to_roman((low + high) / 2));
    } else {
        printf(_("Your guessed number is %d!\n"), (low + high) / 2);
    }
    return 0;
}
