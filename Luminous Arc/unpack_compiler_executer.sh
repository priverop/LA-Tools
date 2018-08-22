#bin/bash
clear
rm -f ./la_unpack
rm -r ./extractor
g++ la_unpack.cpp ../Tools/HexTools.cpp ../Tools/BinaryTools.cpp -o la_unpack -std=c++11
./la_unpack ADVMSG05.iear
