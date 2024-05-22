#!/bin/bash

cmake -B build
cmake --build build

cd ./build

sudo cmake --install .