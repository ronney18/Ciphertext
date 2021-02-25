#include <stdio.h>
#include <ctype.h>

void storeAlphabet(char alphabet[]);
void encryptAlphabet(char alphabet[], char encrypt[]);
void decryptAlphabet(char encrypt[], char decrypt[]);
void printAlphabet(char alphabet[]);
void encryptMessage(char buffer[], int size);
void decryptMessage(char description[], int size);

int main(int argc char* argv[])
{
	if(argc != 3)
	{
		puts("ERROR: Incorrect number of arguments!");
		puts("./Ciphertext [original_file][encrypted_file]");
		return -1;
	}

	int size;
	char read;
	char alphabet[25];
	char alphabetEncrypt[25];
	char alphabetDecrypt[25];
	FILE *in_file_encryption;
	FILE *in_file_decryption;
	FILE *out_file_encryption;
	FILE *out_file_decryption;
	in_file_encryption = fopen(argv[1], "r");

	if(in_file_encryption == NULL)
	{
		puts("ERROR: File encryption cannot be opened!");
		return -2;
	}
	fseek(in_file_encryption, 0, SEEK_END);
	size = ftell(in_file_encryption);
	rewind(in_file_encryption);
	char buffer[size];
	int i = 0;
	while((read = fgetc(in_file_encryption)) != EOF)
	{
		buffer[i] = read;
		i++;
	}
	fclose(in_file_encryption);
	
	storeAlphabet(alphabet);
	encryptAlphabet(alphabet, alphabetEncrypt);

	puts("------------Ciphertext Encryption------------");
	printAlphabet(alphabet);
	printAlphabet(alphabetEncrypt);

	out_file_encryption = fopen("huckleberry_finn_encrypt.txt", "w");
	if(out_file_encryption == NULL)
	{
		puts("ERROR: Cannot write to the encrypted file!");
		return -3;
	}

	encryptMessage(buffer, size);

	for(i = 0; i < size; i++)
	{
		fputc(buffer[i], out_file_encryption);
	}
	fclose(out_file_encryption);
	puts("The Huckleberry Finn file has been encrypted!");

	in_file_decryption = fopen(argv[2], "r");

	if(in_file_decryption == NULL)
        {
                puts("ERROR: File decryption cannot be opened!");
                return -4;
        }
        fseek(in_file_decryption, 0, SEEK_END);
        size = ftell(in_file_decryption);
        rewind(in_file_decryption);
        char description[size];
        i = 0;
        while((read = fgetc(in_file_decryption)) != EOF)
        {
                description[i] = read;
                i++;
        }
        fclose(in_file_decryption);

	decryptAlphabet(alphabetEncrypt, alphabetDecrypt);
	printf("\n");
	puts("------------Ciphertext Decryption------------");
        printAlphabet(alphabetEncrypt);
	printAlphabet(alphabetDecrypt);

	out_file_decryption = fopen("hamlet_decrypt.txt", "w");
        if(out_file_decryption == NULL)
        {
                puts("ERROR: Cannot write to the decrypted file!");
                return -5;
        }

        decryptMessage(description, size);

        for(i = 0; i < size; i++)
        {
                fputc(description[i], out_file_decryption);
        }
        fclose(out_file_decryption);
        puts("The Hamlet file has been decrypted!");
	return 0;
}

void storeAlphabet(char alphabet[])
{
	char letter = 65;
        for(int i = 0; i < 26; i++)
        {
                alphabet[i] = letter;
                letter = letter + 1;
        }
}

void encryptAlphabet(char alphabet[], char encrypt[])
{
        int start = 65;
        for(int i = 0; i < 26; i++)
        {
                encrypt[i] = start + ((3 * alphabet[i] + 8) % 26);
        }
}

void decryptAlphabet(char encrypt[], char decrypt[])
{
	int start = 65;
        for(int i = 0; i < 26; i++)
        {
                decrypt[i] = start + (((encrypt[i] - 8) * 9) % 26);
        }
}

void printAlphabet(char alphabet[])
{
	for(int i = 0; i < 26; i++)
        {
                printf("%c", alphabet[i]);
                if(i != 25)
                {
                        printf(" ");
                }
        }
        printf("\n");
}

void encryptMessage(char buffer[], int size)
{
	for(int i = 0; i < size; i++)
        {
                if((buffer[i] >= 65 && buffer[i] <= 90) || (buffer[i] >= 97 && buffer[i] <= 122))
                {
			int start = 65;
			if(islower(buffer[i]))
			{
				buffer[i] = toupper(buffer[i]);
				buffer[i] = tolower(start + ((3 * buffer[i] + 8) % 26));
			}
			else
			{
                                buffer[i] = start + ((3 * buffer[i] + 8) % 26);
			}
                }
	}
}

void decryptMessage(char description[], int size)
{
        for(int i = 0; i < size; i++)
        {
                if((description[i] >= 65 && description[i] <= 90) || (description[i] >= 97 && description[i] <= 122))
                {
                        int start = 65;
			if(islower(description[i]))
			{
				description[i] = toupper(description[i]);
				description[i] = tolower(start + (((description[i] - 8) * 9) % 26));
			}
			else
			{
				description[i] = start + (((description[i] - 8) * 9) % 26);
			}
		}
	}
}
