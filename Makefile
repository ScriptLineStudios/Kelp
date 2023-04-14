main: main.c kasm/assembler.c
	gcc -o out main.c -Wall -Wextra -O3 -pedantic
	gcc -o kasma kasm/assembler.c -Wall -Wextra -O3 -pedantic
	gcc -o kemulator emulator/kemulator.c -Wall -Wextra -O3 -pedantic
	./out