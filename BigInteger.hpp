#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <string>
#include <cstring>
#include <iostream>
#include <random>

#include <stdint.h>

#include "src/DynamicDecimal/DynamicDecimal.hpp"

/*
Author:
Steven Borisko

Description:
Class for arbitrarily large number arithmetic
*/

class BigInteger {

private:

	// constants used mainly for bit masking //

	// 32 bits of 1
	static constexpr uint64_t half = 0b11111111111111111111111111111111;
	// 64 bits of 1
	static constexpr uint64_t full = 0b1111111111111111111111111111111111111111111111111111111111111111;
	// 1 at 64th (index 63) (leftmost) bit
	static constexpr uint64_t left = 0b1000000000000000000000000000000000000000000000000000000000000000;

	// data

	// number of digits in the number
	uint64_t size;
	// array of digits in the number
	// endianness: little
	uint64_t* digits;

	// helper function

	// retrieves, in string form, digits at index 'digit'
	// found in src/Functions/Printing.cpp
	std::string binDigit(const uint64_t digit) const;

public:

	// Data Types //

	struct div_t;

	// Constructors //

	// creates a number of '_size' digits set to zero
	BigInteger(const uint64_t& _size);
	// creates a number of '_size' digits set to 'val'
	BigInteger(const uint64_t& _size, const uint64_t& val);
	// creates a number from a string.
	// For negative numbers, just start with a hyphen
	BigInteger(const uint64_t& _size, const std::string& num);
	// deep copy of rhs
	BigInteger(const BigInteger& rhs);
	~BigInteger();

	// Print Functions //

	// prints the entire number in hexadecimal
	void hexPrint(std::ostream& os) const;
	// prints, starting at the first non-zero digit, the number in binary
	void binPrint(std::ostream& os) const;
	// prints entire number in decimal
	void decPrint(std::ostream& os) const;
	// prints binary form of a number to an ostream
	// to be read by `binScoop`
	friend void binDump(const BigInteger& num, std::ostream& os);
	// reads binary form of a number to an ostream into num
	// written by `binDump`
	// num will be resized to whatever length it reads
	friend void binScoop(BigInteger& num, std::istream& is);

	// Math Functions //

	// Absolute Value
	friend BigInteger abs(const BigInteger& num);
	// Square Root
	friend BigInteger sqrt(const BigInteger& num);
	// Power: num ^ exp
	friend BigInteger pow(const BigInteger& num, const BigInteger& exp);
	friend BigInteger pow(const BigInteger& num, const uint64_t& exp);
	// Factorialize
	friend BigInteger fact(const BigInteger& num);
	// checks if num1 is divisible by num2
	//	returns [(num1 % num2) == 0]
	friend bool divisible(const BigInteger& num1, const BigInteger& num2);
	// Greatest Common Denominator
	friend BigInteger gcd(const BigInteger& num1, const BigInteger& num2);
	// Log base 2
	friend BigInteger log(const BigInteger& num);
	// Divides num1 by num2. Returns both the quotient and remainder such that
	//     num1 == quot * num2 + rem
	friend div_t div(const BigInteger& num1, const BigInteger& num2);

	// SetFunctions //

	// Set to zero
	void zero();
	// Set to a random number
	void rand();
	// negate the number
	void neg();
	// flip all the bits
	void flip();
	// Resizes the number to 'newSize' digits
	// if digits < size
		// the most significant digits will be cut off
		// the least significant digits will remain in the resized number
	// if digits > size
		// the whole number will remain in the resized number
		// the new, most significant digits will be willed in with zeroes
	void resize(uint64_t newSize);

	/*** Operator Overloads ***/

	// Assignment: deep copy //
	BigInteger& operator=(const BigInteger& rhs);
	BigInteger& operator=(const uint64_t& rhs);
	uint64_t operator[](const uint64_t& index) const;
	uint64_t& operator[](const uint64_t& index);

	// Binary //
	BigInteger operator+(const BigInteger& rhs) const;
	BigInteger operator+(const uint64_t& rhs) const;
	BigInteger operator-(const BigInteger& rhs) const;
	BigInteger operator-(const uint64_t& rhs) const;
	BigInteger operator*(const BigInteger& rhs) const;
	//BigInteger operator*(const uint64_t& rhs) const;
	BigInteger operator/(const BigInteger& rhs) const;
	//BigInteger operator/(const uint64_t& rhs) const;
	BigInteger operator%(const BigInteger& rhs) const;
	//BigInteger operator%(const uint64_t& rhs) const;

	// Binary Assignment //
	BigInteger& operator+=(const BigInteger& rhs);
	BigInteger& operator+=(const uint64_t& rhs);
	BigInteger& operator-=(const BigInteger& rhs);
	BigInteger& operator-=(const uint64_t& rhs);
	BigInteger& operator*=(const BigInteger& rhs);
	//BigInteger& operator*=(const uint64_t& rhs);
	BigInteger& operator/=(const BigInteger& rhs);
	//BigInteger& operator/=(const uint64_t& rhs);
	BigInteger& operator%=(const BigInteger& rhs);
	//BigInteger& operator%=(const uint64_t& rhs);

	// Bitwise //
	BigInteger operator~() const;
	BigInteger operator&(const BigInteger& rhs) const;
	BigInteger operator&(const uint64_t& rhs) const;
	BigInteger operator^(const BigInteger& rhs) const;
	BigInteger operator^(const uint64_t& rhs) const;
	BigInteger operator|(const BigInteger& rhs) const;
	BigInteger operator|(const uint64_t& rhs) const;
	BigInteger operator<<(const uint64_t& shift) const;
	BigInteger operator>>(const uint64_t& shift) const;

	// Bitwise Assignment //
	BigInteger& operator&=(const BigInteger& rhs);
	BigInteger& operator&=(const uint64_t& rhs);
	BigInteger& operator^=(const BigInteger& rhs);
	BigInteger& operator^=(const uint64_t& rhs);
	BigInteger& operator|=(const BigInteger& rhs);
	BigInteger& operator|=(const uint64_t& rhs);
	BigInteger& operator<<=(const uint64_t& shift);
	BigInteger& operator>>=(const uint64_t& shift);


	// Unary //
	BigInteger operator!() const;
	BigInteger operator-() const;
		// Prefix
	BigInteger& operator++();
	BigInteger& operator--();
		// Postfix
	BigInteger operator++(int);
	BigInteger operator--(int);

	// Relational //
	bool operator==(const BigInteger& rhs) const;
	bool operator!=(const BigInteger& rhs) const;
	bool operator<=(const BigInteger& rhs) const;
	bool operator<(const BigInteger& rhs) const;
	bool operator>=(const BigInteger& rhs) const;
	bool operator>(const BigInteger& rhs) const;

	// Flags //

	// Zero
	bool Z() const;
	// Negative
	bool N() const;
	// Odd
	bool O() const;

	friend std::ostream& operator<<(std::ostream& os,const BigInteger& num) {
		num.decPrint(os);
		return os;
	}

};

// Mersenne Prime Test: located in src/Functions/Primality.cpp
// If ((2 ^ `n`) - 1) is a prime number, then return the prime number
// Else return zero
// prints to `progress` the progress of it checking
BigInteger mersennePrime(
	const uint64_t n,
	std::ostream& progress
);

struct BigInteger::div_t { BigInteger quot; BigInteger rem; };

#endif
