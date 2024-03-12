#!/bin/sh
INPUT_FILE=input1.txt
if [ -n "$1" ]
then
    INPUT_FILE=$1
fi

SITE=$(basename $(dirname $(realpath .)))
PROBLEM_NO=$(basename $(realpath .))
TOP=$(realpath .)
OUTPUT_PATH=$(realpath .)/../../output/${SITE}/${PROBLEM_NO}
mkdir -p ${OUTPUT_PATH}/solve ${OUTPUT_PATH}/verify ${OUTPUT_PATH}/random

javac -d ${OUTPUT_PATH}/random random/main.java
javac -d ${OUTPUT_PATH}/solve solve/main.java
javac -d ${OUTPUT_PATH}/verify verify/main.java

echo "====================================================="
echo " [*] RUN SOLVE APP"
echo "====================================================="
#../../output/${SITE}/${PROBLEM_NO}-solve < ${INPUT_FILE}
java -cp ${OUTPUT_PATH}/solve Main < ${INPUT_FILE}

echo "====================================================="
echo " [*] RUN VERIFY APP"
echo "====================================================="
java -cp ${OUTPUT_PATH}/verify Main < ${INPUT_FILE}
