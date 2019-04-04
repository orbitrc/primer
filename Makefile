OBJ = src/Int.o
CXXFLAGS = -std=c++17

default: $(OBJ)
	mkdir -p lib
	$(CXX) $(CXXFLAGS) -shared -o lib/libprimer.so $^ -Iinclude

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -Iinclude -o $@ $<

test:
	$(MAKE) -C tests/
