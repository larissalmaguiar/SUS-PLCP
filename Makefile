CC = gcc
CFLAGS += -Wall 
#CFLAGS += -g -O0
CFLAGS += -D_FILE_OFFSET_BITS=64 -O3 -fomit-frame-pointer -Wno-char-subscripts 

LFLAGS = -lm -lrt -ldl

LIBOBJ = \
	lib/sus.o\
	lib/file.o\
	lib/utils.o\
	external/gsacak.o\
	external/malloc_count/malloc_count.o

INPUT = dataset/example.txt
ALG = 1

# Função para verificar o tamanho dos arquivos em LIBOBJ e definir M64
M64 := $(shell for file in $(LIBOBJ); do if [ -f $$file ] && [ $$(stat -c%s $$file) -gt 2147483648 ]; then echo 1; exit; fi; done; echo 0)

# Adicionar -m64 a CFLAGS se M64 for 1
ifeq ($(M64),1)
    CFLAGS += -m64
endif

####

all: main

main: main.c ${LIBOBJ}
	$(CC) main.c -o main-sus ${LIBOBJ} $(CFLAGS) $(LFLAGS) 

clean:
	\rm -f main-sus lib/*.o external/*.o external/malloc_count/*.o

run:
	./main-sus $(INPUT) -A $(ALG) -t
