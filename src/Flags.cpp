#include "../BigInteger.hpp"

bool BigInteger::Z() const {
	uint64_t index = this->size;
	while(index) if(this->digits[--index]) return false;
	return true;
}

bool BigInteger::N() const {
	return (left & this->digits[size - 1]);
}

bool BigInteger::O() const {
	return (1 & this->digits[0]);
}
