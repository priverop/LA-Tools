#bin/bash
clear
rm -f ./la_pack
rm -f ./TEST.iear
g++ la_pack.cpp ../Tools/HexTools.cpp ../Tools/BinaryTools.cpp -o la_pack -std=c++11
./la_pack fileList.txt
