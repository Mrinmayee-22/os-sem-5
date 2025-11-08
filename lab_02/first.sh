#!/bin/bash
echo "hello world"
echo "enter your number"
read a
if [ $((a % 2)) -eq 0 ]
then 
echo "your number is even"
else 
echo "your number is odd"
fi

