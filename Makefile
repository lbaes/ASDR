default: asdr-clang

asdr-clang: asdr.c
	clang asdr.c -o asdr.exe -Wall -std=c11

asdr-mingw: asdr.c
	gcc asdr.c -o asdrgcc.exe -Wall -std=c11
