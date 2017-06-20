#!/bin/bash

echo "========================================"
echo " Cleaning the temporaries and outputs"
make clean
echo " Building..."
make bin/c_lexer -B
if [[ "$?" -ne 0 ]]; then
    echo "Build failed.";
fi
cat test/c_lexer/everything.txt | ./bin/c_lexer | tee bin/output.txt
