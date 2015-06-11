#ifndef __RC4__
#define __RC4__

class rc4_stream_cipher
{
	public:
	rc4_stream_cipher(char* key, int key_length);

	//Decrypt or encrypt using this function
	void transform(char* input, char* output, unsigned int length);

	private:
	char cipher_stream_next_byte();

	char byte_permutation[256];
};

//Functions for going from hex to binary and the reverse as well as handling strings
namespace rc4
{
	//Conversion back and forth from hex strings to binary 
	unsigned int bin_length(char* input);
	void hex_to_bin(char* input, char* output);
	void bin_to_hex(char* input, unsigned int length, char* output);

	//Single byte conversions
	char hex_to_byte(char msn, char lsn);
	char msn(char byte);
	char lsn(char byte);
}

#endif
