#include "../BigInteger.hpp"

BigInteger::BigInteger(uint64_t _size) :
	size(_size),
	digits(new uint64_t[_size])
{
	memset(this->digits, '\0', this->size << 3);
}

BigInteger::BigInteger(
	uint64_t _size,
	uint64_t val
) :
	BigInteger(_size)
{
	this->digits[0] = val;
}

BigInteger::BigInteger(const BigInteger& rhs) :
	size(rhs.size),
	digits(new uint64_t[this->size])
{
	memcpy(this->digits, rhs.digits, this->size << 3);
}

BigInteger::~BigInteger() {
	if(digits) delete[] digits;
}
