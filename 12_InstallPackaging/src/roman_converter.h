#ifndef ROMAN_CONVERTER_H_DEFINED
#define ROMAN_CONVERTER_H_DEFINED

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
char *numeral_to_roman(int numeral);

/**
 * \brief Convert roman string to integer.
 *
 * \param roman roman string (e.g. "XIV").
 * \return Parsed integer.
 */
int roman_to_numeral(const char *roman);

#endif /* ROMAN_CONVERTER_H_DEFINED */
