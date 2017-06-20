#!/bin/bash

echo "========================================"
echo " Cleaning the temporaries and outputs"
make clean
echo " Building..."
make bin/c_parser -B
if [[ "$?" -ne 0 ]]; then
    echo "Build failed.";
fi
mkdir -p working
echo ""
cat test/c_parser/test_parser.c | ./bin/c_parser | tee working/output_1.txt
