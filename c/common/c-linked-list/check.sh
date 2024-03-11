#!/bin/sh
INPUT_FILE=input_random.txt

SITE=$(basename $(dirname $(realpath .)))
PROBLEM_NO=$(basename $(realpath .))

make clean
make debug
while [ 1 ]
do
    echo "RUN"
    ../../output/${SITE}/${PROBLEM_NO}-random > ${INPUT_FILE}
    ../../output/${SITE}/${PROBLEM_NO}-solve < ${INPUT_FILE} > output_solve.txt
    ../../output/${SITE}/${PROBLEM_NO}-verify < ${INPUT_FILE} > output_verify.txt

    diff -q output_solve.txt output_verify.txt
    if [ $? -ne 0 ]
    then
        exit 1
    fi
    rm output_solve.txt output_verify.txt
done