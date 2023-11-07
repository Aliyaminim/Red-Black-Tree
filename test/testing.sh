#!/bin/bash

echo Testing has started!
echo 
echo "End-to-end tests:"
for file in e2e/*.in; do
    echo $file
    echo "RBT: "
    ../build/main_rbt < $file
    echo "Standard Set: "
    ../build/main_set < $file
    echo 
done