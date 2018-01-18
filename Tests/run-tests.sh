#!/usr/bin/env bash

cd ../

function runTests {
    FILES=$1
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
}
abc=Tests/correct/*.lat
runTests "$abc"


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

runTests Tests/extensions/struct/*.lat
