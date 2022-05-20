#!/bin/bash

echo 'C/C++: g++ build ./main_2.cpp file'

/usr/bin/g++ -pthread -g ./main_2.cpp -o ./main_2 -lrt
