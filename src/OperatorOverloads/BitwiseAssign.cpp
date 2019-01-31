#include "../../BigInteger.hpp"

// AND

BigInteger& BigInteger::operator&=(const BigInteger& rhs) {
	if(this->size != rhs.size) {
		//std::cout << "&=: unequal sizes\n";
		return *this;
	}
	uint64_t index = this->size;
	while(index--)
		this->digits[index] &= rhs.digits[index];
	return *this;
}

BigInteger& BigInteger::operator&=(const uint64_t& rhs) {
	uint64_t index = this->size;
	while(--index) this->digits[index] = 0;
	this->digits[0] &= rhs;
	return *this;
}

// XOR

BigInteger& BigInteger::operator^=(const BigInteger& rhs) {
	if(this->size != rhs.size) {
		//std::cout << "^=: unequal sizes\n";
		return *this;
	}
	uint64_t index = this->size;
	while(index--)
		this->digits[index] ^= rhs.digits[index];
	return *this;
}

BigInteger& BigInteger::operator^=(const uint64_t& rhs) {
	this->digits[0] ^= rhs;
	return *this;
}

// OR

BigInteger& BigInteger::operator|=(const BigInteger& rhs) {
	if(this->size != rhs.size) {
		//std::cout << "|=: unequal sizes\n";
		return *this;
	}
	uint64_t index = this->size;
	while(index--)
		this->digits[index] |= rhs.digits[index];
	return *this;
}

BigInteger& BigInteger::operator|=(const uint64_t& rhs) {
	this->digits[0] |= rhs;
	return *this;
}

// SHIFTS

BigInteger& BigInteger::operator<<=(const uint64_t& shift) {
	uint64_t completeShifts = shift >> 6;

	// if shift > 64
	if(completeShifts) {
		if(completeShifts >= this->size) {
			this->zero();
			return *this;
		}
		else {
			uint64_t index = this->size;
			while(index-- - completeShifts) {
				this->digits[index] = this->digits[index - completeShifts];
			}
			++index;
			while(index--) {
				this->digits[index] = 0;
			}
		}
	}

	uint64_t insideShifts = 0b111111;
	insideShifts &= shift;

	uint64_t digitsToShift = 64 - insideShifts;
	uint64_t overflowMask = 0;
	if(insideShifts) {
		overflowMask = full;
		overflowMask >>= digitsToShift;
		overflowMask <<= digitsToShift;
	}
	else {
		return *this;
	}

	uint64_t index = 0;
	uint64_t overflow = 0;
	uint64_t pastOverflow = 0;

	while(index < this->size) {
		pastOverflow = overflowMask & this->digits[index];
		this->digits[index] <<= insideShifts;
		this->digits[index] += overflow;
		overflow = pastOverflow >> digitsToShift;
		++index;
	}

	return *this;
}

BigInteger& BigInteger::operator>>=(const uint64_t& shift) {
	uint64_t completeShifts = shift >> 6;

	// if shift > 64
	if(completeShifts) {
		if(completeShifts >= this->size) {
			this->zero();
			return *this;
		}
		else {
			uint64_t index = 0;
			while(index < this->size - completeShifts) {
				this->digits[index] = this->digits[index + completeShifts];
				++index;
			}
			index = this->size - completeShifts;
			while(index < this->size) {
				this->digits[index] = 0;
				++index;
			}
		}
	}

	uint64_t insideShifts = 0b111111;
	insideShifts &= shift;

	uint64_t digitsToShift = 64 - insideShifts;
	uint64_t overflowMask = 0;
	if(insideShifts) {
		overflowMask = full;
		overflowMask <<= digitsToShift;
		overflowMask >>= digitsToShift;
	}
	else {
		return *this;
	}

	uint64_t index = this->size;
	uint64_t overflow = 0;
	uint64_t pastOverflow = 0;

	while(index--) {
		pastOverflow = overflowMask & this->digits[index];
		this->digits[index] >>= insideShifts;
		this->digits[index] += overflow;
		overflow = pastOverflow << digitsToShift;
	}

	return *this;
}
