BASE_DIR := .

BUILD_DIR := ${BASE_DIR}/build
TARGET_DIR := ${BASE_DIR}/output

SUBMAKEFILES := $(wildcard acmicpc_net/w-*/target.mk) $(wildcard goorm_io/w-*/target.mk)
