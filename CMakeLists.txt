cmake_minimum_required(VERSION 3.28)
project(NXlib)

set(CMAKE_CXX_STANDARD 20)

add_library(NXlib STATIC library.cpp
        window.cpp
        window.h
        lout.cpp
        lout.h
        TIME.cpp
        TIME.h
        prof.cpp
        prof.h
        tools.cpp
        tools.h
        globals.h
)
