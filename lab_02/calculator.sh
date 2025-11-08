#!/bin/bash

while true
do
# Take user input
echo "Enter two numbers:"
read a
read b

# Input type of operation
echo "Enter choice:"
echo "1. Addition"
echo "2. Subtraction"
echo "3. Multiplication"
echo "4. Division"
echo "5. Exit"
read ch

# Perform calculator operations using case statement
case $ch in
  1)
    res=$(echo "$a + $b" | bc)
    ;;
  2)
    res=$(echo "$a - $b" | bc)
    ;;
  3)
    res=$(echo "$a * $b" | bc)
    ;;
  4)
    # Check for division by zero
    if [ "$b" -eq 0 ]; then
      echo "Error: Division by zero"
      exit 1
    fi
    res=$(echo "scale=2; $a / $b" | bc)
    ;;
  5)
	echo "Exit"
	break
  	;;
  *)
    echo "Invalid choice"
    exit 1
    ;;
esac

echo "Result: $res"
done

