Ciphertext: Ciphertext.o
	gcc -o Ciphertext Ciphertext.o

Ciphertext.o: Ciphertext.c
	gcc -c -g -Werror Ciphertext.c

clean:
	rm -f *.o Ciphertext huckleberry_finn_encrypt.txt hamlet_decrypt.txt
