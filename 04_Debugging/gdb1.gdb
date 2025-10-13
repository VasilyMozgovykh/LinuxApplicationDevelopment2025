set pagination off
set confirm off

file range

break main
run 1 12 > /dev/null

break 42 if (i % 5 == 0)

commands
    silent
    printf "@@@ from: %d, to: %d, step: %d, i: %d\n", from, to, step, i
    continue
end

continue
quit
