OBJ = range.o \
	string.o \
	vector.o \
	json.o \
	format.o \
	hash-map.o \
	byte-array.o \
	d-bus.o

default: $(OBJ)
	$(CXX) $(CFLAGS) $^ main.cpp -o primer-test -I../include -L../build/ -lprimer -Wl,-rpath=../build
	$(CXX) $(CFLAGS) println.cpp -o println -I../include -L../build/ -lprimer -Wl,-rpath=../build

d-bus:
	$(CXX) $(CFLAGS) d-bus-server.cpp -o d-bus-server -I../include -L../build/ -lprimer -Wl,-rpath=../build
	$(CXX) $(CFLAGS) d-bus-client.cpp -o d-bus-client -I../include -L../build/ -lprimer -Wl,-rpath=../build

%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $^ -I../include

run:
	./primer-test

clean:
	rm -f *.o
	rm -f primer-test
