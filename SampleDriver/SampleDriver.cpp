#include <iostream>

#include "BigInteger/BigInteger.hpp"

using namespace std;

//----------------------------------------------------------------------------//
// Test Function Declarations
//----------------------------------------------------------------------------//

void fib();
void power();
void prime();

//----------------------------------------------------------------------------//
// Main
//----------------------------------------------------------------------------//

int main(int argc, char* argv[]) {

	prime();

	return 0;
}

//----------------------------------------------------------------------------//
// Test function implementation
//----------------------------------------------------------------------------//

void fib() {

	// calculate the millionth fibonacci number //
	// should take about 90s

	BigInteger num1 = BigInteger(11000,0);
	BigInteger num2 = BigInteger(11000,1);
	BigInteger num3 = BigInteger(11000,0);

	cout << "calculating...\n";
	for(unsigned long long i = 2;i <= 1000000;++i) {
		num3 = num1;
		num3 += num2;
		num1 = num2;
		num2 = num3;
	}
	cout << "\tdone.\n";

	cout << "generating decimal...\n";
	cout << num1 << "\n";
}

void power() {
	// prints a bunch of powers of ten
	BigInteger num = BigInteger(10,10);
	for(uint64_t i = 0; i < 100;++i)
		cout << i << ":\t" << pow(num,i) << "\n";
}

void prime() {
	// Checks for primality and prints if prime
	// Should take about 15s
	BigInteger prime = mersennePrime(4423,std::cout);
	if(prime.Z()) std::cout << "Not a prime\n";
	else std::cout << prime << "\n";
}
