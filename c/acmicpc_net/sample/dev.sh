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

inotifywait -m -r -e modify -e create . |
    while read file_path file_event file_name; do
        FILE=${file_path}${file_name}
        EXT="${FILE##*.}"
        case ${EXT} in
            c)
                make clean && make -j8 debug
                echo "====================================================="
                echo " [*] RUN SOLVE APP"
                echo "====================================================="
                ../../output/${SITE}/${PROBLEM_NO}-solve < "${LAST_INPUT_FILE}"
                echo "====================================================="
                echo " [*] RUN VERIFY APP"
                echo "====================================================="
                ../../output/${SITE}/${PROBLEM_NO}-verify < "${LAST_INPUT_FILE}"
                ;;
            txt)
                LAST_INPUT_FILE=${FILE}
                echo "====================================================="
                echo " [*] RUN SOLVE APP"
                echo "====================================================="
                ../../output/${SITE}/${PROBLEM_NO}-solve < "${FILE}"
                echo "====================================================="
                echo " [*] RUN VERIFY APP"
                echo "====================================================="
                ../../output/${SITE}/${PROBLEM_NO}-verify < "${FILE}"
                ;;
        esac
    done
