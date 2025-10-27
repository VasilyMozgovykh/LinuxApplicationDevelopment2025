#include <stdio.h>
#include <string.h>

#define BUF_SIZE 1024

enum {
    ERR_SUCCESS = 0,
    ERR_NARGS = 1,
    ERR_ROPEN = 2,
    ERR_WOPEN = 3,
    ERR_REMOVE = 4,
    ERR_CLOSE = 5
};

int close_file(FILE **fp) {
    if (*fp != NULL) {
        int err_code = fclose(*fp);
        *fp = NULL;
        return err_code;
    }
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s infile outfile\n", argv[0]);
        return ERR_NARGS;
    }

    char *infile = argv[1];
    char *outfile = argv[2];
    char tmpfile[] = "__tempfile__";
    if (strcmp(infile, outfile) == 0) {
        return ERR_SUCCESS;
    }
    
    FILE *fin = NULL, *fout = NULL;

    /* Check possibility to write outfile */
    int fout_exists = 0;
    if ((fin = fopen(outfile, "rb")) != NULL) {
        fout_exists = 1;
    }
    if (close_file(&fin) != 0) {
        fprintf(stderr, "Can't close %s\n", outfile);
        return ERR_CLOSE;
    }
    if (fout_exists && (fout = fopen(outfile, "ab")) == NULL) {
        fprintf(stderr, "Can't open %s for writing\n", outfile);
        return ERR_WOPEN;
    }
    if (close_file(&fout) != 0) {
        fprintf(stderr, "Can't close %s\n", outfile);
        return ERR_CLOSE;
    }

    /* Try to open tempfile */
    if ((fout = fopen(tmpfile, "wb")) == NULL) {
        fprintf(stderr, "Can't open %s for writing\n", tmpfile);
        return ERR_WOPEN;
    }

    /* Try to copy input file to tempfile */
    if ((fin = fopen(infile, "rb")) == NULL) {
        fprintf(stderr, "Can't open %s for reading\n", infile);
        close_file(&fout);
        remove(tmpfile);
        return ERR_ROPEN;
    }

    size_t bytes_read;
    char buffer[BUF_SIZE];
    while ((bytes_read = fread(buffer, sizeof(*buffer), BUF_SIZE, fin)) > 0) {
        fwrite(buffer, sizeof(*buffer), bytes_read, fout);
    }
    if (close_file(&fin) != 0) {
        fprintf(stderr, "Can't close %s\n", infile);
        return ERR_CLOSE;
    }
    if (close_file(&fout) != 0) {
        fprintf(stderr, "Can't close %s\n", tmpfile);
        return ERR_CLOSE;
    }

    /* Copy file to output */
    if ((fin = fopen(tmpfile, "rb")) == NULL) {
        fprintf(stderr, "Can't open %s for reading\n", tmpfile);
        return ERR_ROPEN;
    }
    if ((fout = fopen(outfile, "wb")) == NULL) {
        fprintf(stderr, "Can't open %s for writing\n", outfile);
        close_file(&fin);
        return ERR_WOPEN;
    }
    while ((bytes_read = fread(buffer, sizeof(*buffer), BUF_SIZE, fin)) > 0) {
        fwrite(buffer, sizeof(*buffer), bytes_read, fout);
    }
    if (close_file(&fin) != 0) {
        fprintf(stderr, "Can't close %s\n", tmpfile);
        return ERR_CLOSE;
    }
    if (close_file(&fout) != 0) {
        fprintf(stderr, "Can't close %s\n", outfile);
        return ERR_CLOSE;
    }

    /* Remove tmp and source file */
    if (remove(tmpfile) != 0) {
        fprintf(stderr, "Can't remove %s\n", tmpfile);
        return ERR_REMOVE;
    }
    if (remove(infile) != 0) {
        fprintf(stderr, "Can't remove %s\n", infile);
        return ERR_REMOVE;
    }

    /* Success! */
    return ERR_SUCCESS;
}