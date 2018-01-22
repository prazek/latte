#!/bin/bash

antlr4='java -jar /usr/local/lib/antlr-4.7.1-complete.jar'
$antlr4 -Dlanguage=Cpp -no-listener -visitor Latte.g4
