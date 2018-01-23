#!/usr/bin/env bash

cd ../

function runTests {
    FILES=$1
    lli=~/MRJP/llvm39/bin/lli
    if [ ! -f $lli ]; then
        lli="lli-3.9"
    fi
    for i in $FILES
    do
        echo "running $i"
        ./latc_llvm $i
        result="${i/.lat/.bc}"
        echo $result
        input="${i/.lat/.input}"
        if [ -f $input ]; then
            echo "lli-3.9 $result > out.tmp < $input"
            lli-3.9 $result > out.tmp < $input
        else
            lli-3.9 $result > out.tmp
        fi
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

runTests "Tests/extensions/struct/*.lat"
runTests "Tests/extensions/objects1/*.lat"

runTests "Tests/extensions/objects2/*.lat"

#runTests "Tests/mrjp-tests/good/basic/*.lat"
#runTests "Tests/mrjp-tests/bad/semantic/*.lat"
