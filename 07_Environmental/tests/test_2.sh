#!/usr/bin/env sh
ground_truth=$(sha1sum ../Makefile.am | awk '{ print $1 }');
res=$(echo 'SHA1 ../Makefile.am' | ./rhasher);

if ["$res" = "$ground_truth"];
then
    echo "Test 2 (sha1sum) ok"
    exit 0;
else
    echo "Test 2 (sha1sum) failed: res:'$res' gt:'$ground_truth'"
    exit 1;
fi
