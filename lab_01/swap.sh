#!/bin/bash
echo "swapper"
echo "enter the first number"
read a
echo "enter the second number"
read b
c=$a
a=$b
b=$c
echo "a is $a"
echo "b is $b"
