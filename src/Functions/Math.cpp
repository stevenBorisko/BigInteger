#include "../../BigInteger.hpp"

BigInteger abs(const BigInteger& num) {
	return (num.N() ? -(num) : BigInteger(num));
}

BigInteger sqrt(const BigInteger& num) {
	if(num.Z()) return num;
	if(num.N()) {
		//std::cout << "sqrt: negative radicand\n";
		return num;
	}

	BigInteger temp = BigInteger(1,num.size);
	if(num == temp) return temp;

	BigInteger ret = BigInteger(num);

	unsigned long long digitsIn = num.size - 1;
	unsigned long long insideBits = 64;
	unsigned long long mask = num.left;

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

	for(unsigned long long i = num.size;i;--i) {
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
	BigInteger acc = BigInteger(1,num.size);

	bool thisZ = num.Z();
	bool expZ = num.Z();
	if(thisZ & expZ) {
		//std::cout << "pow: 0 ^ 0\n";
		return acc;
	}

	if(expZ) return acc;
	if(thisZ) {
		acc.digits[0] = 0;
		return acc;
	}


	BigInteger expCopy = BigInteger(exp);
	BigInteger numCopy = BigInteger(num);
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

BigInteger pow(const BigInteger& num, const unsigned long long& exp) {
	return pow(num, BigInteger(exp,1));
}

BigInteger fact(const BigInteger& num) {
	BigInteger ret = BigInteger(1,num.size);
	if(num.N()) {
		//std::cout << "fact: negative number\n";
		return ret;
	}
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
	BigInteger mod = BigInteger(1,num1.size);
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

	unsigned long long index = 0;
	unsigned long long mask = 1;

	do {
		for(mask = 1; mask; mask <<= 1) {
			if(mask & num.digits[index]) ret = counter;
			++counter;
		}
	} while(++index < num.size);

	return ret;
}
