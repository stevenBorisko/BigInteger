#include "../../BigInteger.hpp"

// ADDITION //

BigInteger BigInteger::operator+(const BigInteger& rhs) const {
	BigInteger ret = BigInteger(*this); 
	ret += rhs;
	return ret;
}

BigInteger BigInteger::operator+(const unsigned long long& rhs) const {
	BigInteger ret = BigInteger(*this);
	ret += rhs;
	return ret;
}

// SUBTRACTION //

BigInteger BigInteger::operator-(const BigInteger& rhs) const {
	BigInteger ret = BigInteger(*this); 
	ret -= rhs;
	return ret;
}

BigInteger BigInteger::operator-(const unsigned long long& rhs) const {
	BigInteger ret = BigInteger(*this);
	ret -= rhs;
	return ret;
}

// MULTIPLICATION //

BigInteger BigInteger::operator*(const BigInteger& rhs) const {
	BigInteger ret = BigInteger(*this); 
	ret *= rhs;
	return ret;
}

BigInteger BigInteger::operator*(const unsigned long long& rhs) const {
	BigInteger ret = BigInteger(*this);
	ret *= rhs;
	return ret;
}

// DIVISION //

BigInteger BigInteger::operator/(const BigInteger& rhs) const {
	BigInteger ret = BigInteger(*this); 
	ret /= rhs;
	return ret;
}

BigInteger BigInteger::operator/(const unsigned long long& rhs) const {
	BigInteger ret = BigInteger(*this);
	ret /= rhs;
	return ret;
}

// MODULUS //

BigInteger BigInteger::operator%(const BigInteger& rhs) const {
	BigInteger ret = BigInteger(*this); 
	ret %= rhs;
	return ret;
}

BigInteger BigInteger::operator%(const unsigned long long& rhs) const {
	BigInteger ret = BigInteger(*this);
	ret %= rhs;
	return ret;
}

