#include "rc4.h"

#include <iostream>
#include <stdio.h>
#include <string>

int main()
{
	//Initialize arrays for all the inputs/outputs
	char input_str[200], key_str[33];

	//Get the key and input
	std::cout << "RC4 Stream Cipher.  Please make all inputs in hexadecimal.\nKey: ";
	fgets(key_str, 33, stdin);
	std::cout << "Input: ";
	fgets(input_str, 200, stdin);

	//Get the length of the key and input
	unsigned int input_length, key_length;
	key_length   = rc4::bin_length(key_str);
	input_length = rc4::bin_length(input_str);

	//Assign space for the binary key and input
	char input_bin[input_length], key_bin[key_length];

	//Convert the key and input into binary
	rc4::hex_to_bin(key_str, key_bin);
	rc4::hex_to_bin(input_str, input_bin);

	//Create our cipher
	rc4_stream_cipher cipher(key_bin, key_length);

	//Initialize our output
	char output_bin[input_length];

	//Transform our input
	cipher.transform(input_bin, output_bin, input_length);

	//Initialize our output string buffer
	char output_str[2*input_length+1];

	//Convert from binary to a hex string
	rc4::bin_to_hex(output_bin, input_length, output_str);

	//Output it
	std::cout << output_str << std::endl;

	return 0;
}
