#!/bin/bash

which inotifywait >/dev/null
if [ $? -ne 0 ]
then
  echo "INSTALL inotify-tools: sudo apt-get install inotify-tools"
  exit 1
fi

LAST_INPUT_FILE=input1.txt

inotifywait -m -r -e modify -e create . |
    while read file_path file_event file_name; do
        FILE=${file_path}${file_name}
        EXT="${FILE##*.}"
        case ${EXT} in
            c)
                SITE=$(basename $(dirname $(dirname $(realpath ${file_path}))))
                PROBLEM_NO=$(basename $(dirname $(realpath ${file_path})))
                BASE_PATH=$(realpath ${file_path}/..)
                OUTPUT_PATH=$(realpath ${file_path}/../../../output)

                make clean -C ${BASE_PATH} && make -j8 debug -C ${BASE_PATH}
                echo "====================================================="
                echo " [*] RUN ${PROBLEM_NO} SOLVE APP"
                echo "====================================================="
                /usr/bin/timeout 2 ${OUTPUT_PATH}/${SITE}/${PROBLEM_NO}-solve < "${BASE_PATH}/${LAST_INPUT_FILE}"
                echo "====================================================="
                echo " [*] RUN ${PROBLEM_NO} VERIFY APP"
                echo "====================================================="
                /usr/bin/timeout 2 ${OUTPUT_PATH}/${SITE}/${PROBLEM_NO}-verify < "${BASE_PATH}/${LAST_INPUT_FILE}"
                ;;
            txt)
                SITE=$(basename $(dirname $(realpath ${file_path})))
                PROBLEM_NO=$(basename $(realpath ${file_path}))
                BASE_PATH=$(realpath ${file_path})
                OUTPUT_PATH=$(realpath ${file_path}/../../output)
                BASE_NAME=$(basename $(realpath ${FILE}))
                LAST_INPUT_FILE=${BASE_NAME}

                echo "====================================================="
                echo " [*] RUN ${PROBLEM_NO} SOLVE APP"
                echo "====================================================="
                /usr/bin/timeout 2 ${OUTPUT_PATH}/${SITE}/${PROBLEM_NO}-solve < "${BASE_PATH}/${BASE_NAME}"
                echo "====================================================="
                echo " [*] RUN ${PROBLEM_NO} VERIFY APP"
                echo "====================================================="
                /usr/bin/timeout 2 ${OUTPUT_PATH}/${SITE}/${PROBLEM_NO}-verify < "${BASE_PATH}/${BASE_NAME}"

                ;;
        esac
    done
