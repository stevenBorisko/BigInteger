#include "../../BigInteger.hpp"

BigInteger abs(const BigInteger& num) {
	return (num.N() ? -num : num);
}

BigInteger sqrt(const BigInteger& num) {

	// Error handling
	if(num.N()) {
		std::cerr << "sqrt(const BigInteger&): negative input\n";
		std::cerr << "\tcomplex numbers have not been implemented\n";
		exit(1);
	}

	// Easy sauce
	if(num.Z()) return num;

	// Now actually calculate
	BigInteger temp = BigInteger(num.size,1);
	if(num == temp) return temp;

	BigInteger ret = BigInteger(num);

	uint64_t digitsIn = num.size - 1;
	uint64_t insideBits = 64;
	uint64_t mask = num.left;

	while(!(mask & num.digits[digitsIn])) {
		--insideBits;
		mask >>= 1;
		if(!mask) {
			--digitsIn;
			insideBits = 64;
			mask = num.left;
		}
	}

	if(digitsIn & 1) {
		insideBits = 64 - insideBits;
	}
	else {
		insideBits >>= 1;
	}

	digitsIn >>= 1;
	while(digitsIn--) {
		ret >>= 64;
	}

	ret >>= insideBits;

	for(uint64_t i = num.size;i;--i) {
		for(unsigned char j = 2;j;--j) {
			temp = num;
			temp /= ret;
			ret += temp;
			ret >>= 1;
		}
	}
	temp = ret;
	temp *= ret;
	if(temp > num) --ret;
	return ret;
}

BigInteger pow(const BigInteger& num, const BigInteger& exp) {
	BigInteger acc = BigInteger(num.size,1);
	bool numZ = num.Z();
	bool expZ = exp.Z();

	// Error handling
	if(numZ & expZ) {
		std::cerr << "pow(const BigInteger&, const BigInteger&): (0,0) input\n";
		exit(1);
	}

	// Easy sauce
	if(numZ) return num;
	if(expZ) return acc;

	// Now actually calculate
	BigInteger numCopy = BigInteger(num);
	BigInteger expCopy = BigInteger(exp);
	while(!expCopy.Z()) {
		while(!expCopy.O()) {
			numCopy *= numCopy;
			expCopy >>= 1;
		}
		acc *= numCopy;
		--expCopy;
	}
	return acc;
}

BigInteger pow(const BigInteger& num, const uint64_t& exp) {
	BigInteger acc = BigInteger(num.size,1);
	bool numZ = num.Z();
	bool expZ = !exp;

	// Error handling
	if(numZ & expZ) {
		std::cerr << "pow(const BigInteger&, const uint64_t&): (0,0) input\n";
		exit(1);
	}

	// Easy sauce
	if(numZ) return num;
	if(expZ) return acc;

	// Now actually calculate
	BigInteger numCopy = BigInteger(num);
	uint64_t expCopy = exp;
	while(expCopy) {
		while(!(expCopy & 1)) {
			numCopy *= numCopy;
			expCopy >>= 1;
		}
		acc *= numCopy;
		--expCopy;
	}
	return acc;
}

BigInteger fact(const BigInteger& num) {
	BigInteger ret = BigInteger(num.size,1);

	// Error handling
	if(num.N()) {
		std::cerr << "fact(const BigInteger&): negative input\n";
		exit(1);
	}

	// Easy sauce
	if(num.Z() || num == ret) return ret;

	BigInteger copy = BigInteger(num);
	do {
		ret *= copy;
		--copy;
	}while(!copy.Z());

	return ret;
}

bool divisible(const BigInteger& num1, const BigInteger& num2) {
	return (num1 % num2).Z();
}

BigInteger gcd(const BigInteger& num1, const BigInteger& num2) {
	BigInteger mod = BigInteger(num1.size,1);
	BigInteger a = BigInteger(num1);
	BigInteger b = BigInteger(num2);

	mod = a;
	mod %= b;

	while(!mod.Z()) {
		a = b;
		b = mod;
		mod = a;
		mod %= b;
	}

	return b;

}

BigInteger log(const BigInteger& num) {

	BigInteger ret = BigInteger(num.size);
	BigInteger counter = BigInteger(num.size);

	// Error handling
	if(num.N()) {
		std::cerr << "log(const BigInteger&): negative input\n";
		exit(1);
	}
	if(num.Z()) {
		std::cerr << "log(const BigInteger&): zero input\n";
		exit(1);
	}

	uint64_t index = 0;
	uint64_t mask = 1;

	do {
		for(mask = 1; mask; mask <<= 1) {
			if(mask & num.digits[index]) ret = counter;
			++counter;
		}
	} while(++index < num.size);

	return ret;
}
