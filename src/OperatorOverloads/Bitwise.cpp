#include "../../BigInteger.hpp"

// NOT

BigInteger BigInteger::operator~() const {
	BigInteger ret = BigInteger(*this);
	unsigned long long index = this->size;
	while(index--)
		ret.digits[index] = ~(this->digits[index]);
	return ret;
}

// AND

BigInteger BigInteger::operator&(const BigInteger& rhs) const {
	BigInteger ret = BigInteger(*this);
	ret &= rhs;
	return ret;
}

BigInteger BigInteger::operator&(const unsigned long long& rhs) const {
	BigInteger ret = BigInteger(*this);
	ret &= rhs;
	return ret;
}

// XOR

BigInteger BigInteger::operator^(const BigInteger& rhs) const {
	BigInteger ret = BigInteger(*this);
	ret ^= rhs;
	return ret;
}

BigInteger BigInteger::operator^(const unsigned long long& rhs) const {
	BigInteger ret = BigInteger(*this);
	ret ^= rhs;
	return ret;
}

// OR

BigInteger BigInteger::operator|(const BigInteger& rhs) const {
	BigInteger ret = BigInteger(*this);
	ret |= rhs;
	return ret;
}

BigInteger BigInteger::operator|(const unsigned long long& rhs) const {
	BigInteger ret = BigInteger(*this);
	ret |= rhs;
	return ret;
}

// SHIFTS

BigInteger BigInteger::operator<<(const unsigned long long& shift) const {
	BigInteger ret = BigInteger(*this);
	ret <<= shift;
	return ret;
}

BigInteger BigInteger::operator>>(const unsigned long long& shift) const {
	BigInteger ret = BigInteger(*this);
	ret >>= shift;
	return ret;
}
