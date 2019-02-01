#include <iostream>

#include "BigInteger/BigInteger.hpp"

using namespace std;

//----------------------------------------------------------------------------//
// Test Function Declarations
//----------------------------------------------------------------------------//

void fib();
void power();

//----------------------------------------------------------------------------//
// Main
//----------------------------------------------------------------------------//

int main(int argc, char* argv[]) {

	fib();

	return 0;
}

//----------------------------------------------------------------------------//
// Test function implementation
//----------------------------------------------------------------------------//

void fib() {

	// calculate the millionth fibonacci number //
	// should take about 90s

	BigInteger num1 = BigInteger(0,11000);
	BigInteger num2 = BigInteger(1,11000);
	BigInteger num3 = BigInteger(0,11000);

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
	BigInteger num = BigInteger(10,10);
	for(uint64_t i = 0; i < 100;++i)
		cout << i << ":\t" << pow(num,i) << "\n";
}
