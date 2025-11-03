#define _GNU_SOURCE

#include <ctype.h>
#include <rhash.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

#ifdef READLINE_OVERRIDE
#include <readline/readline.h>
#endif

const char STRTOK_DELIM[5] = {'\n', '\t', '\r', ' ', '\0'};

int read_line(char **line_ptr);

void print_hash_from_str(const char *str, int is_file_input, int rhash_id, int rhpr);

int main(int argc, char **argv) {
    char *line = NULL;

    rhash_library_init();

    while (read_line(&line) != -1) {
        char *hash_type = strtok(line, STRTOK_DELIM);
        char *str = strtok(NULL, STRTOK_DELIM);
        if (hash_type == NULL || str == NULL) {
            fprintf(stderr, "Usage: hash_type str_or_file\n");
            continue;
        }

        int rhash_id = 0;
        if (!strcasecmp(hash_type, "MD5")) {
            rhash_id = RHASH_MD5;
        } else if (!strcasecmp(hash_type, "SHA1")) {
            rhash_id = RHASH_SHA1;
        } else if (!strcasecmp(hash_type, "TTH")) {
            rhash_id = RHASH_TTH;
        } else {
            fprintf(stderr, "Hash type %s is not supported. MD5, SHA1, TTH are only available types\n", hash_type);
            continue;
        }

        int is_file_input = str[0] != '"';
        int rhpr = isupper(hash_type[0]) ? RHPR_HEX : RHPR_BASE64;
        print_hash_from_str(str, is_file_input, rhash_id, rhpr);

        free(line);
        line = NULL;
    }

    if (line != NULL) {
        free(line);
    }
    return 0;
}

void print_hash_from_str(const char *str, int is_file_input, int rhash_id, int rhpr) {
    unsigned char digest[64];
    char output[130];

    if (is_file_input) {
        if (rhash_file(rhash_id, str, digest) == -1) {
            fprintf(stderr, "Error getting hash of file %s\n", str);
            return;
        }
    } else {
        const char *true_str_ptr = str + 1;
        if (rhash_msg(rhash_id, true_str_ptr, strlen(true_str_ptr), digest) == -1) {
            fprintf(stderr, "Error getting hash of string %s\n", true_str_ptr);
            return;
        }
    }
    int digest_size = rhash_get_digest_size(rhash_id);
    rhash_print_bytes(output, digest, digest_size, rhpr);
    printf("%s\n", output);
}

int read_line(char **line_ptr) {
#ifndef READLINE_OVERRIDE
    size_t n;
    return getline(line_ptr, &n, stdin);
#else
    *line_ptr = readline("");
    if (*line_ptr == NULL) {
        return -1;
    }
    return 0;
#endif
}
