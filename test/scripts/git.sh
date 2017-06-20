#!/bin/bash -e
commit_message="$1"
echo "========================================"
echo " Cleaning the temporaries and outputs"
make clean
echo "========================================"
echo "========================================"
echo " Commiting..."
git add -A
git commit -m "$commit_message"
echo "========================================"
echo "========================================"
echo " Pushing..."
git push origin master
echo "========================================"
