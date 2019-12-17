#!/usr/bin/env bash

# TODO: Check -H. and -BDebug
cmake -H. -BDebug -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=YES
[ ! -e ./compile_commands.json ] && ln -s Debug/compile_commands.json
cd Debug
make

