#!/bin/sh
find acmicpc_net goorm_io \( -name "*.c" -or -name "*.h" \) -exec uncrustify -c coding-rule.fmt -l c --replace --no-backup {} \;
