
/* 
* RSA Algorithm for enxryption implementation
*/
#include <iostream>
#include <vector>
#include <set>
#include <string>

class Crypto {

private:

    int secret_key;
    bool keyIsSet = false;
public:

    std::string encrypt(std::string data_string);
    std::string decrpyt(std::string data_string);
    void setSecretKey(int key);
    bool isKeySet() { return keyIsSet; }

};