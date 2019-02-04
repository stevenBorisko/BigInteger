#include "../../BigInteger.hpp"

BigInteger BigInteger::operator!() const {
	BigInteger ret = BigInteger(this->size,!this->Z());
	return ret;
}
BigInteger BigInteger::operator-() const {
	BigInteger copy = BigInteger(*this);
	copy.neg();
	return copy;
}

// Prefix
BigInteger& BigInteger::operator++() {
	*this += 1;
	return *this;
}

BigInteger& BigInteger::operator--() {
	*this -= 1;
	return *this;
}

// Postfix
BigInteger BigInteger::operator++(int) {
	BigInteger ret = BigInteger(*this);
	++(*this);
	return ret;
}

BigInteger BigInteger::operator--(int) {
	BigInteger ret = BigInteger(*this);
	--(*this);
	return ret;
}
