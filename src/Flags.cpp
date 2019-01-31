#include "../BigInteger.hpp"

bool BigInteger::Z() const {
	uint64_t index = size;
	while(index) if(digits[--index]) return false;
	return true;
}

bool BigInteger::N() const {
	return (left & digits[size - 1]);
}

bool BigInteger::O() const {
	return (1 & digits[0]);
}
