#!/bin/sh


# Handling removing tmp file
exit_handler() {
    trap - EXIT;
    test -r "$TMPFILE" && rm -f "$TMPFILE";
}

trap exit_handler EXIT HUP INT QUIT PIPE TERM;

TMPFILE=$(mktemp);


# Reading input chars and saving to tmp file
NROW=0;
while IFS="" read -r LINE; do
    NCOL=0;
    echo "$LINE" | fold --width=1 | while IFS="" read -r CHAR; do
        echo $NROW $NCOL $CHAR >> "$TMPFILE";
        NCOL=$((NCOL+1));
    done
    NROW=$((NROW+1));
done


# Putting shuffled chars
DELAY=$1;
tput clear;
shuf "$TMPFILE" | while read -r NROW NCOL CHAR; do
    tput cup $NROW $NCOL;
    /bin/echo -e "$CHAR";
    sleep $DELAY;
done
tput cup $((NROW+1)) 0;
