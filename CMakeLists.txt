cmake_minimum_required(VERSION 3.5)

project(primer
    VERSION 0.4.0
    DESCRIPTION "Primer library"
    LANGUAGES CXX)

add_library(primer SHARED
    src/json.cpp
    src/range.cpp
    src/string.cpp
    src/format.cpp
    src/io.cpp
    src/d-bus.cpp
    include/primer/json.h
    include/primer/range.h
    include/primer/string.h
    include/primer/vector.h
    include/primer/format.h
    include/primer/io.h
    include/primer/d-bus.h
)

target_include_directories(primer
    PRIVATE ./include
    PRIVATE ./libprimer-core/include
)

target_compile_features(primer
    PRIVATE cxx_std_17)

target_compile_options(primer
    PRIVATE -Wall -Wextra -O2)
string(REPLACE "-O3" "" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
target_link_options(primer
    PRIVATE -O2)

# Link libdbus-1.
find_package(PkgConfig REQUIRED)
pkg_check_modules(DBUS REQUIRED dbus-1)

target_include_directories(primer
    PRIVATE ${DBUS_INCLUDE_DIRS})

target_link_options(primer
    PRIVATE -ldbus-1)

# Version info.
set_target_properties(primer PROPERTIES
    VERSION ${CMAKE_PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

# Link libprimer-core.
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
find_library(PRIMER_CORE_LIBRARY libprimer_core.a
    HINTS ./libprimer-core/target/release)
if (PRIMER_CORE_LIBRARY)
    target_link_libraries(primer PRIVATE ${PRIMER_CORE_LIBRARY})
else()
    message(FATAL_ERROR "libprimer_core.a not found!")
endif()

# Tests. For IDE.
add_custom_target(tests
    SOURCES
    ./tests/d-bus-server.cpp
    ./tests/d-bus-client.cpp
)
