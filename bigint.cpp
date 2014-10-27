#include <iostream>
#include "bigint.h"
using namespace std;

/*  The BigInt is internally represented as an array of longs, which one can
 *  think of as a series of digits in base 2^32 (or 2^64).
 *  Operations that never exceed 2^32 are the same as operations
 *  on long integers, and will likely have little extra overhead.
 *  The numbers are stored in little-endian order, so that position 0 contains
 *  the least significant digits, and position (digits - 1) contains the
 *  most significant digit.
 */


BigInt::BigInt(unsigned long value)
{
    digits = 1;
    number = new long[digits];
    number[0] = value;
}


BigInt::BigInt(string value, unsigned base)
{
(void) value;
}


BigInt::BigInt(BigInt const &rhs)
{
(void) rhs;
}


BigInt::~BigInt()
{
    delete number;
}


BigInt &BigInt::operator=(BigInt const &rhs)
{
(void) rhs;
return *this;
}


BigInt &BigInt::operator+=(BigInt const &rhs)
{
(void) rhs;
return *this;
}


BigInt &BigInt::operator-=(BigInt const &rhs)
{
(void) rhs;
return *this;
}


BigInt &BigInt::operator*=(BigInt const &rhs)
{
(void) rhs;
return *this;
}


BigInt &BigInt::operator/=(BigInt const &rhs)
{
(void) rhs;
return *this;
}


BigInt &BigInt::operator%=(BigInt const &rhs)
{
(void) rhs;
return *this;
}


BigInt &BigInt::operator>>=(long rhs)
{
(void) rhs;
return *this;
}


BigInt &BigInt::operator<<=(long rhs)
{
(void) rhs;
return *this;
}


BigInt &BigInt::operator&=(BigInt const &rhs)
{
(void) rhs;
return *this;
}


BigInt &BigInt::operator|=(BigInt const &rhs)
{
(void) rhs;
return *this;
}


BigInt &BigInt::operator^=(BigInt const &rhs)
{
(void) rhs;
return *this;
}


BigInt BigInt::operator-() const
{
return *this;
}


bool BigInt::operator==(BigInt rhs) const
{
(void) rhs;
return false;
}


bool BigInt::operator<(BigInt rhs) const
{
(void) rhs;
return false;
}


BigInt::operator long() const
{
return 0;
}


BigInt::operator string() const
{
    if (number[0] == 0) return "0";
    string result = "";
    return result;
}


istream& operator>>(istream &is, BigInt &obj)
{
    std::string string_val;
    char c = '\0';
    c = is.peek();
    if (is.good() && (c == '+' || c == '-' || isdigit(c))) {
        string_val += c;
    }
    is.get();
    c = is.peek();
    if (!isdigit(c) || !is.good()) {
        is.setstate(std::ios::failbit);
        return is;
    }
    while (is.good() && isdigit(c)) {
        string_val += c;
        is.get();
        c = is.peek();
    }
    obj = BigInt(string_val);
    return is;
}
