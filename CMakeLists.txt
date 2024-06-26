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
        Bitmap.cpp
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
        Bitmap.h
)

# Find libpng
find_package(PNG REQUIRED)

# Find imlib2 using pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(IMLIB2 REQUIRED imlib2)

# Find XCB using pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(XCB REQUIRED xcb xcb-ewmh xcb-keysyms xcb-proto xcb-cursor xcb-icccm)

# Include directories
include_directories(${IMLIB2_INCLUDE_DIRS} ${PNG_INCLUDE_DIRS} ${XCB_INCLUDE_DIRS})

# Create the static library
add_library(NXlib_static STATIC ${NXLIB_SOURCES} ${NXLIB_HEADERS})

# Create the shared library
add_library(NXlib_shared SHARED ${NXLIB_SOURCES} ${NXLIB_HEADERS})

# Specify the include directories for the libraries
target_include_directories(NXlib_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(NXlib_shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link the static versions of the required libraries to the shared library
target_link_libraries(NXlib_shared
        ${IMLIB2_STATIC_LIBRARIES}
        ${PNG_STATIC_LIBRARIES}
        ${XCB_LIBRARIES}
        ${XCB_STATIC_LIBRARIES}
)

target_link_libraries(NXlib_static
        ${IMLIB2_STATIC_LIBRARIES}
        ${PNG_STATIC_LIBRARIES}
        ${XCB_LIBRARIES}
        ${XCB_STATIC_LIBRARIES}
)

# Set the properties for the shared library
set_target_properties(NXlib_shared PROPERTIES OUTPUT_NAME "NXlib")

# Set the properties for the static library
set_target_properties(NXlib_static PROPERTIES OUTPUT_NAME "NXlib")

# Add optimization flags
target_compile_options(NXlib_static PRIVATE -O3 -march=native)
target_compile_options(NXlib_shared PRIVATE -O3 -march=native)

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
