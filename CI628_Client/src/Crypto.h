
/* 
* RSA Algorithm for enxryption implementation
*/
#include <iostream>
#include <vector>
#include <set>
#include <string>

class Crypto {

private:

    std::set<int> prime; // a set will be the collection of prime numbers,
               // where we can select random primes p and q
    int public_key;
    int private_key;
    int n;
    bool key_received = false;
public:

    int gcd(int u, int v);
    void primefiller();
    int pickrandomprime();
    void setkeys();
    int getPublicKey() { return public_key; }
    void setPublicKey(int pKey) { public_key = pKey; }
    int getPrivateKey() { return private_key; }
    void setPrivateKey(int pKey) { private_key = pKey; }
    bool getKeyRecieved() { return key_received; }
    void setKeyRecieved(bool recieved) { key_received = recieved; }
    long long int encrypt(double message);
    long long int decrypt(int encrypted_text);
    void setN(int sentN) { n = sentN; }
    std::vector<int> encoder(std::string message);
    std::string decoder(std::vector<int> encoded);

};