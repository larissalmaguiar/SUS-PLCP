CC = gcc
CFLAGS += -Wall 
#CFLAGS += -g -O0
CFLAGS += -D_FILE_OFFSET_BITS=64 -m64 -O3 -fomit-frame-pointer -Wno-char-subscripts 

LFLAGS = -lm -lrt -ldl

LIBOBJ = \
	lib/sus.o\
	external/sacak-lcp.o\
	external/malloc_count/malloc_count.o

INPUT = dataset/example.txt

####

all: main

main: main.c ${LIBOBJ}
		gcc main.c -o main-sus ${LIBOBJ} $(CFLAGS) $(LFLAGS) 

clean:
	\rm -f main-sus lib/*.o external/*.o external/malloc_count/*.o

run:
	./main-sus $(INPUT) -1 -t
