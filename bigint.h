#ifndef CBH_BIGINT_H_INCLUDED
#define CBH_BIGINT_H_INCLUDED
#include <iostream>

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
