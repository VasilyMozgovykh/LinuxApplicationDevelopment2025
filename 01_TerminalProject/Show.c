#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DX 7
#define DY 3
#define BUFFER_SIZE 256


int count_digits(int number) {
    if (number == 0) {
        return 1;
    }

    int digits = 0;
    while (number != 0) {
        number /= 10;
        digits++;
    }
    return digits;
}


void draw_line(WINDOW *win, FILE *fp, char *buf, int buf_size, int max_x, int *line_number) {
    if (ferror(fp) || feof(fp)) {
        return;
    }

    /* Print truncated line first */
    fgets(buf, max_x * sizeof(*buf), fp);
    
    char *newline_ptr = NULL;
    if ((newline_ptr = strchr(buf, '\n')) != NULL) {
        *newline_ptr = '\0';
    }
    
    buf[max_x - 3 - count_digits(*line_number)] = '\0';
    wprintw(win, "\n%d: %s", *line_number, buf);
    (*line_number)++;
    if (newline_ptr != NULL) {
        return;
    }

    /* Read file to the next line */
    while (fgets(buf, buf_size * sizeof(*buf), fp) != NULL) {
        if ((newline_ptr = strchr(buf, '\n')) != NULL) {
            break;
        }
    }
}


int main(int argc, char **argv) {
    /* Reading argument */
    if (argc < 2) {
        fprintf(stderr, "Too few arguments! Try: 'Show FILENAME'\n");
        return 1;
    }
    char *filename = argv[1];


    /* Opening file */
    FILE *file_ptr;
    if ((file_ptr = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Can't open file '%s'\n", filename);
        return 1;
    }


    /* Initializing screen */
    WINDOW *frame, *win;
    
    if (initscr() == NULL) {
        fprintf(stderr, "Error initializing screen: 'initscr' returned NULL");
        fclose(file_ptr);
        return 1;
    }
    noecho();
    cbreak();
    printw("Press SPACE to read new line\n");
    printw("Press ESC to escape\n");
    refresh();


    /* Initializing frame */
    if ((frame = newwin(LINES - 2 * DY, COLS - 2 * DX, DY, DX)) == NULL) {
        fprintf(stderr, "Error initializing frame: 'newwin' returned NULL");
        endwin();
        fclose(file_ptr);
        return 1;
    }
    box(frame, 0, 0);
    mvwaddstr(frame, 0, 4, filename);
    wrefresh(frame);


    /* Initializing inner window */
    if ((win = newwin(LINES - 2 * DY - 2, COLS - 2 * DX - 2, DY + 1, DX + 1)) == NULL) {
        fprintf(stderr, "Error initializing inner window: 'newwin' returned NULL");
        delwin(frame);
        endwin();
        fclose(file_ptr);
        return 1;
    }
    keypad(win, TRUE);
    scrollok (win, TRUE);


    /* Reading file */
    char buf[BUFFER_SIZE];
    int line_number = 0;
    for (int i = 0; i < LINES - 2 * DY - 2; i++) {
        draw_line(win, file_ptr, buf, BUFFER_SIZE, COLS - 2 * DX - 2, &line_number);
    }


    /* Reading input */
    int ch = 0;
    while((ch = wgetch(win)) != 27) {
        switch (ch) {
            case ' ':
                draw_line(win, file_ptr, buf, BUFFER_SIZE, COLS - 2 * DX - 2, &line_number);
            default:
                break;
        }
    }


    /* Free memory*/
    delwin(win);
    delwin(frame);
    endwin();
    

    /* Closing file */
    fclose(file_ptr);

    return 0;
}
