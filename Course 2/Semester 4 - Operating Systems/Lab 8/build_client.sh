#!/bin/bash

echo 'C/C++: g++ build ./main_client.cpp file'

/usr/bin/g++ -pthread -g ./main_client.cpp -o ./main_client -lrt
