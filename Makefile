VERSION = 0.0.1
VERSION_MAJOR = 0
VERSION_MINOR = 0
VERSION_PATCH = 1
SONAME = libprimer.so.$(VERSION)

OBJ = src/range.o
CXXFLAGS = -std=c++17 -Iinclude -Ilibprimer-core/include

default: $(OBJ)
	mkdir -p lib
	$(CXX) -shared -Wl,-soname,$(SONAME) -o lib/libprimer.so.$(VERSION) $^ -Iinclude
	rm -f lib/libprimer.so.0.0 lib/libprimer.so.0 lib/libprimer.so
	ln -s libprimer.so.$(VERSION) lib/libprimer.so.0.0
	ln -s libprimer.so.0.0 lib/libprimer.so.0
	ln -s libprimer.so.0 lib/libprimer.so

src/%.o: src/%.c
	$(CXX) -c -Iinclude -fPIC -o $@ $<

test:
	$(MAKE) -C tests/

clean:
	rm -rf src/*.o
	rm -rf lib/
	rm tests/*.o
	rm tests/primer-test
