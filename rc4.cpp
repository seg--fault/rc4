#include "rc4.h"
#include <iostream>

rc4_stream_cipher::rc4_stream_cipher(char* key, int key_length)
{
	//Set each byte in the permutation array to its location in the array
	for(unsigned int i=0; i<256; i++)
	{
		byte_permutation[i] = (char)i;
	}

	unsigned int j = 0;

	//Permute the bytes
	for(unsigned int i=0; i<256; i++)
	{
		j = (j + byte_permutation[i] + key[i%key_length])%256;
		char old_value = byte_permutation[j];
		byte_permutation[j] = byte_permutation[i];
		byte_permutation[i] = old_value;
	}
}

void rc4_stream_cipher::transform(char* input, char* output, unsigned int length)
{
	//Iterate through each byte in the input
	for(int i=0; i<length; i++)
	{
		//XOR it with the next byte in the cipher stream
		output[i] = input[i]^cipher_stream_next_byte();
	}

	return;
}

char rc4_stream_cipher::cipher_stream_next_byte()
{
	//Initialize two array indices
	unsigned int i = 0;
	unsigned int j = 0;

	//Get the new array indices
	i = (i + 1)%256;
	j = (j + byte_permutation[i])%256;

	//Swap the values in the permutation at the indices
	char old_value = byte_permutation[j];
	byte_permutation[j] = byte_permutation[i];
	byte_permutation[i] = old_value;

	//Compute the next cipherstream byte
	return byte_permutation[(byte_permutation[i] + byte_permutation[j])%256];
}

unsigned int rc4::bin_length(char* input)
{
	unsigned int i;
	for(i=0; input[i] != '\0'; i++) {};
	i--;

	return i/2;
}

void rc4::hex_to_bin(char* input, char* output)
{
	//Get the length of the output
	unsigned int length = bin_length(input);

	//Go through each character of the output
	for(unsigned int i=0; i<length; i++)
	{
		output[i] = hex_to_byte(input[2*i], input[2*i+1]);
	}

	return;
}

void rc4::bin_to_hex(char* input, unsigned int length, char* output)
{
	//Go through each byte of the input
	for(int i=0; i<length; i++)
	{
		//Get the msn and lsn
		output[2*i] = msn(input[i]);
		output[2*i+1] = lsn(input[i]);
	}

	//Append a null terminator
	output[2*length] = '\0';

	return;
}

char rc4::hex_to_byte(char msn, char lsn)
{
	char return_byte;

	//Find out the most significant byte
	if(msn >= '0' && msn <= '9')
		return_byte = msn - '0';
	else
	if(msn >= 'a' && msn <= 'f')
		return_byte = msn - 'a' + 10;
	else
	if(msn >= 'A' && msn <= 'F')
		return_byte = msn - 'A' + 10;
	else
		return (char)0;

	//Shift over the msn
	return_byte = return_byte << 4;

	if(lsn >= '0' && lsn <= '9')
		return_byte += lsn - '0';
	else
	if(lsn >= 'a' && lsn <= 'f')
		return_byte += lsn - 'a' + 10;
	else
	if(lsn >= 'A' && lsn <= 'F')
		return_byte += lsn - 'A' + 10;
	else
		return (char)0;

	return return_byte;
}

char rc4::msn(char byte)
{
	//Move the most significant nibble into the least significant nibble and call lsn
	return lsn(byte >> 4);
}

char rc4::lsn(char byte)
{
	//Get rid of the most significant nibble
	byte = byte&15;

	if(byte <= 9)
		return byte + '0';
	return byte + 'A' - 10;
}
