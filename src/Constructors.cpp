#include "../BigInteger.hpp"

BigInteger::BigInteger(unsigned long long newSize) :

	size(newSize),
	digits(new unsigned long long[newSize])

	{

	while(newSize)
		digits[--newSize] = 0;

}

BigInteger::BigInteger(

	unsigned long long initNum,
	unsigned long long newSize

	) :

	size(newSize),
	digits(new unsigned long long[newSize])

	{

	while(newSize)
		digits[--newSize] = 0;


	digits[0] = initNum;

}

BigInteger::BigInteger(const BigInteger& rhs) :

	size(rhs.size),
	digits(new unsigned long long[rhs.size])

	{

	unsigned long long index = this->size;
	while(index--)
		this->digits[index] = rhs.digits[index];

}

BigInteger::~BigInteger() {
	if(digits) delete[] digits;
}
