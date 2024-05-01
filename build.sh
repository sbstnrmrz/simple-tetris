#!/bin/bash

CC="clang"
CCFLAGS="-Wall -Wextra"
IFLAGS=""
LFLAGS=""
LIBS="-lm -lSDL3"
SRC="src/*.c"

$CC $CCFLAGS $SRC -o main $LIBS
