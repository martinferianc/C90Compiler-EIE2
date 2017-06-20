#!/bin/bash

SRCFILE=$1  # Program to test
MIPS=$2  # Try generating mips?

echo " Cleaning the temporaries and outputs"
echo "========================================"
mkdir -p working
rm -rf working/*
echo "========================================"

echo " Building Pretty print"
echo "========================================"
make bin/c_compiler_pretty_print
echo "========================================"

if [[ "$?" -ne "0" ]]; then
    echo "Error while building compiler."
    exit 1;
fi

b=$(basename ${SRCFILE});
mkdir -p working/$b

cat test/c_compiler/$b/$b.c | ./bin/c_compiler_pretty_print | tee working/$b/$b.s
cat test/c_compiler/$b/$b.c | ./bin/c_compiler_pretty_print X Y | tee working/$b/pretty.txt

if [[ "${MIPS}" == "Y" ]]; then
    mips-linux-gnu-gcc -static test/c_compiler/$b/$b.c -o a
    mips-linux-gnu-gcc -static -c -S test/c_compiler/$b/$b.c
    mv a test/c_compiler/$b/exe
    mv $b.s test/c_compiler/$b/$b.s
    qemu-mips test/c_compiler/$b/exe

    REF_RESULT=$?;

    echo "${REF_RESULT}" > test/c_compiler/$b/$b.txt

    echo "Running $b Assembly into executable"

    mips-linux-gnu-gcc -static working/$b/$b.s -o a
    mv a working/$b/$b


    echo "Running $b MY EXECUTABLE"
    qemu-mips working/$b/$b

    MY_RESULT=$?;


    if [[ "${MY_RESULT}" -ne "${REF_RESULT}" ]]; then
        echo "  got result : ${MY_RESULT}"
        echo "  ref result : ${REF_RESULT}"
        echo "  FAIL!";
    fi
fi
