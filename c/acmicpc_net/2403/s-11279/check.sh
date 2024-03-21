#!/bin/sh
SITE=$(basename $(dirname $(realpath .)))
PROBLEM_NO=$(basename $(realpath .))

mkdir -p /tmp/${SITE}/${PROBLEM_NO}
INPUT_FILE=/tmp/${SITE}/${PROBLEM_NO}/input_random.txt

make clean
make
while [ 1 ]
do
    ../../output/${SITE}/${PROBLEM_NO}-random > ${INPUT_FILE}
    /usr/bin/timeout 1 ../../output/${SITE}/${PROBLEM_NO}-solve < ${INPUT_FILE} > /tmp/${SITE}/${PROBLEM_NO}/output_solve.txt
    if [ $? -ne 0 ]
    then
        echo "Solve Timeout!"
        cp /tmp/${SITE}/${PROBLEM_NO}/*.txt .
        exit 1
    fi
    ../../output/${SITE}/${PROBLEM_NO}-verify < ${INPUT_FILE} > /tmp/${SITE}/${PROBLEM_NO}/output_verify.txt

    diff -q /tmp/${SITE}/${PROBLEM_NO}/output_solve.txt /tmp/${SITE}/${PROBLEM_NO}/output_verify.txt
    if [ $? -ne 0 ]
    then
        cp /tmp/${SITE}/${PROBLEM_NO}/*.txt .
        exit 1
    fi
    rm /tmp/${SITE}/${PROBLEM_NO}/output_solve.txt /tmp/${SITE}/${PROBLEM_NO}/output_verify.txt
done
