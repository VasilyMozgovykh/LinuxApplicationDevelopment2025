#!/usr/bin/env sh
ground_truth=$(tthsum ../Makefile.am | awk '{ print $1 }');
res=$(echo 'TTH ../Makefile.am' | ./rhasher);

if ["$res" = "$ground_truth"];
then
    echo "Test 3 (tthsum) ok"
    exit 0;
else
    echo "Test 3 (tthsum) failed: res:'$res' gt:'$ground_truth'"
    exit 1;
fi
