#include "../../BigInteger.hpp"

// ADDITION //

BigInteger& BigInteger::operator+=(const BigInteger& rhs) {
	if(this->size != rhs.size) {
		//std::cout << "+: unequal sizes\n";
		return *this;
	}

	if(this == &rhs) {
		*this = (*this + rhs);
		return *this;
	}

	uint64_t index = 0;
	uint64_t originalDigit = 0;
	unsigned char overflow = 0;
	do {
		originalDigit = this->digits[index];
		this->digits[index] += overflow;
		overflow = (this->digits[index] < originalDigit);

		originalDigit = this->digits[index];
		this->digits[index] += rhs.digits[index];
		overflow |= (this->digits[index] < originalDigit);
	}while(++index < this->size);

	return *this;
}

BigInteger& BigInteger::operator+=(const uint64_t& rhs) {
	uint64_t index = 0;
	uint64_t originalDigit = 0;
	uint64_t overflow = rhs;
	do {
		originalDigit = this->digits[index];
		this->digits[index] += overflow;
		overflow = (this->digits[index] < originalDigit);
	} while(overflow & (++index < this->size));

	return *this;
}

// SUBTRACTION //

BigInteger& BigInteger::operator-=(const BigInteger& rhs) {
	if(this->size != rhs.size) {
		//std::cout << "-: unequal sizes\n";
		return *this;
	}
	*this += -rhs;
	return *this;
}

BigInteger& BigInteger::operator-=(const uint64_t& rhs) {

	this->neg();
	*this += rhs;
	this->neg();

	return *this;
}

// MULTIPLICATION //

BigInteger& BigInteger::operator*=(const BigInteger& rhs) {
	if(this->size != rhs.size) {
		//std::cout << "*: unequal sizes\n";
		return *this;
	}

	if(this == &rhs) {
		*this = (*this * rhs);
		return *this;
	}

	if(this->Z()) return *this;
	if(rhs.Z()) {
		this->zero();
		return *this;
	}

	BigInteger rhsCopy(rhs);

	bool thisN = this->N();
	bool rhsN = rhs.N();
	bool negAns = (thisN ^ rhsN);
	if(thisN) this->neg();
	if(rhsN) rhsCopy.neg();

	BigInteger acc = BigInteger(this->size);

	for(uint64_t i = this->size;i;--i) {
		for(uint64_t j = 64;j;--j) {

			if(this->digits[0] & 1) acc += rhsCopy;
			*this >>= 1;
			this->digits[this->size - 1] |= ((acc.digits[0] & 1ULL) << 63);
			acc >>= 1;

		}
	}

	if(negAns) this->neg();

	return *this;
}

BigInteger& BigInteger::operator*=(const uint64_t& rhs) {

	uint64_t rhsCopy = rhs;

	bool thisN = this->N();
	bool rhsN = rhs & left;
	bool negAns = (thisN ^ rhsN);
	if(thisN) this->neg();
	if(rhsN) rhsCopy = ~rhs + 1;

	uint64_t acc = 0;
	for(uint64_t i = this->size;i;--i) {
		for(uint64_t j = 64;j;--j) {

			if(this->digits[0] & 1) acc += rhsCopy;
			*this >>= 1;
			this->digits[this->size - 1] |= ((acc & 1ULL) << 63);
			acc >>= 1;

		}
	}

	if(negAns) this->neg();

	return *this;
}

// DIVISION //

BigInteger& BigInteger::operator/=(const BigInteger& rhs) {
	if(this->size != rhs.size) {
		//std::cout << "/: unequal sizes\n";
		return *this;
	}

	if(this == &rhs) {
		*this = (*this / rhs);
		return *this;
	}

	// if either number is zero, return zero

	if(rhs.Z()) {
		//std::cout << "/: division by zero\n";
		this->zero();
		return *this;
	}

	if(this->Z()) return *this;

	BigInteger acc = BigInteger(this->size);
	BigInteger sor = BigInteger(rhs);

	bool thisNegative = this->N();
	bool rhsNegative = rhs.N();

	bool negAns = (thisNegative ^ rhsNegative);

	if(thisNegative) this->neg();
	if(rhsNegative) sor.neg();

	BigInteger negSor = BigInteger(sor);
	negSor.neg();

	bool negative = false;
	for(uint64_t i = this->size;i;--i) {
		for(uint64_t j = 64;j;--j) {

			negative = acc.N();
			acc <<= 1;
			acc.digits[0] |= (this->N() & 1);
			*this <<= 1;
			acc += (negative ? sor : negSor);
			this->digits[0] |= !acc.N();

		}
	}

	if(negAns) this->neg();

	return *this;
}

/*
BigInteger& BigInteger::operator/=(const uint64_t& rhs) {

	if(rhs == 0) {
		this->zero();
		return *this;
	}
	if(this->Z()) return *this;

	bool negAns = this->N();
	if(negAns) this->neg();

	uint64_t acc = 0;
	uint64_t negRHS = ~rhs;
	++negRHS;
	bool negative = false;
	for(uint64_t i = this->size;i;--i) {
		for(uint64_t j = 64;j;--j) {

			negative = (acc & left);
			acc <<= 1;
			acc |= (this->N() & 1);
			*this <<= 1;
			acc += (negative ? rhs : negRHS);
			this->digits[0] |= !(acc & left);

		}
	}

	if(negAns) this->neg();

	return *this;
}
*/

// MODULUS //

BigInteger& BigInteger::operator%=(const BigInteger& rhs) {
	if(this->size != rhs.size) {
		//std::cout << "%: unequal sizes\n";
		return *this;
	}

	if(this == &rhs) {
		*this = (*this % rhs);
		return *this;
	}

	// obvious cases

	if(this->Z()) return *this;

	BigInteger acc = BigInteger(this->size);
	BigInteger sor = BigInteger(rhs);

	bool thisNegative = this->N();
	bool rhsNegative = rhs.N();

	if(thisNegative) this->neg();
	if(rhsNegative) sor.neg();

	// Another trivial case
	if(*this <= sor) {
		if(*this == sor)
			this->zero();
		return *this;
	}

	BigInteger negSor = BigInteger(sor);
	negSor.neg();

	bool negative = false;
	for(uint64_t i = this->size;i;--i) {
		for(uint64_t j = 64;j;--j) {

			negative = acc.N();
			acc <<= 1;
			acc.digits[0] |= (this->N() & 1);
			*this <<= 1;
			acc += (negative ? sor : negSor);
			this->digits[0] |= !acc.N();

		}
	}

	if(acc.N()) acc += sor;
	if(thisNegative) acc.neg();

	*this = acc;

	return *this;
}

/*
BigInteger& BigInteger::operator%=(const uint64_t& rhs) {

	bool thisNegative = this->N();
	if(thisNegative) this->neg();
	if(this->Z()) return *this;

	uint64_t acc = 0;
	uint64_t negRHS = ~rhs;
	++negRHS;
	bool negative = false;
	for(uint64_t i = this->size;i;--i) {
		for(uint64_t j = 64;j;--j) {

			negative = (acc & left);
			acc <<= 1;
			acc |= (this->N() & 1);
			*this <<= 1;
			acc += (negative ? rhs : negRHS);
			this->digits[0] |= !(acc & left);

		}
	}

	if(acc & left) acc += rhs;

	this->zero();
	this->digits[0] = acc;

	return *this;
}
*/
