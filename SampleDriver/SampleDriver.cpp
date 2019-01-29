#include <iostream>

#include "../BigInteger.hpp"

using namespace std;

int main(int argc, char* argv[]) {

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

	return 0;
}
