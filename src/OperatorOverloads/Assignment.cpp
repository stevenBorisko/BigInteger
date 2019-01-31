#include "../../BigInteger.hpp"

BigInteger& BigInteger::operator=(const BigInteger& rhs) {
	if(this->size != rhs.size) {
		//std::cout << "=: unequal sizes\n";
		return *this;
	}
	uint64_t index = this->size;
	while(index--)
		this->digits[index] = rhs.digits[index];
	return *this;
}

BigInteger& BigInteger::operator=(const uint64_t& rhs) {
	this->zero();
	this->digits[0] = rhs;
	return *this;
}

uint64_t BigInteger::operator[](const uint64_t& index) const {
	return digits[index];
}

uint64_t& BigInteger::operator[](const uint64_t& index) {
	return digits[index];
}
