BASE_DIR := .

BUILD_DIR := ${BASE_DIR}/build
TARGET_DIR := ${BASE_DIR}/output

SUBMAKEFILES := $(wildcard acmicpc_net/p-*/target.mk) $(wildcard groom_io/p-*/target.mk)
