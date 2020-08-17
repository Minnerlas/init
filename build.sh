#!/bin/sh

MAKE_FLAGS=""

[ ! -d "./build" ] && mkdir build
[ ! -d "./run" ] && mkdir run

cd init
make $MAKE_FLAGS
echo

cd ../initsv
make $MAKE_FLAGS
echo

cd ../sv
make $MAKE_FLAGS
echo

