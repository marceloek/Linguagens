#!/bin/bash

INIT=1658720900
DELAY=2

START=1
END=5

TIMESTAMP=$(date +%s)
echo $TIMESTAMP

DIFF=$(($INIT - $TIMESTAMP))
echo "sleep $DIFF"
if [ $DIFF -lt 1 ]; then
    exit 1
fi
sleep $DIFF

echo "START"
TIMESTAMP=$(date +%s)

for i in $( seq $START $END); do

    echo $i;

    DIFF=$(($i * $DELAY))
    DIFF=$(($TIMESTAMP + $DIFF))
    DIFF=$(($DIFF - $(date +%s)))
    echo "sleep $DIFF"
    sleep $DIFF
done