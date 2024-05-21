cmake_minimum_required(VERSION 3.28)
project(NXlib)

set(CMAKE_CXX_STANDARD 20)

add_library(NXlib STATIC
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
        color.cpp
        color.h
)

# Specify the include directories for the library
target_include_directories(NXlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Install the library
install(TARGETS NXlib
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)

# Install the header files
install(FILES
        window.h
        lout.h
        TIME.h
        prof.h
        tools.h
        globals.h
        DESTINATION include/NXlib
)