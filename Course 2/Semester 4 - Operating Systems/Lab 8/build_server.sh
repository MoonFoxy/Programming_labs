#!/bin/bash

echo 'C/C++: g++ build ./main_server.cpp file'

/usr/bin/g++ -pthread -g ./main_server.cpp -o ./main_server -lrt
