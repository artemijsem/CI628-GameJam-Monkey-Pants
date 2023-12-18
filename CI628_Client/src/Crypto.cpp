#include <iostream>
#include <vector>
#include <set>
#include <string>
#include "Crypto.h"
#include <numeric>


std::string Crypto::encrypt(std::string data_string)
{
	
	char encoded_data[1024];
	strcpy(encoded_data, data_string.c_str());

	for (int i = 0; i < data_string.size(); i++)
	{
		encoded_data[i] = (char)((i % 2 == 0) ? encoded_data[i] + secret_key : encoded_data - secret_key);
	}
	
	
}

std::string Crypto::decrpyt(std::string data_string)
{

}

void Crypto::setSecretKey(int key)
{
	secret_key = key;
	keyIsSet = true;

	std::cout << std::endl << std::endl << "SECRET KEY: " << secret_key << std::endl << std::endl;
}
