#include "../BigInteger.hpp"

BigInteger::BigInteger(uint64_t newSize) :
	size(newSize),
	digits(new uint64_t[newSize])
{
	memset(this->digits, '\0', this->size << 3);
}

BigInteger::BigInteger(
	uint64_t initNum,
	uint64_t newSize
) :
	BigInteger(newSize)
{
	this->digits[0] = initNum;
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
