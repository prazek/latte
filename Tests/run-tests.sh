#!/usr/bin/env bash

cd ../
FILES=Tests/correct/*.lat
for i in $FILES
do
    echo "running $i"
    ./latc_llvm $i
    result="${i/.lat/.bc}"
    echo $result
    lli-3.9 $result > out.tmp
    real="${i/.lat/.output}"
    echo $real
    diff $real out.tmp

done

FILES=Tests/bad/*.lat
for i in $FILES
do
    echo "running $i"
    ./latc_llvm $i
    if [ $? -eq 0 ]; then
        echo "Not issued error!!!"
        echo "."
        echo "."
    fi

    result="${i/.lat/.bc}"

done
