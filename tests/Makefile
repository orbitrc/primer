OBJ = main.o

default: $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o primer-test -I../include -L../lib/ -lprimer -Wl,-rpath=../lib

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^ -I../include
