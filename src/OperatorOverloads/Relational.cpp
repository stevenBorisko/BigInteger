#include "../../BigInteger.hpp"

bool BigInteger::operator==(const BigInteger& rhs) const {
	if(this->size != rhs.size) {
		//std::cout << "==: unequal sizes\n";
		return false;
	}
	for(unsigned long long index = 0;index < this->size;++index) {
		if(this->digits[index] != rhs.digits[index]) {
			return false;
		}
	}
	return true;
}

bool BigInteger::operator!=(const BigInteger& rhs) const {
	if(this->size != rhs.size) {
		//std::cout << "!=: unequal sizes\n";
		return false;
	}
	return !(*this == rhs);
}

bool BigInteger::operator<=(const BigInteger& rhs) const {
	if(this->size != rhs.size) {
		//std::cout << "<=: unequal sizes\n";
		return false;
	}
	return !(*this > rhs);
}

bool BigInteger::operator<(const BigInteger& rhs) const {
	if(this->size != rhs.size) {
		//std::cout << "<: unequal sizes\n";
		return false;
	}

	// obvious different sign case
	if(this->N() != rhs.N())
		return (this->N() & !(rhs.N()));

	unsigned long long index = this->size;
	while(index--)
		if(this->digits[index] - rhs.digits[index])
			return (this->digits[index] < rhs.digits[index]);
	return false;
}

bool BigInteger::operator>=(const BigInteger& rhs) const {
	if(this->size != rhs.size) {
		//std::cout << ">=: unequal sizes\n";
		return false;
	}
	return !(*this < rhs);
}

bool BigInteger::operator>(const BigInteger& rhs) const {
	if(this->size != rhs.size) {
		//std::cout << ">: unequal sizes\n";
		return false;
	}

	// obvious different sign case
	if(this->N() != rhs.N())
		return (!(this->N()) & rhs.N());

	unsigned long long index = this->size;
	while(index--)
		if(this->digits[index] - rhs.digits[index])
			return (this->digits[index] > rhs.digits[index]);
	return false;
}
