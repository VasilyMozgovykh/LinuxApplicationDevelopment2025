/** \mainpage guess
 *
 * \file guess.c
 * 
 * \section name NAME
 * guess - simple guess a number game for kids
 * 
 * \section synopsis SYNOPSIS
 * \b guess [\b -r] [\b --help]
 * 
 * \section description DESCRIPTION
 *
 * Program asks user if their number is greater than guessed value
 * and finds the number using binary search.
 *
 * Supports arabic numbers (1..100) and roman numbers (I..C).
 * 
 * \section options OPTIONS
 * \b --help
 * \n Display help
 * 
 * \b -r
 * \n Use roman numbers
 */

#include <libgen.h>
#include <libintl.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

/** gettext shortcut */
#define _(STRING) gettext(STRING)

/**
 * \struct RomanNumeralPair
 * \brief Mapping pair roman literal -> integer value.
 */
typedef struct RomanNumeralPair {
    const char *roman; /**< Roman literal */
    int numeral; /**< Integer value */
} RomanNumeralPair;

/**
 * \brief Roman to arabic mapping table.
 *
 * Order from largest to smallest.
 */
RomanNumeralPair RomanNumeralMap[] = {
    {"C", 100}, {"XC", 90}, {"L", 50},
    {"XL", 40},{"X", 10}, {"IX", 9},
    {"V", 5}, {"IV", 4}, {"I", 1}
};

/**
 * \brief Convert integer to Roman representation.
 *
 * \param numeral Number in range 1..100.
 * \return Pointer to static buffer with roman representation.
 * \warning The returned pointer refers to a static buffer.
 */
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

/**
 * \brief Convert roman string to integer.
 *
 * \param roman roman string (e.g. "XIV").
 * \return Parsed integer.
 */
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

/**
 * \brief Program's entry point
 *
 * \param argc Total number of arguments.
 * \param argv Provided argument strings.
 * \return Error code, 0 on success
 */
int main(int argc, char **argv) {
    setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, LOCALE_PATH);
    textdomain(PACKAGE);

    char roman_mode = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-r") == 0) {
            roman_mode = 1;
        } else if (strcmp(argv[i], "--help") == 0) {
            printf(_(
                "Usage: %s [-r | --help | --version]\n"
                "Simple guess a number game for kids.\n"
                "Program asks user if their number is greater than guessed value "
                "and finds the number using binary search.\n"
                "\n"
                "Possible flags:\n"
                "    -r           Use roman numbers\n"
                "    --help       Display this help\n"
                "    --version    Display program version\n"
            ), argv[0]);
            return 0;
        } else if (strcmp(argv[i], "--version") == 0) {
            printf(_("0.1"));
            return 0;
        }
    }

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
