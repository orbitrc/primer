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

default: $(OBJ)
	mkdir -p lib
	$(CXX) -shared -Wl,-soname,$(SONAME) -o lib/libprimer.so.$(VERSION) $^ -Iinclude -Llibprimer-core -lprimer-core
	rm -f lib/libprimer.so.$(VERSION_MAJOR).$(VERSION_MINOR) lib/libprimer.so.$(VERSION_MAJOR) lib/libprimer.so
	ln -s libprimer.so.$(VERSION) lib/libprimer.so.$(VERSION_MAJOR).$(VERSION_MINOR)
	ln -s libprimer.so.$(VERSION_MAJOR).$(VERSION_MINOR) lib/libprimer.so.$(VERSION_MAJOR)
	ln -s libprimer.so.$(VERSION_MAJOR) lib/libprimer.so

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
