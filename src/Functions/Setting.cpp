#include "../../BigInteger.hpp"

void BigInteger::zero() {
	uint64_t index = size;
	while(index) digits[--index] = 0;
}

void BigInteger::rand() {
	uint64_t index = size;
	uint64_t temp = 0;

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
	uint64_t index = size;
	while(index--) this->digits[index] = ~(this->digits[index]);
	++(*this);
}

void BigInteger::resize(uint64_t newSize) {
	if(newSize == size) return;
	uint64_t* newArray = new uint64_t[newSize];
	uint64_t index = 0;
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
