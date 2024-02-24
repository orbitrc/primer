# File: tests/string/CMakeLists.txt

file(GLOB CXX_SOURCES "*.cpp")
foreach(CXX_SOURCE ${CXX_SOURCES})
    get_filename_component(TEST_NAME ${CXX_SOURCE} NAME_WE)
    list(APPEND TEST_NAMES ${TEST_NAME})
endforeach()


foreach(TEST_NAME ${TEST_NAMES})
    set(TEST_FULL_NAME primer.string.${TEST_NAME})
    add_executable(${TEST_FULL_NAME}
        ${TEST_NAME}.cpp
    )
    target_include_directories(${TEST_FULL_NAME}
        PRIVATE ${CMAKE_SOURCE_DIR}/include
    )
    target_link_libraries(${TEST_FULL_NAME} primer)

    add_test(NAME ${TEST_FULL_NAME}
        COMMAND ${TEST_FULL_NAME}
    )
    set_target_properties(${TEST_FULL_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${PRIMER_TEST_BINARY_DIR}
    )
endforeach()

