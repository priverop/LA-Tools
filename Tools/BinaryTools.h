#ifndef BINARYTOOLS_H_
#define BINARYTOOLS_H_
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>
using namespace std;

class BinaryTools{
  public:
    BinaryTools();
    void createBinaryFile(const string& fileName, const string& content);
};

#endif
