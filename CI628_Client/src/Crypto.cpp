#include <iostream>
#include <vector>
#include <set>
#include <string>
#include "Crypto.h"
#include <numeric>


int Crypto::gcd(int u, int v)
{
    while (v != 0)
    {
        int r = u % v;
        u = v;
        v = r;
    }
    return u;
}
// we will run the function only once to fill the set of
// prime numbers
void Crypto::primefiller()
{
    // method used to fill the primes set is seive of
    // eratosthenes(a method to collect prime numbers)
    std::vector<bool> seive(250, true);
    seive[0] = false;
    seive[1] = false;
    for (int i = 2; i < 250; i++) {
        for (int j = i * 2; j < 250; j += i) {
            seive[j] = false;
        }
    } // filling the prime numbers
    for (int i = 0; i < seive.size(); i++) {
        if (seive[i])
            prime.insert(i);
    }
}
// picking a random prime number and erasing that prime
// number from list because p!=q
int Crypto::pickrandomprime()
{
    int k = rand() % prime.size();
    auto it = prime.begin();
    while (k--)
        it++;
    int ret = *it;
    prime.erase(it);
    return ret;
}
void Crypto::setkeys()
{
    int prime1 = pickrandomprime(); // first prime number
    int prime2 = pickrandomprime(); // second prime number
    // to check the prime numbers selected
    // cout<<prime1<<" "<<prime2<<endl;
    n = prime1 * prime2;
    ////int fi = (prime1 - 1) * (prime2 - 1);
    ////int e = 2;
    ////while (1) {
    ////    if (gcd(e, fi) == 1)
    ////        
    ////        break;
    ////    e++;
    ////} // d = (k*Φ(n) + 1) / e for some integer k
    ////public_key = e;
    ////int d = 2;
    ////while (1) {
    ////    if ((d * e) % fi == 1)
    ////        break;
    ////    d++;
    ////}
    ////private_key = d;
}
// to encrypt the given number
long long int Crypto::encrypt(double message)
{
    int e = public_key;
    long long int encrpyted_text = 1;
    while (e--) {
        encrpyted_text *= message;
        encrpyted_text %= n;
    }
    return encrpyted_text;
}
// to decrypt the given number
long long int Crypto::decrypt(int encrpyted_text)
{
    int d = private_key;
    long long int decrypted = 1;
    while (d--) {
        decrypted *= encrpyted_text;
        decrypted %= n;
    }
    return decrypted;
}
// first converting each character to its ASCII value and
// then encoding it then decoding the number to get the
// ASCII and converting it to character
std::vector<int> Crypto::encoder(std::string message)
{
    std::vector<int> form;
    // calling the encrypting function in encoding function
    for (auto& letter : message)
        form.push_back(encrypt((int)letter));
    return form;
}
std::string Crypto::decoder(std::vector<int> encoded)
{
    std::string s;
    // calling the decrypting function decoding function
    for (auto& num : encoded)
        s += decrypt(num);
    return s;
}