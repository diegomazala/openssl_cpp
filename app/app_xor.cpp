#include <iostream>

std::string encrypt_decrypt(std::string toEncrypt) 
{
	char key = 'K'; //Any char will work
	std::string output = toEncrypt;

	for (int i = 0; i < toEncrypt.size(); i++)
		output[i] = toEncrypt[i] ^ key;

	return output;
}


int main()
{
	std::string encrypted = encrypt_decrypt("hello world!");
	std::cout << "Encrypted:" << encrypted << "\n";

	std::string decrypted = encrypt_decrypt(encrypted);
	std::cout << "Decrypted:" << decrypted << "\n";

    return EXIT_SUCCESS;
}