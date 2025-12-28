#include "roman_converter.h"
#include <string.h>

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
