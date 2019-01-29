#include "../../BigInteger.hpp"

void BigInteger::zero() {
	unsigned long long index = size;
	while(index) digits[--index] = 0;
}

void BigInteger::rand() {
	unsigned long long index = size;
	unsigned long long temp = 0;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1,0xFFFF);

	while(index--) {
		digits[index] = 0;
		for(unsigned char j = 0;j < 4;++j) {
			temp = dis(gen);
			temp <<= (j << 4);
			digits[index] |= temp;
		}
	}
}

void BigInteger::neg() {
	unsigned long long index = size;
	while(index--) this->digits[index] = ~(this->digits[index]);
	++(*this);
}

void BigInteger::resize(unsigned long long newSize) {
	if(newSize == size) return;
	unsigned long long* newArray = new unsigned long long[newSize];
	unsigned long long index = 0;
	while((index < newSize) & (index < size)) {
		newArray[index] = digits[index];
		++index;
	}
	--index;
	while(++index < newSize)
		newArray[index] = 0;
	delete[] digits;
	digits = newArray;
	size = newSize;
}
