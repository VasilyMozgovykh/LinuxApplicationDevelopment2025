#!/usr/bin/env sh
ground_truth=$(md5sum ../Makefile.am | awk '{ print $1 }');
res=$(echo 'MD5 ../Makefile.am' | ./rhasher);

if ["$res" = "$ground_truth"];
then
    echo "Test 1 (md5sum) ok"
    exit 0;
else
    echo "Test 1 (md5sum) failed: res:'$res' gt:'$ground_truth'"
    exit 1;
fi
