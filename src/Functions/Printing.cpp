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

void BigInteger::decPrint(std::ostream& os) const {
	BigInteger thisCopy = BigInteger(*this);
	if(thisCopy.N()) thisCopy.neg();
	DynamicDecimal acc = DynamicDecimal(0);
	uint64_t mask = left;
	uint64_t index = thisCopy.size;
	uint64_t currDigit = thisCopy.digits[index];

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

void binDump(const BigInteger& num, std::ostream& os) {
	void* voidArr = static_cast<void*>(num.digits);
	char* charArr = static_cast<char*>(voidArr);

	os << num.size << "\n";

	for(uint64_t index = 0; index < (num.size << 3); ++index)
		os << *(charArr++);
}

void binScoop(BigInteger& num, std::istream& is) {
	uint64_t dCount;
	std::string dCountStr;
	void* voidArr;
	char* charArr;

	// get digit count
	is >> dCountStr;
	uint64_t i = 0;
	for(
		i = 0;
		i < dCountStr.length() && (dCountStr[i] < '0' || '9' < dCountStr[i]);
		++i
	);
	dCount = static_cast<uint64_t>(
		stoi(dCountStr.substr(i, dCountStr.length() - i))
	);

	num = BigInteger(dCount);

	voidArr = static_cast<void*>(num.digits);
	charArr = static_cast<char*>(voidArr);

	// Skip the first character since it's just the space
	// between the digit count and the actual number
	is >> std::noskipws >> *(charArr);

	for(uint64_t index = 0; index < (num.size << 3); ++index)
		is >> std::noskipws >> *(charArr++);
}
