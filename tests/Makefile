OBJ = main.o

default: $(OBJ)
	$(CC) $(CFLAGS) $^ -o primer-test -I../include -L../lib/ -lprimer -Wl,-rpath=../lib

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^ -I../include

clean:
	rm -f *.o
	rm -f primer-test
