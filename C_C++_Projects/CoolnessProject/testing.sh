#!/usr/bin/bash

# For coolness 

# Test for No args
echo "Test No args"
./coolness
echo -e "\n"

# Test for  One arg
echo "Test One arg"
./coolness 16
echo -e "\n"

# Test Two args
echo "Test Two args"
./coolness 16 16
echo -e "\n"

# Test More than two args
echo "Test more than two args "
./coolness 16 20 9
echo -e "\n"

# Test non number
echo "Test Non numeric input"
./coolness "twenty" "ten"
echo -e "\n"




# Clean up
rm -f output.txt

