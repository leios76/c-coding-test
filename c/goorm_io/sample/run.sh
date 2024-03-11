#!/bin/sh
INPUT_FILE=input1.txt
if [ -n "$1" ]
then
    INPUT_FILE=$1
fi

SITE=$(basename $(dirname $(realpath .)))
PROBLEM_NO=$(basename $(realpath .))

make clean
make debug
echo "====================================================="
echo " [*] RUN SOLVE APP"
echo "====================================================="
/usr/bin/timeout 2 ../../output/${SITE}/${PROBLEM_NO}-solve < ${INPUT_FILE}
if [ $? -ne 0 ]
then
    echo "Timeout!"
    exit 1
fi

echo "====================================================="
echo " [*] RUN VERIFY APP"
echo "====================================================="
../../output/${SITE}/${PROBLEM_NO}-verify < ${INPUT_FILE}