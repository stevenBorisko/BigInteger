## BigInteger
This is a c++ class made for calculations of arbitrarily large numbers

## Makefile Setup
- Include BigInteger's makefile with: `include <path to>/BigInteger/BigInteger.mk`
- Add as a prerequisite for your executable target: `$(BIGINTEGER_MAIN_OBJ)`
- Add as a prerequisite for your clean target: `BigIntegerClean`
- Before compiling, the objectfile directory needs to be created with: `make BigIntegerObjectDirectory`

## Sample Driver
SampleDriver setup can be found in the README in the `SampleDriver` directory
