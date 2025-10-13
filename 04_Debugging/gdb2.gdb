set pagination off
set confirm off


file range

break main
run -100 100 3 > /dev/null

set $cnt = 0

break 42

commands
    silent
    set $cnt = ($cnt + 1)
    if ($cnt >= 28 && $cnt <= 35)
        printf "@@@ from: %d, to: %d, step: %d, i: %d\n", from, to, step, i
    end
    continue
end

continue
quit
