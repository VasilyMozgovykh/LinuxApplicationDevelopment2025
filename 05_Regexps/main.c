#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR_BUF_SIZE (1024)
#define MAX_MATCHES (9)
#define MAX_REFS (100)


int substitute(regex_t *preg, char *substitution, char *string, char **result);

int parse_substitution(char *substitution, int *pos, int *num_ref, int *ref_count);

int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "Usage: ./esub regexp substitution string\n");
        return 1;
    }

    char *regexp = argv[1];
    char *substitution = argv[2];
    char *string = argv[3];

    regex_t reg;
    int ret;

    if ((ret = regcomp(&reg, regexp, REG_EXTENDED)) != 0) {
        char errbuf[ERR_BUF_SIZE];
        regerror(ret, &reg, errbuf, sizeof(errbuf));
        fprintf(stderr, "%s\n", errbuf);
        regfree(&reg);
        return 1;
    }

    char *result;
    if (substitute(&reg, substitution, string, &result) == -1) {
        regfree(&reg);
        return 1;
    }

    printf("%s\n", result);
    free(result);

    return 0;
}

int substitute(regex_t *preg, char *substitution, char *string, char **result) {
    regmatch_t pmatch[MAX_MATCHES + 1];
    int ret;

    ret = regexec(preg, string, MAX_MATCHES + 1, pmatch, 0);
    if (ret == REG_NOMATCH) {
        *result = strdup(string);
        return 0;
    } else if (ret != 0) {
        char errbuf[ERR_BUF_SIZE];
        regerror(ret, preg, errbuf, sizeof(errbuf));
        fprintf(stderr, "Error matching regexp: %s\n", errbuf);
        return -1;
    }

    int ref_pos[MAX_REFS];
    int num_ref[MAX_REFS];
    
    int ref_count;

    if (parse_substitution(substitution, ref_pos, num_ref, &ref_count) == -1) {
        return -1;
    }

    for (int i = 0; i < ref_count; i++) {
        if (num_ref[i] > preg->re_nsub) {
            fprintf(stderr, "Pocket %d doesn't exist (%ld total pockets)\n", num_ref[i], preg->re_nsub);
            return -1;
        }
    }

    size_t result_len = 0;
    size_t sub_len = strlen(substitution);

    result_len += pmatch[0].rm_so;

    int last_pos = 0;
    for (int i = 0; i < ref_count; i++) {
        result_len += ref_pos[i] - last_pos;

        int bref = num_ref[i];
        result_len += pmatch[bref].rm_eo - pmatch[bref].rm_so;

        last_pos = ref_pos[i] + 2;
    }
    result_len += sub_len - last_pos;
    result_len += strlen(string) - pmatch[0].rm_eo;

    *result = (char *) malloc(result_len + 1);
    if (*result == NULL) {
        fprintf(stderr, "Malloc error\n");
        return -1;
    }

    char *out = *result;
    char *in = string;

    strncpy(out, in, pmatch[0].rm_so);
    out += pmatch[0].rm_so;
    in += pmatch[0].rm_so;

    last_pos = 0;
    for (int i = 0; i < ref_count; i++) {
        strncpy(out, substitution + last_pos, ref_pos[i] - last_pos);
        out += ref_pos[i] - last_pos;

        int bref = num_ref[i];
        size_t bref_len = pmatch[bref].rm_eo - pmatch[bref].rm_so;
        strncpy(out, string + pmatch[bref].rm_so, bref_len);
        out += bref_len;

        last_pos = ref_pos[i] + 2;
    }

    strcpy(out, substitution + last_pos);
    out += strlen(substitution + last_pos);

    strcpy(out, string + pmatch[0].rm_eo);

    return 0;
}

int parse_substitution(char *substitution, int *pos, int *num_ref, int *ref_count) {
    int i = 0;
    int ref_idx = 0;
    *ref_count = 0;

    while (substitution[i] != '\0') {
        if (substitution[i] == '\\' && substitution[i + 1] != '\0') {
            if (substitution[i + 1] != '\0') {
                if (substitution[i + 1] >= '1' && substitution[i + 1] <= '9') {
                    if (ref_idx >= MAX_REFS) {
                        fprintf(stderr, "Max %d refs exceeded\n", MAX_REFS);
                        return -1;
                    }
                    pos[ref_idx] = i;
                    num_ref[ref_idx] = substitution[i + 1] - '0';
                    ref_idx++;
                    i += 2;
                    continue;
                } else if (substitution[i + 1] == '\\') {
                    i += 2;
                    continue;
                }
            }
            fprintf(stderr, "Wrong substitution pocket\n");
            return -1;
        }
        i++;
    }

    *ref_count = ref_idx;
    return 0;
}
