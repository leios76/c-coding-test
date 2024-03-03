#!/bin/sh
NAME=$(printf "%05d" $1)
BASE=$(basename $(realpath .))

~/.cargo/bin/cargo init --name ${BASE}-${NAME} w-${NAME}
