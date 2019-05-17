project(BigInteger LANGUAGES CXX)

set(BigInteger_SRC
	src/Constructors.cpp
	src/Flags.cpp
	src/Functions/Math.cpp
	src/Functions/Primality.cpp
	src/Functions/Printing.cpp
	src/Functions/Setting.cpp
	src/OperatorOverloads/Assignment.cpp
	src/OperatorOverloads/BinaryAssign.cpp
	src/OperatorOverloads/Binary.cpp
	src/OperatorOverloads/BitwiseAssign.cpp
	src/OperatorOverloads/Bitwise.cpp
	src/OperatorOverloads/Relational.cpp
	src/OperatorOverloads/Unary.cpp
	)

set(BigInteger_HDR
	BigInteger.hpp
	)

set(DynamicDecimal_SRC src/DynamicDecimal/DynamicDecimal.cpp)
set(DynamicDecimal_HDR src/DynamicDecimal/DynamicDecimal.hpp)

set(BigInteger_FILES ${BigInteger_SRC} ${BigInteger_HDR})
set(DynamicDecimal_FILES ${DynamicDecimal_SRC} ${DynamicDecimal_HDR})

add_library(BigInteger ${BigInteger_FILES} ${DynamicDecimal_FILES})
