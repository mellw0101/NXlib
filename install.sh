#!/bin/bash

cmake -B build
cmake --build build

sudo cmake --install build --prefix /usr/local