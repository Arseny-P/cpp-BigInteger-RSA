#include "biginteger.hpp"
#include <string>
#include <cstdint>
#include <stdexcept>

BigInteger::BigInteger(): size_(1), negative(false) {
    digits = new uint32_t[1]{0};
}

BigInteger::BigInteger(int num): negative(false) {
    if(num < 0){
        negative = true;
        num = -num;
    }
    if(num == 0){
        size_ = 1;
        digits = new uint32_t[1]{0};
        return;
    }
    size_ = 0;
    unsigned long long tmp = static_cast<unsigned long long>(num);
    while(tmp > 0){
        tmp >>= 32;
        size_++;
    }
    digits = new uint32_t[size_]();
    tmp = num;
    for(unsigned long long i = 0; i < size_; ++i){
        digits[i] = static_cast<uint32_t>(tmp & 0xFFFFFFFF);
        tmp >>= 32;
    }
}
BigInteger::BigInteger(long int num): negative(false) {
    if(num < 0){
        negative = true;
        num = -num;
    }
    if(num == 0){
        size_ = 1;
        digits = new uint32_t[1]{0};
        return;
    }
    size_ = 0;
    unsigned long long tmp = static_cast<unsigned long long>(num);
    while(tmp > 0){
        tmp >>= 32;
        size_++;
    }
    digits = new uint32_t[size_]();
    tmp = num;
    for(unsigned long long i = 0; i < size_; ++i){
        digits[i] = static_cast<uint32_t>(tmp & 0xFFFFFFFF);
        tmp >>= 32;
    }
}
BigInteger::BigInteger(long long int num): negative(false) {
    if(num < 0){
        negative = true;
        num = -num;
    }
    if(num == 0){
        size_ = 1;
        digits = new uint32_t[1]{0};
        return;
    }
    size_ = 0;
    unsigned long long tmp = static_cast<unsigned long long>(num);
    while(tmp > 0){
        tmp >>= 32;
        size_++;
    }
    digits = new uint32_t[size_]();
    tmp = num;
    for(unsigned long long i = 0; i < size_; ++i){
        digits[i] = static_cast<uint32_t>(tmp & 0xFFFFFFFF);
        tmp >>= 32;
    }
}
BigInteger::BigInteger(unsigned int num): negative(false) {
    if(num == 0){
        size_ = 1;
        digits = new uint32_t[1]{0};
        return;
    }
    size_ = 0;
    unsigned long long tmp = static_cast<unsigned long long>(num);
    while(tmp > 0){
        tmp >>= 32;
        size_++;
    }
    digits = new uint32_t[size_]();
    tmp = num;
    for(unsigned long long i = 0; i < size_; ++i){
        digits[i] = static_cast<uint32_t>(tmp & 0xFFFFFFFF);
        tmp >>= 32;
    }
}
BigInteger::BigInteger(unsigned long int num): negative(false) {
    if(num == 0){
        size_ = 1;
        digits = new uint32_t[1]{0};
        return;
    }
    size_ = 0;
    unsigned long long tmp = static_cast<unsigned long long>(num);
    while(tmp > 0){
        tmp >>= 32;
        size_++;
    }
    digits = new uint32_t[size_]();
    tmp = num;
    for(unsigned long long i = 0; i < size_; ++i){
        digits[i] = static_cast<uint32_t>(tmp & 0xFFFFFFFF);
        tmp >>= 32;
    }
}
BigInteger::BigInteger(unsigned long long int num): negative(false) {
    if(num == 0){
        size_ = 1;
        digits = new uint32_t[1]{0};
        return;
    }
    size_ = 0;
    unsigned long long tmp = static_cast<unsigned long long>(num);
    while(tmp > 0){
        tmp >>= 32;
        size_++;
    }
    digits = new uint32_t[size_]();
    tmp = num;
    for(unsigned long long i = 0; i < size_; ++i){
        digits[i] = static_cast<uint32_t>(tmp & 0xFFFFFFFF);
        tmp >>= 32;
    }
}

BigInteger::BigInteger(std::string num, biginteger_base base): negative(false), size_(1) {
    if(num.empty()){
        throw std::invalid_argument("Empty string");
    }
    if(num[0] == '-'){  
        negative = true;
        num = num.substr(1);
    }
    if(num[0] == '+'){
        num = num.substr(1);
    }
    if(num.empty()){
        throw std::invalid_argument("Empty string");
    }
    const std::string hexValidSymb = "0123456789ABCDEFabcdef";
    const std::string decValidSymb = "0123456789";
    if(base == biginteger_base::hex){
        for(char c: num){
            if(hexValidSymb.find(c) == std::string::npos){
                throw std::invalid_argument("Incorrect hex str: an incorrect character was found");
            }
        }

        digits = new uint32_t[(num.size() + 7)/8]();
        size_ = (num.size() + 7)/8;
        for(long long int i = static_cast<long long int>(num.size()-1); i >= 0; --i){
            uint32_t value = 0;
            if(num[i] >= 'A'){
                if(num[i] >= 'a'){
                    value = num[i] - 'a' + 10;
                }else{
                    value = num[i] - 'A' + 10;
                }
            }else{
                value = num[i] - '0';
            }
            digits[(num.size() - i - 1)/8] |= ( value << (4 * ( (num.size() - i - 1) % 8 )) );   
        }         
    }else{
        for(char c: num){
            if(decValidSymb.find(c) == std::string::npos){
                throw std::invalid_argument("Incorrect dec str: an incorrect character was found");
            }
        }

        uint32_t* tmp = new uint32_t[num.size() / 9 + 2]();
        unsigned long long int tmp_size = 0;
        for(char c: num){
            uint32_t digit = c - '0';
            unsigned long long int carry = digit;
            for(unsigned long long int i = 0; i < tmp_size; ++i){
                unsigned long long int val = static_cast<unsigned long long int>(tmp[i]) * 10 + carry;
                tmp[i] = static_cast<uint32_t>(val & 0xFFFFFFFF);
                carry = val >> 32;
            }
            
            if(carry > 0){
                tmp[tmp_size++] = static_cast<uint32_t>(carry);
            }
        }
            
        if(tmp_size == 0){
            delete[] tmp;
            size_ = 1;
            digits = new uint32_t[1]{0};
        }else{
            size_ = tmp_size;
            digits = new uint32_t[size_]();
            std::copy(tmp, tmp + size_, digits);
            delete[] tmp;
        }
    }

    if(isZero()){
        negative = false;
    }
}

BigInteger::BigInteger(const BigInteger& other) : size_(other.size_), negative(other.negative) {
    digits = new uint32_t[size_]();
    std::copy(other.digits, other.digits + size_, digits);
}

BigInteger& BigInteger::operator=(const BigInteger& other){
    if(this != &other){
        delete[] digits;
        size_ = other.size_;
        negative = other.negative;
        digits = new uint32_t[size_]();
        std::copy(other.digits, other.digits + size_, digits);
    }
    return *this;
}

BigInteger::BigInteger(BigInteger&& other) noexcept: digits(other.digits), size_(other.size_), negative(other.negative) {
    other.digits = nullptr;
    other.size_ = 0;
}

BigInteger& BigInteger::operator=(BigInteger&& other) noexcept {
    if(this != &other){
        delete[] digits;
        digits = other.digits;
        size_ = other.size_;
        negative = other.negative;
        other.digits = nullptr;
        other.size_ = 0;
    }
    return *this;
}

unsigned long long BigInteger::size() const {
    return size_;
}

bool BigInteger::operator==(const BigInteger& other) const{
    if(this->isZero() && other.isZero()){
        return true;
    }
    if(this->negative != other.negative){
        return false;
    }
    if(this->size() != other.size()){
        return false;
    }
    for(unsigned long long i = 0; i < size_; ++i){
        if(digits[i] != other.digits[i]){
            return false;
        }
    }
    return true;
}
bool BigInteger::operator==(const int& other) const {
    return *this == BigInteger(other);
}
bool BigInteger::operator==(const long int& other) const {
    return *this == BigInteger(other);
}
bool BigInteger::operator==(const long long int& other) const {
    return *this == BigInteger(other);
}
bool BigInteger::operator==(const unsigned int& other) const {
    return *this == BigInteger(other);
}
bool BigInteger::operator==(const unsigned long int& other) const {
    return *this == BigInteger(other);
}
bool BigInteger::operator==(const unsigned long long int& other) const {
    return *this == BigInteger(other);
}

bool BigInteger::operator!=(const BigInteger& other) const {
    return !(*this == other);
}
bool BigInteger::operator!=(const int& other) const {
    return !(*this == BigInteger(other));
}
bool BigInteger::operator!=(const long int& other) const {
    return !(*this == BigInteger(other));
}
bool BigInteger::operator!=(const long long int& other) const {
    return !(*this == BigInteger(other));
}
bool BigInteger::operator!=(const unsigned int& other) const {
    return !(*this == BigInteger(other));
}
bool BigInteger::operator!=(const unsigned long int& other) const {
    return !(*this == BigInteger(other));
}
bool BigInteger::operator!=(const unsigned long long int& other) const {
    return !(*this == BigInteger(other));
}

bool BigInteger::operator<(const BigInteger& other) const {
    if(this->negative != other.negative){
        return this->negative;
    }
    if(!this->negative){
        if(size_ != other.size_){
            return size_ < other.size_;
        }
        for(long long i = static_cast<long long>(size_) - 1; i >= 0; --i){
            if(digits[i] != other.digits[i]){
                return digits[i] < other.digits[i];
            }
        }
    }else{
        if(size_ != other.size_){
            return size_ > other.size_;
        }
        for(long long i = static_cast<long long>(size_) - 1; i >= 0; --i){
            if(digits[i] != other.digits[i]){
                return digits[i] > other.digits[i];
            }
        }
    }
    return false;
}

bool BigInteger::operator>(const BigInteger& other) const{
    return other < *this;
}

bool BigInteger::operator<=(const BigInteger& other) const{
    return !(other < *this);
}

bool BigInteger::operator>=(const BigInteger& other) const {
    return !(*this < other);
}

BigInteger BigInteger::operator-(const BigInteger& other) const{
    if(negative == other.negative){
        if(negative){
            return (-other) - (-*this);
        }
        BigInteger res;
        if(other >= *this){
            res.negative = true;
            delete[] res.digits;
            res.digits = new uint32_t[std::max(size_, other.size())]();
            res.size_ = std::max(size_, other.size());

            int borrowing = 0;
            for(unsigned long long int i = 0; i < other.size_; ++i){
                long long int minuend = static_cast<long long int>(other.digits[i]);
                long long int subtrahend = (i < size_) ? static_cast<long long int>(digits[i]) : 0;
                long long int d = minuend - subtrahend - borrowing;
                if(d < 0){
                    d += (1ULL << 32);
                    borrowing = 1;
                }else{
                    borrowing = 0;
                }
                res.digits[i] = static_cast<uint32_t>(d);
            }
            return res;
        }
        delete[] res.digits;
        res.digits = new uint32_t[std::max(size_, other.size())]();
        res.size_ = std::max(size_, other.size());

        int borrowing = 0;
        for(unsigned long long int i = 0; i < size_; ++i){
            long long int minuend = static_cast<long long int>(digits[i]);
            long long int subtrahend = (i < other.size_) ? static_cast<long long int>(other.digits[i]) : 0;
            long long int d = minuend - subtrahend - borrowing;
            if(d < 0){
                d += (1ULL << 32);
                borrowing = 1;
            }else{
                borrowing = 0;
            }
            res.digits[i] = static_cast<uint32_t>(d);
        }

        unsigned long long int final_size = res.size_;
        while(final_size > 1 && res.digits[final_size - 1] == 0){
            --final_size;
        }
        if(final_size == 0){
            final_size = 1;
        }

        if(final_size < res.size_){
            uint32_t* final_digits = new uint32_t[final_size]();
            std::copy(res.digits, res.digits + final_size, final_digits);
            delete[] res.digits;
            res.digits = final_digits;
            res.size_ = final_size;
        }
        if(res.isZero()) {
            res.negative = false;
        }
        return res;
    }
    if(negative){
        return -((-*this) + other);
    }
    return *this + (-other);
    
}

bool BigInteger::isZero() const {
    for(unsigned long long i = 0; i < size_; ++i){
        if(digits[i] != 0){
            return false;
        }
    }
    return true;
}

BigInteger BigInteger::operator-() const {
    BigInteger res(*this);
    if(!res.isZero()){
        res.negative = !res.negative;
    }else{
        res.negative = false;
    }
    return res;
}
BigInteger BigInteger::operator+() const {
    return *this;
}

BigInteger BigInteger::operator+(const BigInteger& other) const {
    if(negative == other.negative){
        BigInteger tmp;
        tmp.negative = negative;
        unsigned long long int maxNum = std::max(size_, other.size());
        delete[] tmp.digits;
        tmp.digits = new uint32_t[maxNum + 1]();
        tmp.size_ = maxNum + 1;
        unsigned long long int carry = 0;
        
        for(unsigned long long int i = 0; i < maxNum || carry != 0; ++i){
            if(i >= tmp.size_){
            uint32_t* new_digits = new uint32_t[i + 1]();
            std::copy(tmp.digits, tmp.digits + tmp.size_, new_digits);
            delete[] tmp.digits;
            tmp.digits = new_digits;
            tmp.size_ = i + 1;
        }
            unsigned long long int s = carry;
            if(i < size_){
                s += digits[i];
            }
            if(i < other.size()){
                s += other.digits[i];
            }
            tmp.digits[i] = static_cast<uint32_t>(s & 0xFFFFFFFF);
            carry = s >> 32;
        }
        
        unsigned long long int final_size = tmp.size_;
        while(final_size > 1 && tmp.digits[final_size - 1] == 0){
            --final_size;
        }
        if(final_size == 0){
            final_size = 1;
        }

        if(final_size < tmp.size_){
            uint32_t* final_digits = new uint32_t[final_size]();
            std::copy(tmp.digits, tmp.digits + final_size, final_digits);
            delete[] tmp.digits;
            tmp.digits = final_digits;
            tmp.size_ = final_size;
        }
        
        if(tmp.isZero()){ 
            tmp.negative = false;
        }
        return tmp;
    }
    if(negative){
        return other - (-*this);
    }
    return *this - (-other);
}
BigInteger BigInteger::operator+(int other) const{
    return *this + BigInteger(other);
}
BigInteger BigInteger::operator+(const long int other) const{
    return *this + BigInteger(other);
}
BigInteger BigInteger::operator+(const long long int other) const{
    return *this + BigInteger(other);
}
BigInteger BigInteger::operator+(const unsigned int other) const{
    return *this + BigInteger(other);
}
BigInteger BigInteger::operator+(const unsigned long int other) const{
    return *this + BigInteger(other);
}
BigInteger BigInteger::operator+(const unsigned long long int other) const{
    return *this + BigInteger(other);
}

BigInteger& BigInteger::operator++(){
    *this = *this + BigInteger(1); 
    return *this;
}
BigInteger& BigInteger::operator--(){
    *this = *this - BigInteger(1); 
    return *this;
}
BigInteger BigInteger::operator++(int){
    BigInteger tmp = *this;
    *this = *this + BigInteger(1); 
    return tmp;
}
BigInteger BigInteger::operator--(int){
    BigInteger tmp = *this;
    *this = *this - BigInteger(1); 
    return tmp;
}

BigInteger BigInteger::operator*(const BigInteger& other) const {
    if(this->isZero() || other.isZero()){
        return BigInteger(0);
    }

    BigInteger res;
    res.negative = (negative != other.negative);
    unsigned long long int m = size_;
    unsigned long long int n = other.size_;
    unsigned long long SIZE = m + n;
    uint32_t* tmp = new uint32_t[SIZE](); 
    for(unsigned long long j = 0; j < n; ++j){
        unsigned long long int carry = 0;
        for(unsigned long long i = 0; i < m; ++i){
            unsigned long long int product = (unsigned long long int)digits[i] * other.digits[j] + tmp[i + j] + carry;
            tmp[i + j] = static_cast<uint32_t>(product & 0xFFFFFFFF);
            carry = product >> 32;
        }
        tmp[j + m] = static_cast<uint32_t>(carry);
    }
    while(SIZE > 1 && tmp[SIZE - 1] == 0){
        --SIZE;
    }

    delete[] res.digits;
    res.digits = new uint32_t[SIZE]();
    std::copy(tmp, tmp + SIZE, res.digits);
    res.size_ = SIZE;
    
    delete[] tmp;
    return res;
}

BigInteger BigInteger::operator/(const BigInteger& other) const {
    if(other.isZero()){
        throw std::invalid_argument("Division by zero");
    }
    BigInteger abs_this = (*this); abs_this.negative = false;
    BigInteger abs_other = other; abs_other.negative = false;
    if(abs_this < abs_other){
        if(this->isZero()){
            return BigInteger(0);
        }
        return BigInteger(0);
    }
    unsigned long long int b = 1ULL << 32;
    unsigned long long int d = b / (static_cast<unsigned long long int>(other.digits[other.size_ - 1]) + 1);
    
    BigInteger u = *this * static_cast<uint32_t>(d);
    BigInteger v = other * static_cast<uint32_t>(d);
    u.negative = false;
    v.negative = false;

    unsigned long long int m = u.size_ - v.size_;
    unsigned long long int n = v.size_;

    BigInteger q;
    delete[] q.digits;
    q.digits = new uint32_t[m + 1]();
    q.size_ = m + 1;
    q.negative = (negative != other.negative);

    uint32_t* new_udigits = new uint32_t[u.size_ + 1]();
    std::copy(u.digits, u.digits + u.size_, new_udigits);
    delete[] u.digits;
    u.digits = new_udigits;
    u.size_++;

    for(long long int j = static_cast<long long int>(m); j >= 0; --j){
        unsigned long long int dividend = static_cast<unsigned long long int>(u.digits[j + n]) * b + u.digits[j + n - 1];
        unsigned long long int Q = dividend / v.digits[n - 1];
        unsigned long long int R = dividend % v.digits[n - 1];

        while(Q >= b || (n > 1 && Q * v.digits[n - 2] > b * R + u.digits[j + n - 2])) {
            --Q;
            R += v.digits[n - 1];
            if(R >= b){
                break;
            }
        }

        unsigned long long int borrowing = 0;
        for(unsigned long long int i = 0; i < n; ++i){
            unsigned long long int product = Q * v.digits[i];
            unsigned long long int subtrahend = product + borrowing;
            borrowing = subtrahend >> 32;
            
            if(u.digits[j + i] < (subtrahend & 0xFFFFFFFF)){
                borrowing++;
            }
            u.digits[j + i] -= static_cast<uint32_t>(subtrahend & 0xFFFFFFFF);
        }

        if(u.digits[j + n] < borrowing){
            --Q;
            unsigned long long int carry = 0;
            for(unsigned long long int i = 0; i < n; ++i){
                unsigned long long int sum = static_cast<unsigned long long int>(u.digits[j + i]) + v.digits[i] + carry;
                u.digits[j + i] = static_cast<uint32_t>(sum & 0xFFFFFFFF);
                carry = sum >> 32;
            }
            u.digits[j + n] += static_cast<uint32_t>(carry);
        }

        q.digits[j] = static_cast<uint32_t>(Q);
    }

    unsigned long long int SIZE = q.size_;
    while(SIZE > 1 && q.digits[SIZE - 1] == 0){
        SIZE--;
    }

    BigInteger res;
    delete[] res.digits;
    res.digits = new uint32_t[SIZE];
    std::copy(q.digits, q.digits + SIZE, res.digits);
    res.size_ = SIZE;
    res.negative = q.negative;

    return res;
}
BigInteger BigInteger::operator%(const BigInteger& other) const{
    if(other.isZero()){
        throw std::invalid_argument("Division by zero");
    }
    if(this->isZero()){
        return BigInteger(0);
    }
    return *this - (*this / other) * other;
}

BigInteger& BigInteger::operator+=(const BigInteger& other) {
    *this = *this + other;
    return *this;
}
BigInteger& BigInteger::operator-=(const BigInteger& other) {
    *this = *this - other;
    return *this;
}
BigInteger& BigInteger::operator*=(const BigInteger& other) {
    *this = *this * other;
    return *this;
}
BigInteger& BigInteger::operator/=(const BigInteger& other) {
    *this = *this / other;
    return *this;
}
BigInteger& BigInteger::operator%=(const BigInteger& other) {
    *this = *this % other;
    return *this;
}

BigInteger& BigInteger::operator>>=(unsigned int shift){
    if(this->isZero()){
        return *this;
    }
    uint32_t carry = 0; 
    for(long long i = static_cast<long long>(size_) - 1; i >= 0; --i){
        uint32_t lastDigit = digits[i] & 1;
        digits[i] >>= 1;
        digits[i] |= (carry << 31);
        carry = lastDigit;
    }
    
    unsigned long long SIZE = size_;
    while(size_ > 1 && digits[size_ - 1] == 0){
        size_--;
    }
    if(size_ != SIZE) {
        uint32_t* new_digits = new uint32_t[size_];
        std::copy(digits, digits + size_, new_digits);
        delete[] digits;
        digits = new_digits;
    }
    if(this->isZero()) {
        negative = false;
    }

    return *this;
}

BigInteger BigInteger::decoding(BigInteger c, BigInteger d, BigInteger& n) {
    BigInteger result(1);
    c = c % n;
    while(!d.isZero()) {
        if(d.digits[0] % 2 == 1) {
            result = (result * c) % n;
        }
        d >>= 1;
        c = (c * c) % n;
    }
    return result;
}

std::string BigInteger::to_hex() const {
    std::string res;
    if(negative){
        res += "-";
    }
    const char hex[] = "0123456789ABCDEF";
    bool frontZero = true;

    for(long long int i = static_cast<long long int>(size_ - 1); i >= 0; --i){
        uint32_t num = digits[i];
        for(int j = 28; j >= 0; j -= 4){
            unsigned int digit = (num >> j) & 0xF;
            if(digit != 0 || !frontZero){
                res += hex[digit];
                frontZero = false;
            }
        }
    }

    return res.empty() ? "0" : res;
}

std::string BigInteger::to_string() const {
    if(isZero()){
        return "0";
    }
    BigInteger tmp(*this);
    tmp.negative = false;        
    std::string res;
    while(!tmp.isZero()){
        unsigned long long int remainder = 0;
        for(long long int i = static_cast<long long int>(tmp.size_ - 1); i >= 0; --i){
            unsigned long long int value = (remainder << 32) | tmp.digits[i];
            tmp.digits[i] = static_cast<uint32_t>(value / 10);
            remainder = value % 10;
        }
        res.insert(res.begin(), static_cast<char>(remainder + '0'));
    }
    
    if(negative){
        res = '-' + res;
    }
    return res;
}

std::string to_string(const BigInteger& num){
        return num.to_string();
}
std::string to_hex(const BigInteger& num){
    return num.to_hex();
}
