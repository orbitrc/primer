cmake_minimum_required(VERSION 3.5)

project(primer
    VERSION 0.5.0
    DESCRIPTION "Primer library"
    LANGUAGES CXX)

set(PRIMER_DECL_HEADER_FILES
    include/primer/decl/string.h
)

set(PRIMER_HEADER_FILES
    include/primer/json.h
    include/primer/range.h
    include/primer/string.h
    include/primer/vector.h
    include/primer/hash-map.h
    include/primer/byte-array.h
    include/primer/format.h
    include/primer/io.h
    include/primer/d-bus.h
)

add_library(primer SHARED
    src/json.cpp
    src/range.cpp
    src/string.cpp
    src/byte-array.cpp
    src/format.cpp
    src/io.cpp
    src/d-bus.cpp
    ${PRIMER_DECL_HEADER_FILES}
    ${PRIMER_HEADER_FILES}
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

# Install
include(GNUInstallDirs)

set_target_properties(primer PROPERTIES
    PUBLIC_HEADER
    "${PRIMER_HEADER_FILES}"
)

install(TARGETS primer
    DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER
    DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/primer
)
install(
    FILES ${PRIMER_DECL_HEADER_FILES}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/primer/decl
)

# Tests. For IDE.
add_custom_target(tests
    SOURCES
    ./tests/vector.h
    ./tests/vector.cpp
    ./tests/string.h
    ./tests/string.cpp
    ./tests/d-bus.h
    ./tests/d-bus.cpp
    ./tests/d-bus-server.cpp
    ./tests/d-bus-client.cpp
    ./tests/main.cpp
)
