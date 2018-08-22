#include "BinaryTools.h"
using namespace std;

BinaryTools::BinaryTools(){};

void BinaryTools::createBinaryFile(const string& fileName, const string& content){
  std::ofstream outfile (fileName);
  outfile << content;
  cout << fileName << " creado correctamente." << endl << endl;
  outfile.close();
}
