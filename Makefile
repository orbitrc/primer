OBJ = src/Int.o src/Array.o \
	src/utils.o
CXXFLAGS = -std=c++17

default: $(OBJ)
	mkdir -p lib
	$(CXX) $(CXXFLAGS) -shared -Wl,-soname,$(SONAME) -o lib/libprimer.so.$(LIBRARY_VERSION) $^ -Iinclude
	rm -f lib/libprimer.so.0.0 lib/libprimer.so.0 lib/libprimer.so
	ln -s libprimer.so.$(LIBRARY_VERSION) lib/libprimer.so.0.0
	ln -s libprimer.so.0.0 lib/libprimer.so.0
	ln -s libprimer.so.0 lib/libprimer.so

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -Iinclude -fPIC -o $@ $<

test:
	$(MAKE) -C tests/

clean:
	rm -rf src/*.o
	rm -rf lib/
