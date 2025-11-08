#!/bin/bash
echo "prime number check'er"
echo "enter the number to check"
read a
echo "the number that you have entered is" 
echo "$a"
for (( i=2 ; i<a; i++ ))
do
	if [ $((a % i)) -eq 0 ]
	then 
	echo "the number is not prime" 
	exit
	fi
done
echo "the entered number is prime" 

