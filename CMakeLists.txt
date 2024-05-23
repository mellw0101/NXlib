#[[cmake_minimum_required(VERSION 3.28)
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
)]]

cmake_minimum_required(VERSION 3.28)
project(NXlib)

set(CMAKE_CXX_STANDARD 20)

# Define the sources and headers for the library
set(NXLIB_SOURCES
        window.cpp
        lout.cpp
        TIME.cpp
        prof.cpp
        tools.cpp
        color.cpp
        NXlib.cpp
        Key_Codes.cpp
        Pid_Manager.cpp
)

set(NXLIB_HEADERS
        window.h
        lout.h
        TIME.h
        prof.h
        tools.h
        globals.h
        color.h
        NXlib.h
        Key_Codes.h
        Pid_Manager.h
)

# Create the static library
add_library(NXlib_static STATIC ${NXLIB_SOURCES} ${NXLIB_HEADERS})

# Create the shared library
add_library(NXlib_shared SHARED ${NXLIB_SOURCES} ${NXLIB_HEADERS})

# Specify the include directories for the libraries
target_include_directories(NXlib_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(NXlib_shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Set the properties for the shared library
set_target_properties(NXlib_shared PROPERTIES OUTPUT_NAME "NXlib")

# Set the properties for the static library
set_target_properties(NXlib_static PROPERTIES OUTPUT_NAME "NXlib")

# Install the static library
install(TARGETS NXlib_static
        ARCHIVE DESTINATION lib
)

# Install the shared library
install(TARGETS NXlib_shared
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)

# Install the header files
install(FILES ${NXLIB_HEADERS}
        DESTINATION include/NXlib
)

#cmake_minimum_required(VERSION 3.28)
#project(NXlib)
#
#set(CMAKE_CXX_STANDARD 20)
#
## Define the sources and headers for the library
#set(NXLIB_SOURCES
#        window.cpp
#        lout.cpp
#        TIME.cpp
#        prof.cpp
#        tools.cpp
#        color.cpp
#        NXlib.cpp
#)
#
#set(NXLIB_HEADERS
#        window.h
#        lout.h
#        TIME.h
#        prof.h
#        tools.h
#        globals.h
#        color.h
#        NXlib.h
#)
#
## Specify the include directories for the libraries
#target_include_directories(NXlib_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#target_include_directories(NXlib_shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#
## Set the properties for the shared library
#set_target_properties(NXlib_shared PROPERTIES OUTPUT_NAME "NXlib")
#
## Set the properties for the static library
#set_target_properties(NXlib_static PROPERTIES OUTPUT_NAME "NXlib")
#
## Install the static library
#install(TARGETS NXlib_static
#        ARCHIVE DESTINATION lib
#)
#
## Install the shared library
#install(TARGETS NXlib_shared
#        LIBRARY DESTINATION lib
#        RUNTIME DESTINATION bin
#)
#
## Install the header files
#install(FILES ${NXLIB_HEADERS}
#        DESTINATION include/NXlib
#)

#[[
cmake_minimum_required(VERSION 3.28)
project(NXlib)

set(CMAKE_CXX_STANDARD 20)

# Define the sources and headers for the library
set(NXLIB_SOURCES
        window.cpp
        lout.cpp
        TIME.cpp
        prof.cpp
        tools.cpp
        color.cpp
        NXlib.cpp
)

set(NXLIB_HEADERS
        window.h
        lout.h
        TIME.h
        prof.h
        tools.h
        globals.h
        color.h
        NXlib.h
)

# Create the static library
add_library(NXlib_static STATIC ${NXLIB_SOURCES} ${NXLIB_HEADERS})

# Create the shared library
add_library(NXlib_shared SHARED ${NXLIB_SOURCES} ${NXLIB_HEADERS})

# Specify the include directories for the libraries
target_include_directories(NXlib_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(NXlib_shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Set the properties for the shared library
set_target_properties(NXlib_shared PROPERTIES OUTPUT_NAME "NXlib")

# Set the properties for the static library
set_target_properties(NXlib_static PROPERTIES OUTPUT_NAME "NXlib")

# Install the static library
install(TARGETS NXlib_static
        ARCHIVE DESTINATION lib
)
]]

