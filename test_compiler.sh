#!/bin/bash
echo " Cleaning the temporaries and outputs"
echo "========================================"

rm -f bin/*
rm -rf working

echo "========================================"

mkdir -p working

echo " Force building compiler"
echo "========================================"
make bin/c_compiler
echo "========================================"

if [[ "$?" -ne "0" ]]; then
    echo "Error while building compiler."
    exit 1;
fi

echo "========================================="
echo "| TEST | OUTPUT | REFERENCE OUTPUT |" > working/log.txt

PASSED=0
CHECKED=0
NO=1

for i in test/c_compiler/*; do
  b=$(basename ${i});
  mkdir -p working/$b

  echo "========================================="
  echo "Input file : ${i}"
  echo "${NO}. Test $b"

  echo "Running $b on a MIPS test machine"

  FILE=$i/$b.txt
  if [ -f "$FILE" ]
    then
      REF_RESULT=$(head -n 1 $FILE);
    else
      mips-linux-gnu-gcc -static $i/$b.c -o $i/exe
      mips-linux-gnu-gcc -static -c -S $i/$b.c $i/$b.s
      mv $b.s $i/$b.s
      qemu-mips $i/exe
      REF_RESULT=$?;
      echo "${REF_RESULT}" > $i/$b.txt
  fi


  echo "Running $b on a MY COMPILER"
  cat $i/$b.c | ./bin/c_compiler $i/$b.c > working/$b/$b.s

  echo "Running $b Assembly into executable"
  mips-linux-gnu-gcc -static working/$b/$b.s -o working/$b/$b

  echo "Running $b MY EXECUTABLE"
  qemu-mips working/$b/$b

  MY_RESULT=$?;

  echo "${MY_RESULT}" > working/$b/$b.txt

  OK=0;

  if [[ "${MY_RESULT}" -ne "${REF_RESULT}" ]]; then
      echo "  got result : ${MY_RESULT}"
      echo "  ref result : ${REF_RESULT}"
      echo "  FAIL!";
      printf "| %20s | %5s | %5s | \n" ${b} ${MY_RESULT} ${REF_RESULT}  >> working/log.txt
      OK=1;
  fi


  if [[ "$OK" -eq "0" ]]; then
      PASSED=$(( ${PASSED}+1 ));
  fi

  CHECKED=$(( ${CHECKED}+1 ));

  NO=$(( ${NO}+1 ));
  echo "========================================="
  echo ""
done

echo "########################################"
echo "Passed ${PASSED} out of ${CHECKED}".
echo "########################################"

echo "########################################" >> working/log.txt
echo "Passed ${PASSED} out of ${CHECKED}". >> working/log.txt
echo "########################################" >> working/log.txt
