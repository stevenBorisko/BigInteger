# --- Definitions ---

CC := g++

# Flags for compiling and linking
SAMPLE_CFLAGS := -std=c++11 -O3
SAMPLE_LFLAGS :=

EXEC := execute.out

compile: $(EXEC)
	@echo "- - - - Project compiled - - - -"
	@echo "Executable: $(EXEC)"

test: compile
	time ./$(EXEC)

SAMPLE_PATH := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))

# This is where the SAMPLE_SUB_OBJS will be stored so your work doesn't
#     get cluttered with *.o files
_SAMPLE_OBJDIR := .ObjectFiles/
SAMPLE_OBJDIR := $(SAMPLE_PATH)$(_SAMPLE_OBJDIR)

# Files on which all the implementation files depend
_SAMPLE_DEPS := BigInteger/BigInteger.hpp
SAMPLE_DEPS := $(foreach OBJ,$(_SAMPLE_DEPS),$(SAMPLE_PATH)$(OBJ))

_SAMPLE_MAIN_OBJ := SampleDriver.o
SAMPLE_MAIN_OBJ := $(SAMPLE_OBJDIR)$(_SAMPLE_MAIN_OBJ)

include $(SAMPLE_PATH)BigInteger/BigInteger.mk

# --- Rules ---

$(EXEC): $(SAMPLE_MAIN_OBJ) $(BIGINTEGER_MAIN_OBJ)
	$(CC) $(SAMPLE_CFLAGS) $^ -o $@ $(SAMPLE_LFLAGS)

# Sub objects
# Compile implementation file
$(SAMPLE_OBJDIR)%.o: $(SAMPLE_PATH)%.cpp $(SAMPLE_DEPS)
	$(CC) -c $(SAMPLE_CFLAGS) $< -o $@

# Object Directory Creation
# This creates the object directory for Sample and the directory for Other
SampleObjectDirectory: BigIntegerObjectDirectory
	mkdir -p $(SAMPLE_OBJDIR)
	@echo "- - - - Sample ObjectFile directory created - - - -"

# Clean
# Removes all object directories from Sample and Other
SampleClean: BigIntegerClean
	rm -f $(SAMPLE_MAIN_OBJ) $(EXEC)
