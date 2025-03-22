GIT_TAG := $(shell git describe --tags --always)
BIN_NAME := ipspoon

all: main

main:
	@gcc -DIPSPOON_VERSION="\"${GIT_TAG}"\" -o ${BIN_NAME} main.c

clean:
	@rm -f ipspoon
