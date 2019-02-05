#include "../BigInteger.hpp"

BigInteger::BigInteger(const uint64_t& _size) :
	size(_size),
	digits(new uint64_t[_size])
{
	memset(this->digits, '\0', this->size << 3);
}

BigInteger::BigInteger(const uint64_t& _size, const uint64_t& val):
	BigInteger(_size)
{
	this->digits[0] = val;
}

BigInteger::BigInteger(const uint64_t& _size, const std::string& num):
	BigInteger(_size)
{
	const bool negative = (num[0] == '-');
	for(uint64_t index = negative; index < num.length(); ++index)
		(*this *= 10) += static_cast<uint64_t>(num[index] - '0');
	if(negative) this->neg();
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
