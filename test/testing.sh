#!/bin/bash

echo Testing has started!
echo 
echo "End-to-end tests:"
for file in $(find . -name "test2*" ! -name "test2.in"); do
    echo $file
    echo "RBT: "
    ../build/main_rbt < $file
    echo "Standard Set: "
    line=$(head -n 3 $file | tail -n 1)
    echo "$line"
    echo 
done
for file in $(find . -name "test*.in" -not -name "test2*"); do
    echo $file
    echo "RBT: "
    ../build/main_rbt < $file
    echo "Standard Set: "
    ../build/main_set < $file
    echo 
done