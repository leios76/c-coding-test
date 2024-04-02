#!/bin/sh

SITE=$(basename $(dirname $(realpath .)))
PROBLEM_NO=$(basename $(realpath .))
OUTPUT_PATH=$(realpath .)/../../output/${SITE}/${PROBLEM_NO}
mkdir -p ${OUTPUT_PATH}/solve ${OUTPUT_PATH}/verify ${OUTPUT_PATH}/random

javac -d ${OUTPUT_PATH}/random random/main.java
javac -d ${OUTPUT_PATH}/solve solve/main.java
javac -d ${OUTPUT_PATH}/verify verify/main.java

mkdir -p /tmp/${SITE}/${PROBLEM_NO}
INPUT_FILE=/tmp/${SITE}/${PROBLEM_NO}/input_random.txt

while [ 1 ]
do
    java -cp ${OUTPUT_PATH}/random Main > ${INPUT_FILE}
    /usr/bin/timeout 2 java -cp ${OUTPUT_PATH}/solve Main < ${INPUT_FILE} > /tmp/${SITE}/${PROBLEM_NO}/output_solve.txt
    if [ $? -ne 0 ]
    then
        echo "Solve Timeout!"
        cp /tmp/${SITE}/${PROBLEM_NO}/*.txt .
        exit 1
    fi
    java -cp ${OUTPUT_PATH}/verify Main < ${INPUT_FILE} > /tmp/${SITE}/${PROBLEM_NO}/output_verify.txt

    diff -q /tmp/${SITE}/${PROBLEM_NO}/output_solve.txt /tmp/${SITE}/${PROBLEM_NO}/output_verify.txt
    if [ $? -ne 0 ]
    then
        cp /tmp/${SITE}/${PROBLEM_NO}/*.txt .
        exit 1
    fi
    rm /tmp/${SITE}/${PROBLEM_NO}/output_solve.txt /tmp/${SITE}/${PROBLEM_NO}/output_verify.txt
done
