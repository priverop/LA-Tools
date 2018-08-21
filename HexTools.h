#ifndef HEXTOOLS_H_
#define HEXTOOLS_H_
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

class HexTools{
  public:
    HexTools();
    string hexToString(const string& hex);
    string stringToHex(const string& s);
    string string8to16(const string& word);
};

#endif
