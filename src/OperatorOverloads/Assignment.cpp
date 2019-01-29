#include "../../BigInteger.hpp"

BigInteger& BigInteger::operator=(const BigInteger& rhs) {
	if(this->size != rhs.size) {
		//std::cout << "=: unequal sizes\n";
		return *this;
	}
	unsigned long long index = this->size;
	while(index--)
		this->digits[index] = rhs.digits[index];
	return *this;
}

BigInteger& BigInteger::operator=(const unsigned long long& rhs) {
	this->zero();
	this->digits[0] = rhs;
	return *this;
}

unsigned long long BigInteger::operator[](const unsigned long long& index) const {
	return digits[index];
}

unsigned long long& BigInteger::operator[](const unsigned long long& index) {
	return digits[index];
}
