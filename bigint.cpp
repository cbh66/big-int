#include <iostream>
#include "bigint.h"
using namespace std;

/*  The BigInt is internally represented as an array of longs, which one can
 *  think of as a series of digits in base 2^32.
 *  Operations that never exceed 2^32 are the same as operations
 *  on long integers, and will likely have little extra overhead.
 *  The numbers are stored in little-endian order, so that position 0 contains
 *  the least significant digit, and position (digits - 1) contains the
 *  most significant digit.
 *  The sign bit is not represented within the array; instead it is separate.
 *  Though this makes addition and subtraction a bit messier, it is easier
 *  in many other respects.  The twos-complement addition trick only works
 *  because of overflow, which cannot happen in a BigInt.
 */


BigInt::BigInt(int value)
{
    if (sizeof(HalfInt) >= sizeof(FullInt)) {
        throw string("Size of HalfInt is too large");
    }
    digits = 1;
    number = new HalfInt[digits];
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
    delete[] number;
}


BigInt &BigInt::operator=(BigInt const &rhs)
{
(void) rhs;
return *this;
}


BigInt &BigInt::operator+=(BigInt const &rhs)
{
    unsigned int count;
    HalfInt carry = 0;
    ensure_size(rhs.digits + 1);
    for (count = 0; count < digits && count < rhs.digits; ++count) {
        HalfInt left =  (count < digits) ? number[count] : 0;
        HalfInt right = (count < rhs.digits) ? rhs.number[count] : 0;
        HalfInt sum = left + right;
        number[count] = sum + carry;
        if (number[count] < left && number[count] < right) {
            FullInt full_result = (FullInt) left + (FullInt) right
                                + (FullInt) carry;
            carry = full_result >> ((sizeof(FullInt) - sizeof(HalfInt)) * 8);
            cout << carry << endl;
        } else {
            carry = 0;
        }
    }
    if (carry) {
        ensure_size(count + 1);
        number[count] += carry;
    }
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


BigInt::operator int() const
{
    return number[0];
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


void BigInt::ensure_size(unsigned size)
{
    if (size <= digits) return;
    HalfInt *temp = new HalfInt[size];
    memset(temp, 0, sizeof(*temp) * 8 * size);
    for (unsigned i = 0; i < digits; ++i) {
        temp[i] = number[i];
    }
    digits = size;
    delete number;
    number = temp;
}
