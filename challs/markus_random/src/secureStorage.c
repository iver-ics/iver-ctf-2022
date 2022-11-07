#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int encrypt(char[256]);
void decrypt(char file[256], char decode_key[256]);

int main(int argc, char *argv[])
{
		////////////////////////////////////////////////
		// encryptor filename.enc decrytion
		// Example:  myEncrypt.enc 859302865
		// encrypts up to 4k(!) of data for you with a secret random key.
		////////////////////////////////////////////////
	if (argc ==1){
		printf("Usage: file, decrypt key\n\n");
	}
	if (argc ==2)
	{
        printf("Starting encryption \n\n");
		encrypt(argv[1]);
	}
	if (argc == 3)
	{
        printf("Starting decryption!\n");
		decrypt(argv[1],argv[2]);
	}
	return(0);
	
}

int encrypt(char file[256])
{
	long long int filesize;
	char textFromFile[4096];
	char encryptedData[4096];
	// Create a random number!
	int random = rand();
	// Save it as a string
	char randomNumber[256];
	sprintf(randomNumber,"%d", random);
	
	
	int randomNumberLength = strlen(randomNumber);
	// Give the number to the user.
    printf("Your secure random number is: %d\n",random);
	//Read the file and get all the data.
	FILE *fptr;
	if ((fptr = fopen(file,"r")) == NULL)
		{
			exit(1);
		}
	fseek(fptr,0,SEEK_END);
	filesize = ftell(fptr);
	rewind(fptr);

	// Read file to buffer and close file.
	fread(textFromFile,1,filesize+1,fptr);
	textFromFile[filesize]='\0';
	fclose(fptr);
    // now encrypt
	for(int i=0; i<filesize;i++)
	{
		encryptedData[i]= 	textFromFile[i] ^ randomNumber[i%randomNumberLength];
	}
	//Write a copy of the file with .enc extension.
    char encodedFileName[256];
    strcpy(encodedFileName,file);
    strcat(encodedFileName,".enc");
	FILE *fp;
    fp = fopen(encodedFileName,"wb");
    fputs(encryptedData,fp);
    fclose(fp);
    printf("Your file name is %s\n", encodedFileName);
	return(0);
}


void decrypt(char file[256], char decode_key[256])
{
    long long filesize;
	char *textFromFile;
    char decryptedData[4096];
    int decodeKeyLength;
    decodeKeyLength = strlen(decode_key);
    //Open file
	FILE *fptr;
	if ((fptr = fopen(file,"rb")) == NULL)
		{
			exit(1);
		}
	//Get size of data, and read in to a buffer.
	fseek(fptr,0,SEEK_END);
	filesize = ftell(fptr);
	rewind(fptr);
	fread(textFromFile,1,filesize+1,fptr);
	textFromFile[filesize]='\0';
	fclose(fptr);

	// Do XOR with the provided key!
	// And output the data to terminal so we keep it safe!
    for(int i=0; i<filesize;i++)
	{
		decryptedData[i]= 	textFromFile[i] ^ decode_key[i%decodeKeyLength];
	}
    printf("Your data is: \n%s\n",decryptedData);
}
