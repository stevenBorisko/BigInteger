#include "../../BigInteger.hpp"

BigInteger mersennePrime(
	const uint64_t n,
	std::ostream& progress
) {

	uint64_t size = (n / 32) + 1;

	BigInteger mer = BigInteger(size,1);
	mer <<= n;
	--mer;

	progress << "((2 ^ " << n << ") - 1) primality check\n";
	BigInteger seq = BigInteger(size,4);

	uint64_t every = 100;
	uint64_t nm2 = n - 2;

	BigInteger temp = BigInteger(size);
	BigInteger high = BigInteger(size);
	uint64_t iover = nm2 / every;
	for(uint64_t j = nm2;j;--j) {
		if(j % every == 0) {
			progress << "\r\t"  << ((nm2 - j + 1)/every) + 1;
			progress << "/" << iover << std::flush;
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

	bool isPrime = seq.Z() || (seq == mer);
	progress << (isPrime ? " " : " not ") << "prime\n";
	return isPrime ? mer : BigInteger(1);
}
