#include "../../BigInteger.hpp"

// NOT

BigInteger BigInteger::operator~() const {
	BigInteger ret = BigInteger(*this);
	ret.flip();
	return ret;
}

// AND

BigInteger BigInteger::operator&(const BigInteger& rhs) const {
	BigInteger ret = BigInteger(*this);
	ret &= rhs;
	return ret;
}

BigInteger BigInteger::operator&(const uint64_t& rhs) const {
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

BigInteger BigInteger::operator^(const uint64_t& rhs) const {
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

BigInteger BigInteger::operator|(const uint64_t& rhs) const {
	BigInteger ret = BigInteger(*this);
	ret |= rhs;
	return ret;
}

// SHIFTS

BigInteger BigInteger::operator<<(const uint64_t& shift) const {
	BigInteger ret = BigInteger(*this);
	ret <<= shift;
	return ret;
}

BigInteger BigInteger::operator>>(const uint64_t& shift) const {
	BigInteger ret = BigInteger(*this);
	ret >>= shift;
	return ret;
}
