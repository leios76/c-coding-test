#!/bin/sh

SITE=$(basename $(dirname $(realpath .)))
PROBLEM_NO=$(basename $(realpath .))
OUTPUT_PATH=$(realpath .)/../../output/${SITE}/${PROBLEM_NO}
mkdir -p ${OUTPUT_PATH}/solve ${OUTPUT_PATH}/verify ${OUTPUT_PATH}/random

javac -d ${OUTPUT_PATH}/random random/main.java

INPUT_FILE=input_random.txt

java -cp ${OUTPUT_PATH}/random Main > ${INPUT_FILE}
