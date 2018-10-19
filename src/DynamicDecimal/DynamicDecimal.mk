# make <DynamicDecimal path>/DynamicDecimal.o a prerequisite for your executable

# --- Definitions ---

DYNAMICDECIMAL_PATH := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
DYNAMICDECIMAL_MAIN_OBJ := $(DYNAMICDECIMAL_PATH)DynamicDecimal.o
DYNAMICDECIMAL_CFLAGS := $(BIGINTEGER_CFLAGS)
DYNAMICDECIMAL_LFLAGS := $(BIGINTEGER_LGLAGS)

_DYNAMICDECIMAL_DEPS := DynamicDecimal.hpp
DYNAMICDECIMAL_DEPS := $(foreach OBJ,$(_DYNAMICDECIMAL_DEPS),$(DYNAMICDECIMAL_PATH)$(OBJ))

# --- Rules ---

# Main object
$(DYNAMICDECIMAL_MAIN_OBJ): \
	$(DYNAMICDECIMAL_PATH)DynamicDecimal.cpp \
	$(DYNAMICDECIMAL_DEPS)
	$(CC) -c $(DYNAMICDECIMAL_CFLAGS) $< -o $@
	@echo "- - - - DynamicDecimal compiled and linked - - - -"

# Clean
DynamicDecimalClean:
	rm -f $(DYNAMICDECIMAL_MAIN_OBJ)
