add_executable(primer-test
    range.h
    range.cpp
    string.h
    string.cpp
    vector.h
    vector.cpp
    json.h
    json.cpp
    format.h
    format.cpp
    hash-map.h
    hash-map.cpp
    byte-array.h
    byte-array.cpp
    d-bus.h
    d-bus.cpp
    main.cpp
)

target_include_directories(primer-test
    PRIVATE ../include
)

target_link_libraries(primer-test primer)

add_test(NAME primer-test
    COMMAND primer-test
)

