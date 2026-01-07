OBJ = $(patsubst %.c, %.o, $(wildcard *.c))

inv: $(OBJ)
	gcc -o $@ $^

clean:
	rm -f *.o