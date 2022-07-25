#!/bin/bash

INIT=1658723135
DELAY=15

START=1
END=5

TIMESTAMP=$(date +%s)
echo $TIMESTAMP

DIFF=$(($INIT - $TIMESTAMP))

echo "sleep $DIFF"
if [ $DIFF -lt 1 ]; then
    echo "Erro de timestamp"
    exit 1
fi
sleep $DIFF

echo "START"
TIMESTAMP=$INIT

cd "/home/marceloek/Desktop/mqttloader/"

for i in $( seq $START $END); do

    echo $i;
    ./bin/mqttloader -c mqttloader_pub.conf

    DIFF=$(($i * $DELAY))
    DIFF=$(($TIMESTAMP + $DIFF))
    DIFF=$(($DIFF - $(date +%s)))
    echo "sleep $DIFF"
    sleep $DIFF
done
