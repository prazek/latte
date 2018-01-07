#!/usr/bin/env bash

cd ../
FILES=Tests/correct/*.lat
for i in $FILES
do
    echo "running $i"
    ./latc_llvm $i
    result="${i/.lat/.bc}"
    echo $result
    lli $result > out.tmp
    real="${i/.lat/.output}"
    echo $real
    diff $real out.tmp

done

