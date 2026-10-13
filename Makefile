CC = gcc
CFLAGS = -Wall -Wextra -O2
LIBS = -lgmp

all: rsa gerar_chaves

rsa: rsa.c
	$(CC) $(CFLAGS) rsa.c -o rsa $(LIBS)

gerar_chaves: gerar_chaves.c
	$(CC) $(CFLAGS) gerar_chaves.c -o gerar_chaves $(LIBS)

clean:
	rm -f rsa gerar_chaves