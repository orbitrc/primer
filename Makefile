OBJ = src/Int.o
CXXFLAGS = -std=c++17

default: $(OBJ)
	mkdir -p lib
	$(CXX) $(CXXFLAGS) -shared -Wl,-soname,$(SONAME) -o lib/libprimer.so.$(LIBRARY_VERSION) $^ -Iinclude
	ln -s libprimer.so.$(LIBRARY_VERSION) lib/libprimer.so.0.0
	ln -s libprimer.so.0.0 lib/libprimer.so.0

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -Iinclude -o $@ $<

test:
	$(MAKE) -C tests/

clean:
	rm -rf lib/
