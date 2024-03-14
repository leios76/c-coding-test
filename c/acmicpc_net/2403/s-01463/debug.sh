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
../../output/${SITE}/${PROBLEM_NO}-solve < ${INPUT_FILE}

echo "====================================================="
echo " [*] RUN VERIFY APP"
echo "====================================================="
../../output/${SITE}/${PROBLEM_NO}-verify < ${INPUT_FILE}
