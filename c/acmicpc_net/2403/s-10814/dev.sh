#!/bin/bash

which inotifywait >/dev/null
if [ $? -ne 0 ]
then
  echo "INSTALL inotify-tools: sudo apt-get install inotify-tools"
  exit 1
fi

SITE=$(basename $(dirname $(realpath .)))
PROBLEM_NO=$(basename $(realpath .))

LAST_INPUT_FILE=input1.txt

inotifywait -m -e modify -e create *.txt solve/*.c verify/*.c random/*.c |
    while read file_path file_event; do
        EXT="${file_path##*.}"
        case ${EXT} in
            c)
                make clean && make -j8 debug
                echo "====================================================="
                echo " [*] RUN SOLVE APP"
                echo "====================================================="
                ../../output/${SITE}/${PROBLEM_NO}-solve < ${LAST_INPUT_FILE}
                echo "====================================================="
                echo " [*] RUN VERIFY APP"
                echo "====================================================="
                ../../output/${SITE}/${PROBLEM_NO}-verify < ${LAST_INPUT_FILE}
                ;;
            txt)
                LAST_INPUT_FILE=${file_path}
                echo "====================================================="
                echo " [*] RUN SOLVE APP"
                echo "====================================================="
                ../../output/${SITE}/${PROBLEM_NO}-solve < ${file_path}
                echo "====================================================="
                echo " [*] RUN VERIFY APP"
                echo "====================================================="
                ../../output/${SITE}/${PROBLEM_NO}-verify < ${file_path}
                ;;
        esac
    done
