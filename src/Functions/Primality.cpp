#include "../../BigInteger.hpp"

bool mersennePrime(const unsigned long long n, std::ostream& os) {

	unsigned long long size = (n / 32) + 1;

	BigInteger mer = BigInteger(1,size);
	mer <<= n;
	--mer;

	std::cout << "creating sequence element\n";
	BigInteger seq = BigInteger(4,size);

	unsigned long long every = 100;
	unsigned long long nm2 = n - 2;

	BigInteger temp = BigInteger(size);
	BigInteger high = BigInteger(size);
	unsigned long long iover = nm2 / every;
	for(unsigned long long j = nm2;j;--j) {
		if(j % every == 0) {
			std::cout << "\r\t"  << ((nm2 - j + 1)/every) + 1;
			std::cout << "/" << iover << std::flush;
		}
		temp = seq;
		seq *= temp;
		seq -= 2;
		do {
			high = seq;
			high >>= n;
			seq &= mer;
			seq += high;
		} while(seq > mer);
	}

	std::cout << "\tdone.\n";

	bool isPrime = seq.Z() || (seq == mer);
	if(isPrime) os << mer;

	return isPrime;
}
