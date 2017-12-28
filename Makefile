all: bin/hex

lib/kontroll.o: src/kontroll.c src/head_hex.h
	gcc -Wall -g -c -o $@ src/kontroll.c

lib/main.o: src/main.c src/head_hex.h
	gcc -Wall -g -c -o $@ src/main.c

lib/meny.o: src/meny.c src/head_hex.h
	gcc -Wall -g -c -o $@ src/meny.c

lib/misc.o: src/misc.c src/head_hex.h
	gcc -Wall -g -c -o $@ src/misc.c

lib/read_hex.o: src/read_hex.c src/head_hex.h
	gcc -Wall -g -c -o $@ src/read_hex.c -lm

lib/set.o: src/set.c src/head_hex.h
	gcc -Wall -g -c -o $@ src/set.c

lib/write_hex.o: src/write_hex.c src/head_hex.h
	gcc -Wall -g -c -o $@ src/write_hex.c

bin/hex: lib/kontroll.o lib/main.o lib/meny.o lib/misc.o lib/read_hex.o lib/set.o lib/write_hex.o src/head_hex.h
	gcc -Wall -g -o $@ lib/kontroll.o lib/main.o lib/meny.o lib/misc.o lib/read_hex.o lib/set.o lib/write_hex.o -lm

clean:
	rm -v lib/*.o bin/hex
