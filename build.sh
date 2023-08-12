#!/bin/sh

set -xe

mkdir -p bin
cd bin

CC=gcc
CFLAGS="-Wall -Wextra -Wno-address -std=c11 -std=gnu11 -ggdb"

# Build violet
src=../src/violet.c
name=violet
$CC $CFLAGS -o $name $src

# Build test
test=../test/test.c
test_name=violet_test
$CC $CFLAGS -o violet_test $test

./violet_test

cd ..

