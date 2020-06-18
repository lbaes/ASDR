default: asdr

asdr: asdr.c
	clang asdr.c -o asdr.exe -Wall

