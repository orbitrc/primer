OBJ = range.o \
	string.o \
	vector.o \
	json.o

default: $(OBJ)
	$(CXX) $(CFLAGS) $^ main.cpp -o primer-test -I../include -I../libprimer-core/include -L../build/ -lprimer -Wl,-rpath=../build

%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $^ -I../include

run:
	./primer-test

clean:
	rm -f *.o
	rm -f primer-test
