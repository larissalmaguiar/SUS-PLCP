all: algoritmo
algoritmo: algoritmo.o sacak-lcp.o sus.o
		gcc algoritmo.o sacak-lcp.o sus.o -lm -o algoritmo
algoritmo.o: algoritmo.c sacak-lcp.h sus.h
		gcc -Wall -Werror -c algoritmo.c
sacak-lcp.o: sacak-lcp.c sacak-lcp.h
		gcc -Wall -Werror -c sacak-lcp.c
sus.o: sus.c sus.h
		gcc -Wall -Werror -c sus.c
