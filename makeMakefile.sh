#!/bin/bash

IMPEXT=".cpp"
OBJEXT=".o"
CC="g++"
CFLAGS="-O3 -std=c++!1"
LDFLAGS=""
EXEC="execute.out"
# OBJDIR MUST BE FILLED NOT SET TO A DIRECTORY CONTAINING IMPORTANT FILES !!
# Read under target `clean` for reasoning
OBJDIR=".ObjectFiles/" # This cannot be empty or filled with important files!
# ^ Did you change this to somewhere important or leave it empty?
# If so, fix that!

IMPFILES=$(find * -name "*$IMPEXT")

echo "CC := "$CC
echo "CFLAGS := "$CFLAGS
echo "LDFLAGS := "$LDFLAGS
echo "EXEC := "$EXEC
echo ""
echo '# OBJDIR MUST BE SET AND SET NOT TO A DIRECTORY'
echo '# CONTAINING IMPORTANT FILES !! SEE TARGET `CLEAN` FOR REASONING'
echo "OBJDIR := "$OBJDIR
echo -e "OBJS := \\"
for file in $IMPFILES; do
	OBJECTFILE=${file%$IMPEXT}$OBJEXT
	echo -e "\t""\$(OBJDIR)"${OBJECTFILE##*/}" \\"
done
echo ""
echo "compile: \$(OBJS)"
echo -e "\t\$(CC) \$(OBJS) -o \$(EXEC) \$(LDFLAGS)"
echo ""
for file in $IMPFILES; do
	echo -n "\$(OBJDIR)"
	$CC -M $file
	echo -e "\t\$(CC) -c \$< -o \$@ \$(CFLAGS)"
done
echo "clean:"
echo -e "\trm -f \$(OBJDIR)/* \$(EXEC)"
