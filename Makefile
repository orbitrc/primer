VERSION_MAJOR=$(shell cd libprimer-core ; make version-major)
VERSION_MINOR=$(shell cd libprimer-core ; make version-minor)
VERSION_PATCH=$(shell cd libprimer-core ; make version-patch)
VERSION = $(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH)
SONAME = libprimer.so.$(VERSION_MAJOR)

INSTALL_DIR=$(shell tools/dist-install-dir.sh)

OBJ = src/range.o \
	src/string.o \
	src/json.o
CXXFLAGS = -std=c++17 -Iinclude -Ilibprimer-core/include

default:
	mkdir -p build
	cd build && cmake ..
	cd build && make

src/%.o: src/%.cpp
	$(CXX) -c -Iinclude $(CXXFLAGS) -fPIC -o $@ $<

test:
	$(MAKE) -C tests/

install:
	strip lib/libprimer.so.$(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH)
	cp include/primer/*.h /usr/include/primer/
	cp lib/libprimer.so.$(VERSION) $(INSTALL_DIR)
	cp -P lib/libprimer.so.$(VERSION_MAJOR).$(VERSION_MINOR) $(INSTALL_DIR)
	cp -P lib/libprimer.so.$(VERSION_MAJOR) $(INSTALL_DIR)
	cp -P lib/libprimer.so $(INSTALL_DIR)

clean:
	rm -rf src/*.o
	rm -rf lib/
	rm tests/*.o
	rm tests/primer-test
