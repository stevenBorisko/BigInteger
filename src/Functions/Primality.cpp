#include "../../BigInteger.hpp"

bool mersennePrime(const uint64_t n, std::ostream& os) {

	uint64_t size = (n / 32) + 1;

	BigInteger mer = BigInteger(size,1);
	mer <<= n;
	--mer;

	std::cout << "creating sequence element\n";
	BigInteger seq = BigInteger(size,4);

	uint64_t every = 100;
	uint64_t nm2 = n - 2;

	BigInteger temp = BigInteger(size);
	BigInteger high = BigInteger(size);
	uint64_t iover = nm2 / every;
	for(uint64_t j = nm2;j;--j) {
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
