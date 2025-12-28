#include "config.h"
#include "roman_converter.h"
#include <check.h>
#include <string.h>

RomanNumeralPair RomanNumeralGroundTruthMap[] = {
    {"C", 100},
    {"XCIX", 99}, {"XCVIII", 98}, {"XCVII", 97}, {"XCVI", 96}, {"XCV", 95},
    {"XCIV", 94}, {"XCIII", 93}, {"XCII", 92}, {"XCI", 91}, {"XC", 90},
    {"LXXXIX", 89}, {"LXXXVIII", 88}, {"LXXXVII", 87}, {"LXXXVI", 86}, {"LXXXV", 85},
    {"LXXXIV", 84}, {"LXXXIII", 83}, {"LXXXII", 82}, {"LXXXI", 81}, {"LXXX", 80},
    {"LXXIX", 79}, {"LXXVIII", 78}, {"LXXVII", 77}, {"LXXVI", 76}, {"LXXV", 75},
    {"LXXIV", 74}, {"LXXIII", 73}, {"LXXII", 72}, {"LXXI", 71}, {"LXX", 70},
    {"LXIX", 69}, {"LXVIII", 68}, {"LXVII", 67}, {"LXVI", 66}, {"LXV", 65},
    {"LXIV", 64}, {"LXIII", 63}, {"LXII", 62}, {"LXI", 61}, {"LX", 60},
    {"LIX", 59}, {"LVIII", 58}, {"LVII", 57}, {"LVI", 56}, {"LV", 55},
    {"LIV", 54}, {"LIII", 53}, {"LII", 52}, {"LI", 51}, {"L", 50},
    {"XLIX", 49}, {"XLVIII", 48}, {"XLVII", 47}, {"XLVI", 46}, {"XLV", 45},
    {"XLIV", 44}, {"XLIII", 43}, {"XLII", 42}, {"XLI", 41}, {"XL", 40},
    {"XXXIX", 39}, {"XXXVIII", 38}, {"XXXVII", 37}, {"XXXVI", 36}, {"XXXV", 35},
    {"XXXIV", 34}, {"XXXIII", 33}, {"XXXII", 32}, {"XXXI", 31}, {"XXX", 30},
    {"XXIX", 29}, {"XXVIII", 28}, {"XXVII", 27}, {"XXVI", 26}, {"XXV", 25},
    {"XXIV", 24}, {"XXIII", 23}, {"XXII", 22}, {"XXI", 21}, {"XX", 20},
    {"XIX", 19}, {"XVIII", 18}, {"XVII", 17}, {"XVI", 16}, {"XV", 15},
    {"XIV", 14}, {"XIII", 13}, {"XII", 12}, {"XI", 11}, {"X", 10},
    {"IX", 9}, {"VIII", 8}, {"VII", 7}, {"VI", 6}, {"V", 5},
    {"IV", 4}, {"III", 3}, {"II", 2}, {"I", 1}
};

START_TEST(test_numeral_to_roman) {
    int match = 0;
    for (int i = 0; i < 100; i++) {
        RomanNumeralPair pair = RomanNumeralGroundTruthMap[i];
        char *roman = numeral_to_roman(pair.numeral);
        if (strcmp(roman, pair.roman) == 0) {
            match++;
        }
    }
    ck_assert_int_eq(match, 100);
}
END_TEST

START_TEST(test_roman_to_numeral) {
    int match = 0;
    for (int i = 0; i < 100; i++) {
        RomanNumeralPair pair = RomanNumeralGroundTruthMap[i];
        int numeral = roman_to_numeral(pair.roman);
        if (numeral == pair.numeral) {
            match++;
        }
    }
    ck_assert_int_eq(match, 100);
}
END_TEST

int main(void) {
    TCase *tcase_numeral_to_roman, *tcase_roman_to_numeral;
    Suite *suite;
    SRunner *runner;
    int failed_count;

    tcase_numeral_to_roman = tcase_create("test_numeral_to_roman");
    tcase_roman_to_numeral = tcase_create("test_roman_to_numeral");

    tcase_add_test(tcase_numeral_to_roman, test_numeral_to_roman);
    tcase_add_test(tcase_roman_to_numeral, test_roman_to_numeral);

    suite = suite_create("roman_converter");
    suite_add_tcase(suite, tcase_numeral_to_roman);
    suite_add_tcase(suite, tcase_roman_to_numeral);

    runner = srunner_create(suite);
    srunner_run_all(runner, CK_VERBOSE);
    failed_count = srunner_ntests_failed(runner);
    srunner_free(runner);

    return failed_count != 0;
}
