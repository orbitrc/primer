SOURCES += src/range.cpp \
    src/string.cpp \
    src/json.cpp \
    tests/main.cpp \
    tests/range.cpp \
    tests/string.cpp \
    tests/json.cpp

HEADERS += include/primer/base.h \
    include/primer/range.h \
    include/primer/string.h \
    include/primer/json.h \
    tests/range.h \
    tests/string.h \
    tests/json.h

INCLUDEPATH += libprimer-core/include \
    ./include
