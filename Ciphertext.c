#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

void storeCharacters(char characters[]);
void encryptCharacters(char characters[], char encrypt[]);
void decryptCharacters(char encrypt[], char decrypt[]);
void printCharacters(char characters[]);
void encryptMessage(char* buffer, int size);
void decryptMessage(char* description, int size);

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		puts("ERROR: Incorrect number of arguments!");
		puts("./Ciphertext [original_file][encrypted_file]");
		return -1;
	}

	else
	{
		int size;
		char read;
		char asciiCharacters[94];
		char asciiEncrypt[94];
		char asciiDecrypt[94];
		FILE *in_file_encryption;
		FILE *in_file_decryption;
		FILE *out_file_encryption;
		FILE *out_file_decryption;
		in_file_encryption = fopen(argv[1], "r");

		if(in_file_encryption == NULL)
		{
			perror("ERROR: File encryption cannot be opened!");
			exit(EXIT_FAILURE);
		}
		fseek(in_file_encryption, 0, SEEK_END);
		size = ftell(in_file_encryption);
		rewind(in_file_encryption);
		char buffer[size];
		int i = 0;
		while((read = fgetc(in_file_encryption)) != EOF)
		{
			*(buffer + i) = read;
			i++;
		}
		fclose(in_file_encryption);
	
		storeCharacters(asciiCharacters);
		encryptCharacters(asciiCharacters, asciiEncrypt);

		puts("------------Ciphertext Encryption------------");
		printCharacters(asciiCharacters);
		puts("---------------------------------------------");
		printCharacters(asciiEncrypt);

		out_file_encryption = fopen("huckleberry_finn_encrypt.txt", "w");
		if(out_file_encryption == NULL)
		{
			perror("ERROR: Cannot write to the encrypted file!");
			exit(EXIT_FAILURE);
		}

		encryptMessage(buffer, size);

		for(i = 0; i < size; i++)
		{
			fputc(*(buffer + i), out_file_encryption);
		}
		fclose(out_file_encryption);
		puts("The Huckleberry Finn file has been encrypted!");

		in_file_decryption = fopen(argv[2], "r");

		if(in_file_decryption == NULL)
        	{
                	perror("ERROR: File decryption cannot be opened!");
                	exit(EXIT_FAILURE);
        	}
        	fseek(in_file_decryption, 0, SEEK_END);
        	size = ftell(in_file_decryption);
        	rewind(in_file_decryption);
        	char description[size];
        	i = 0;
        	while((read = fgetc(in_file_decryption)) != EOF)
        	{
                	*(description + i) = read;
                	i++;
        	}
        	fclose(in_file_decryption);

		decryptCharacters(asciiEncrypt, asciiDecrypt);
		printf("\n");
		puts("------------Ciphertext Decryption------------");
        	printCharacters(asciiEncrypt);
		puts("---------------------------------------------");
		printCharacters(asciiDecrypt);

		out_file_decryption = fopen("hamlet_decrypt.txt", "w");
        	if(out_file_decryption == NULL)
        	{
                	perror("ERROR: Cannot write to the decrypted file!");
                	exit(EXIT_FAILURE);
        	}

        	decryptMessage(description, size);

        	for(i = 0; i < size; i++)
        	{
                	fputc(*(description + i), out_file_decryption);
        	}
        	fclose(out_file_decryption);
        	puts("The Hamlet file has been decrypted!");
	}
	return 0;
}

void storeCharacters(char characters[])
{
	char asciiCode = 33;
        for(int i = 0; i < 94; i++)
        {
                characters[i] = asciiCode;
                asciiCode = asciiCode + 1;
        }
}

void encryptCharacters(char characters[], char encrypt[])
{
        int start = 33;
        for(int i = 0; i < 94; i++)
        {
                encrypt[i] = start + (5 * (characters[i] - start) % 94);
        }
}

void decryptCharacters(char encrypt[], char decrypt[])
{
	int start = 33;
        for(int i = 0; i < 94; i++)
        {
                decrypt[i] = start + (((encrypt[i] - start) * 19) % 94);
        }
}

void printCharacters(char characters[])
{
	for(int i = 0; i < 94; i++)
        {
                printf("%c", characters[i]);
                if(i != 93)
                {
                        printf(" ");
                }
        }
        printf("\n");
}

void encryptMessage(char* buffer, int size)
{
	int start = 33;
	for(int i = 0; i < size; i++)
        {
                if(*(buffer + i) >= 33 && *(buffer + i) <= 126)
                {
                        *(buffer + i) = start + ((5 * (*(buffer + i) - start)) % 94);
                }
	}
}

void decryptMessage(char* description, int size)
{
	int start = 33;
        for(int i = 0; i < size; i++)
        {
                if(*(description + i) >= 33 && *(description + i) <= 126)
                {
			*(description + i) = start + (((*(description + i) - start) * 19) % 94);
		}
	}
}
