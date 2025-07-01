#include "biginteger.hpp"
#include <string>
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]){
    if (argc != 3) {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    std::fstream KEY;
    KEY.open(argv[1]);
    if(!KEY.is_open()){
        std::cerr << "Cannot open file " << argv[1] << std::endl;
        return -1;
    }

    std::string modulus; //n
    std::getline(KEY, modulus);
    modulus.erase(0, 9);

    std::string forIgnore;
    std::getline(KEY, forIgnore); 

    std::string privateExponent; //d
    std::getline(KEY, privateExponent);
    privateExponent.erase(0, 17);

    std::fstream EM;
    EM.open(argv[2]);
    if(!EM.is_open()){
        std::cerr << "Cannot open file " << argv[2] << std::endl;
        KEY.close();
        return - 1;
    }
    std::string encryptedMessage; //c
    std::getline(EM, encryptedMessage);

    BigInteger n = BigInteger(modulus, biginteger_base::hex);
    BigInteger d = BigInteger(privateExponent, biginteger_base::hex);
    BigInteger c = BigInteger(encryptedMessage, biginteger_base::hex);
    std::cout << to_hex(BigInteger::decoding(c, d, n));

    KEY.close();
    EM.close();
    return 0;
}
