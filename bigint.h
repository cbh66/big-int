/*  BigInt.h  -  a class for arbitrary-length integers in C++
 *  Written by: Colin Hamilton, Tufts University
 *
 *  This class defines operations on a class whose precision, in theory, is
 *  limited only by the amount of memory avaiable.
 *  In practice, they are limited to 2^(2^32) bits of precision (10^9 digits)
 */

#ifndef CBH_BIGINT_H_INCLUDED
#define CBH_BIGINT_H_INCLUDED
#include <iostream>
/*  HalfInt is the type of each digit as it is stored.
 *  FullInt is the type of the "scratchpad" variables, used for intermediate
 *    calculations.  For multiplication to work,
 *      2^size(FullInt) >= (2^size(HalfInt) - 1) * 2^size(HalfInt)
 *    must be true.  This is true when FullInt has twice as many bits
 *    as HalfInt.
 */
typedef unsigned HalfInt;
typedef unsigned long FullInt;

class BigInt
{
public:
    BigInt(int value = 0);
    BigInt(std::string value, unsigned base = 0);
    BigInt(BigInt const &rhs);
    ~BigInt();

    unsigned long num_digits() {return digits;};

    /*  Assignment operators do assignment.
     *  Arithmetic and bitwise assignment operations are defined.
     *  In fact, the normal arithmetic opertions are defined below,
     *  in terms of these assignment operations.
     */
    BigInt &operator=(BigInt const &rhs);
    BigInt &operator+=(BigInt const &rhs);
    BigInt &operator-=(BigInt const &rhs);
    BigInt &operator*=(BigInt const &rhs);
    BigInt &operator/=(BigInt const &rhs);
    BigInt &operator%=(BigInt const &rhs);
    BigInt &operator>>=(long rhs);
    BigInt &operator<<=(long rhs);
    BigInt &operator&=(BigInt const &rhs);
    BigInt &operator|=(BigInt const &rhs);
    BigInt &operator^=(BigInt const &rhs);
    BigInt operator-() const;
    /*  Comparison operators.  All others are defined in terms of these.
     */
    bool operator==(BigInt rhs) const;
    bool operator<(BigInt rhs) const;

    operator std::string() const;
private:
    unsigned digits;
    HalfInt *number;
    bool is_negative;
    void ensure_size(unsigned size);
};


static inline BigInt &operator+(BigInt &operand)
{
    return operand;
}

static inline BigInt &operator+(BigInt lhs, BigInt const &rhs)
{
    return lhs += rhs;
}

static inline BigInt &operator-(BigInt lhs, BigInt const &rhs)
{
    return lhs -= rhs;
}

static inline BigInt &operator*(BigInt lhs, BigInt const &rhs)
{
    return lhs *= rhs;
}

static inline BigInt &operator/(BigInt lhs, BigInt const &rhs)
{
    return lhs /= rhs;
}

static inline BigInt &operator%(BigInt lhs, BigInt const &rhs)
{
    return lhs %= rhs;
}

static inline BigInt &operator++(BigInt &lhs)
{
    return lhs += 1;
}

static inline BigInt operator++(BigInt lhs, int)
{
    BigInt temp = lhs;
    lhs += 1;
    return temp;
}

static inline BigInt &operator--(BigInt &lhs)
{
    return lhs -= 1;
}

static inline BigInt operator--(BigInt lhs, int)
{
    BigInt temp = lhs;
    lhs -= 1;
    return temp;
}

static inline BigInt &operator&(BigInt lhs, BigInt const &rhs)
{
    return lhs &= rhs;
}

static inline BigInt &operator|(BigInt lhs, BigInt const &rhs)
{
    return lhs |= rhs;
}

static inline BigInt &operator^(BigInt lhs, BigInt const &rhs)
{
    return lhs ^= rhs;
}

static inline BigInt &operator>>(BigInt lhs, long rhs)
{
    return lhs >>= rhs;
}

static inline BigInt &operator<<(BigInt lhs, long rhs)
{
    return lhs <<= rhs;
}

static inline std::ostream& operator<<(std::ostream &os, BigInt const &obj)
{
  os << (std::string)obj;
  return os;
}

std::istream& operator>>(std::istream &is, BigInt &obj);


static inline bool operator> (BigInt const &lhs, BigInt const &rhs)
{
    return rhs < lhs;
}

static inline bool operator<=(BigInt const &lhs, BigInt const &rhs)
{
    return !(lhs > rhs);
}

static inline bool operator>=(BigInt const &lhs, BigInt const &rhs)
{
    return !(lhs < rhs);
}

static inline bool operator!=(BigInt const &lhs, BigInt const &rhs)
{
    return !(lhs == rhs);
}

#endif
