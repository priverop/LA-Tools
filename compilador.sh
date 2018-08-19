#bin/bash
clear
rm -f ./main
rm -f ./MainLevel_translated
g++ main.cpp -o main -std=c++11
./main MainLevel --i MainLevel.txt
