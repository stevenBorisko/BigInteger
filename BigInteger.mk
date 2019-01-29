# make <BigInteger path>/BigInteger.o a prerequisite for your executable

# --- Definitions ---

BIGINTEGER_PATH := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
BIGINTEGER_MAIN_OBJ := $(BIGINTEGER_PATH)BigInteger.o
BIGINTEGER_CFLAGS := -std=c++11 -O3
BIGINTEGER_LFLAGS :=

include $(BIGINTEGER_PATH)src/DynamicDecimal/DynamicDecimal.mk

BIGINTEGER_OBJDIR := $(BIGINTEGER_PATH).ObjectFiles/
BigIntegerObjectDirectory:
	mkdir -p $(BIGINTEGER_OBJDIR)
	mkdir -p $(BIGINTEGER_OBJDIR)src/
	mkdir -p $(BIGINTEGER_OBJDIR)src/Functions/
	mkdir -p $(BIGINTEGER_OBJDIR)src/OperatorOverloads/
	@echo "- - - - BigInteger ObjectFile directory created - - - -"

_BIGINTEGER_DEPS := BigInteger.hpp src/DynamicDecimal/DynamicDecimal.hpp
BIGINTEGER_DEPS := $(foreach OBJ,$(_BIGINTEGER_DEPS),$(BIGINTEGER_PATH)$(OBJ))

_BIGINTEGER_SUB_OBJS := \
	src/Constructors.o \
	src/Flags.o \
	src/Functions/Math.o \
	src/Functions/Primality.o \
	src/Functions/Printing.o \
	src/Functions/Setting.o \
	src/OperatorOverloads/Assignment.o \
	src/OperatorOverloads/Binary.o \
	src/OperatorOverloads/BinaryAssign.o \
	src/OperatorOverloads/Bitwise.o \
	src/OperatorOverloads/BitwiseAssign.o \
	src/OperatorOverloads/Relational.o \
	src/OperatorOverloads/Unary.o
BIGINTEGER_SUB_OBJS := $(DYNAMICDECIMAL_MAIN_OBJ) \
	$(foreach OBJ,$(_BIGINTEGER_SUB_OBJS),$(BIGINTEGER_OBJDIR)$(OBJ))

# --- Rules ---

# Main object
$(BIGINTEGER_MAIN_OBJ): $(BIGINTEGER_SUB_OBJS) $(DYNAMICDECIMAL_MAIN_OBJ)
	@echo "- - - - BigInteger compiled - - - -"
	$(LD) -r $(BIGINTEGER_LFLAGS) $^ -o $@
	@echo "- - - - BigInteger linked - - - -"

# Sub objects
$(BIGINTEGER_OBJDIR)%.o: $(BIGINTEGER_PATH)%.cpp $(BIGINTEGER_DEPS) 
	$(CC) -c $(BIGINTEGER_CFLAGS) $< -o $@

# Clean
BigIntegerClean: DynamicDecimalClean
	rm -f $(BIGINTEGER_SUB_OBJS) $(BIGINTEGER_MAIN_OBJ)
