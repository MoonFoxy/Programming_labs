#!/bin/bash

echo 'C/C++: g++ build ./main_1.cpp file'

/usr/bin/g++ -pthread -g ./main_1.cpp -o ./main_1 -lrt
