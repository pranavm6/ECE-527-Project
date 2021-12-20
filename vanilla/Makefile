CC=gcc
CFLAGS=-I.
DEPS = decoder.h encoder.h utilities.h field.h
OBJ = utility.o field.o encoder.o decoder.o

%.o: %.c $(DEPS)
	$(CC) -o $@ $< $(CFLAGS)

encoder: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf decoder encoder *.o