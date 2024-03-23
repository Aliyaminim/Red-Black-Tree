# Red-Black-Tree
Implementation of a class Red Black Tree

## Task
The input consists of keys (each key is an integer, all keys are different) and queries (each query is a pair of two integers, the second one is greater than the first). For each query, we need to count the number of keys in the tree such that they all lie strictly between its left and right boundaries inclusive.

• Input: k 10 k 20 q 8 31 q 6 9 k 30 k 40 q 15 40.

• Output: 2 0 3.

Query (m) for finding the k-th smallest element. If the zeroth (minus first and so on) smallest is requested, an error should be returned with a non-zero return code. If the smallest element with a number greater than the total number of elements in the tree is requested, simply return the last smallest (i.e., the largest).
Query (n) for finding the number of elements less than a given number.

• Input: k 8 k 2 k -1 m 1 m 2 n 3

• Output: -1 2 2.

Keys can be arbitrarily mixed with queries.

## How to build
```bash
git clone https://github.com/Aliyaminim/Red-Black-Tree
cd Red-Black-Tree
cmake -S ./ -B build/
cd build/
cmake --build .
```

## How to run the program
```bash
./main_rbt < [file]
```

## How to test the program
```bash
cd ../test
bash testing.sh
```

    

