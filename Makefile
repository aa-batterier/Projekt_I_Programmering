all: hex

kontroll.o: kontroll.c head_hex.h
	gcc -Wall -g -c -o $@ kontroll.c

main.o: main.c head_hex.h
	gcc -Wall -g -c -o $@ main.c

meny.o: meny.c head_hex.h
	gcc -Wall -g -c -o $@ meny.c

misc.o: misc.c head_hex.h
	gcc -Wall -g -c -o $@ misc.c

read_hex.o: read_hex.c head_hex.h
	gcc -Wall -g -c -o $@ read_hex.c -lm

set.o: set.c head_hex.h
	gcc -Wall -g -c -o $@ set.c

write_hex.o: write_hex.c head_hex.h
	gcc -Wall -g -c -o $@ write_hex.c

hex: kontroll.o main.o meny.o misc.o read_hex.o set.o write_hex.o head_hex.h
	gcc -Wall -g -o $@ kontroll.o main.o meny.o misc.o read_hex.o set.o write_hex.o -lm

clean:
	rm -v *.o hex
