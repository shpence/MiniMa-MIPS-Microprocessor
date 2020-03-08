SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

%.o: %.c
	gcc -Wall -std=c18 -g -c -o $@ $<

AssemblerTest: $(OBJ)
	gcc -o $@ $^ 

clean:
	rm -rf *.o AssemberTest
