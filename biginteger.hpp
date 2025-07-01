#ifndef BIG_INTEGER_HPP
#define BIG_INTEGER_HPP
#include <string>
#include <cstdint>

enum class biginteger_base { dec=10, hex=16 };

class BigInteger{
    uint32_t* digits;
    unsigned long long int size_;
    bool negative;
public:
    BigInteger();

    BigInteger(int num);
    BigInteger(long int num);
    BigInteger(long long int num);
    BigInteger(unsigned int num);
    BigInteger(unsigned long int num);
    BigInteger(unsigned long long int num);

    BigInteger(std::string num, biginteger_base base = biginteger_base::dec);

    BigInteger(const BigInteger& other);

    BigInteger& operator=(const BigInteger& other);

    BigInteger(BigInteger&& other) noexcept;

    BigInteger& operator=(BigInteger&& other) noexcept;

    unsigned long long size() const;

    bool operator==(const BigInteger& other) const;
    bool operator==(const int& other) const;
    bool operator==(const long int& other) const;
    bool operator==(const long long int& other) const;
    bool operator==(const unsigned int& other) const;
    bool operator==(const unsigned long int& other) const;
    bool operator==(const unsigned long long int& other) const;
    friend bool operator==(int l, const BigInteger& r){
        return r == l;
}

    bool operator!=(const BigInteger& other) const;
    bool operator!=(const int& other) const ;
    bool operator!=(const long int& other) const;
    bool operator!=(const long long int& other) const;
    bool operator!=(const unsigned int& other) const;
    bool operator!=(const unsigned long int& other) const;
    bool operator!=(const unsigned long long int& other) const;
    friend bool operator!=(int l, const BigInteger& r){
        return r != l;
    }

    bool operator<(const BigInteger& other) const;

    bool operator>(const BigInteger& other) const;

    bool operator<=(const BigInteger& other) const;

    bool operator>=(const BigInteger& other) const;

    BigInteger operator-(const BigInteger& other) const;

    bool isZero() const;

    BigInteger operator-() const;
    BigInteger operator+() const;

    BigInteger operator+(const BigInteger& other) const;
    BigInteger operator+(int other) const;
    BigInteger operator+(const long int other) const;
    BigInteger operator+(const long long int other) const;
    BigInteger operator+(const unsigned int other) const;
    BigInteger operator+(const unsigned long int other) const;
    BigInteger operator+(const unsigned long long int other) const;
    friend BigInteger operator+(int l, const BigInteger& r){
        return r + l;
    }

    BigInteger& operator++();
    BigInteger& operator--();
    BigInteger operator++(int);
    BigInteger operator--(int);

    BigInteger operator*(const BigInteger& other) const;
    
    BigInteger operator/(const BigInteger& other) const;
    BigInteger operator%(const BigInteger& other) const;
    
    BigInteger& operator+=(const BigInteger& other);
    BigInteger& operator-=(const BigInteger& other);
    BigInteger& operator*=(const BigInteger& other);
    BigInteger& operator/=(const BigInteger& other);
    BigInteger& operator%=(const BigInteger& other);
    
    BigInteger& operator>>=(unsigned int shift);

    static BigInteger decoding(BigInteger c, BigInteger d, BigInteger& n);

    std::string to_hex() const;

    std::string to_string() const;
    
    ~BigInteger(){
        delete[] digits;
    }
};


std::string to_string(const BigInteger& num);
std::string to_hex(const BigInteger& num);


#endif
