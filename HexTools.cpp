#include "HexTools.h"
using namespace std;

HexTools::HexTools(){};

// https://stackoverflow.com/questions/3381614/c-convert-string-to-hexadecimal-and-vice-versa

string HexTools::hexToString(const string& hex){
  int len = hex.length();
  string newString;
  for(int i=0; i<len; i+=2)
  {
      string byte = hex.substr(i,2);
      char chr = (char) (int)strtol(byte.c_str(), nullptr, 16);
      newString.push_back(chr);
  }
  return newString;
}

string HexTools::stringToHex(const string& s){
    ostringstream ret;

    for (string::size_type i = 0; i < s.length(); ++i){
      int z = s[i]&0xff;
      ret << hex << setfill('0') << setw(2) << uppercase << z;
    }

    return ret.str();
}

string HexTools::string8to16(const string& word){
  string word16;
  string word16_hex;
  string word_hex = stringToHex(word);
  for (int i = 2; i <= word_hex.size(); i+=4) {
    word_hex.insert(i, "00");
  }
  return hexToString(word_hex);
}
