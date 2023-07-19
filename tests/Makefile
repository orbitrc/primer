OBJ = range.o \
	string.o \
	vector.o \
	json.o \
	format.o \
	hash-map.o

default: $(OBJ)
	$(CXX) $(CFLAGS) $^ main.cpp -o primer-test -I../include -L../build/ -lprimer -Wl,-rpath=../build
	$(CXX) $(CFLAGS) println.cpp -o println -I../include -L../build/ -lprimer -Wl,-rpath=../build

%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $^ -I../include

run:
	./primer-test

clean:
	rm -f *.o
	rm -f primer-test
