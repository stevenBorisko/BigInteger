#include <fstream>

#include "../../BigInteger.hpp"

void BigInteger::hexPrint(std::ostream& os) const {
	uint64_t mask = 0xF;
	uint64_t index = this->size;
	uint64_t temp = 0;
	//while(--index && digits[index] == 0) { }
	//++index;
	while(index--) {
		mask = 0xF;
		mask <<= 60;
		for(unsigned char i = 64;i;i -= 4) {
			temp = this->digits[index] & mask;
			temp >>= i - 4;
			temp += 48;
			if(temp > 57) temp += 7;
			os << (char)(temp);
			mask >>= 4;
		}
		os << " ";
	}
}

void BigInteger::binPrint(std::ostream& os) const {
	uint64_t index = size;
	while(--index && digits[index] == 0) { }
	++index;
	while(index--) {
		os << binDigit(index);
		os << " ";
	}
}

std::string BigInteger::binDigit(const uint64_t digit) const {
	if(digit >= size)
		return "invalid index in binDigit(uint64_t)";
	std::string retString = "";
	uint64_t testDigit = 0b1;
	testDigit <<= 63;
	while(testDigit) {
		retString += ( (digits[digit] & testDigit) ? '1' : '0' );
		testDigit >>= 1;
	}
	return retString;
}

void BigInteger::binDump(const std::string filename) const {
	const char* name = filename.c_str();
	std::ofstream file;
	file.open(name);
	uint64_t charMask = 0;
	uint64_t index = this->size;
	uint64_t temp = 0;
	char printer = '\0';
	while(index--) {
		charMask = 0xFF;
		charMask <<= 56;
		
		for(unsigned char i = 64;i;i-=8) {
			temp = digits[index] & charMask;
			temp >>= i - 8;
			printer = (char)temp;
			charMask >>= 8;
			file << printer;
		}
	}
	file.close();
}

void BigInteger::decPrint(std::ostream& os) const {
	BigInteger thisCopy = BigInteger(*this);
	if(thisCopy.N()) thisCopy.neg();
	DynamicDecimal acc = DynamicDecimal(0);
	uint64_t mask = left;
	uint64_t index = thisCopy.size - 1;
	uint64_t currDigit = thisCopy.digits[index];

	// Most significant digit gets treated separately since the sign bit needs
	// to be left uncounted
	mask >>= 1;
	while(mask) {
		acc.multiplyByTwo();
		if(mask & currDigit) acc.addOne();
		mask >>= 1;
	}

	while(index--) {
		currDigit = thisCopy.digits[index];
		mask = left;
		while(mask) {
			acc.multiplyByTwo();
			if(mask & currDigit) acc.addOne();
			mask >>= 1;
		}
	}

	if(this->N()) os << "-";
	acc.print(os);
}
