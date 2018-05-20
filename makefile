all:		vigenere

vigenere:	vigenere.c vigenere.h
	gcc -o vigenere vigenere.c

clean:
	rm -f *.o vigenere
