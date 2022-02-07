OBJ = range.o

default: $(OBJ)
	$(CXX) $(CFLAGS) $^ main.cpp -o primer-test -I../include -L../lib/ -lprimer -Wl,-rpath=../lib

%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $^ -I../include

run:
	LD_LIBRARY_PATH=../libprimer-core ./primer-test

clean:
	rm -f *.o
	rm -f primer-test
