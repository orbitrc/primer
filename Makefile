VERSION_MAJOR=0
VERSION_MINOR=4
VERSION_PATCH=0
VERSION = $(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH)
SONAME = libprimer.so.$(VERSION_MAJOR)

INSTALL_DIR=$(shell tools/dist-install-dir.sh)

PREFIX ?= /usr/local

OBJ = src/range.o \
	src/string.o \
	src/json.o
CXXFLAGS = -std=c++17 -Iinclude -Ilibprimer-core/include

default:
	cd libprimer-core && make
	mkdir -p build
	cd build && cmake ..
	cd build && make

src/%.o: src/%.cpp
	$(CXX) -c -Iinclude $(CXXFLAGS) -fPIC -o $@ $<

test:
	$(MAKE) -C tests/

install:
	strip build/libprimer.so.$(VERSION)
	cp include/primer/*.h $(DESTDIR)/$(PREFIX)/include/primer/
	cp build/libprimer.so.$(VERSION) $(DESTDIR)/$(PREFIX)/lib/
	ln -sf libprimer.so.$(VERSION) \
		$(DESTDIR)/$(PREFIX)/lib/libprimer.so.$(VERSION_MAJOR).$(VERSION_MINOR)
	ln -sf libprimer.so.$(VERSION_MAJOR).$(VERSION_MINOR) \
		$(DESTDIR)/$(PREFIX)/lib/libprimer.so.$(VERSION_MAJOR)
	ln -sf libprimer.so.$(VERSION_MAJOR) \
		$(DESTDIR)/$(PREFIX)/lib/libprimer.so

clean:
	rm -rf build/
	rm tests/*.o
	rm tests/primer-test
