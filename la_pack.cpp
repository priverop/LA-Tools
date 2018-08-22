#include "HexTools.h"
#include "BinaryTools.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <iomanip>
#include <sys/stat.h>

int main(int argc, char* argv[]){

  HexTools tools;
  BinaryTools bTools;


  /*
    - Creamos el .iear final.
    - Abrir el fileList y recorrer.
    - Por cada fichero:
      - Se abre, y se escribe en el final.

  */

  if(argc < 2){
    cout << "Not enough arguments." << endl;
    cout << "USAGE: main fileList.txt" << endl;
  }
  else{
    string inputTxtName = argv[1];
    ifstream inputTxtFile; // fileList.txt

    // Abrimos el fileList.txt
    inputTxtFile.open(inputTxtName);

    if (inputTxtFile.is_open()){

      cout << "== LUMINOUS ARC IEAR PACKER by Nex ==" << endl << endl;
      cout << "Iniciando el empaquetado..." << endl << endl;

      // Creamos el fichero .iear en el que meteremos todo
      ofstream newIear("TEST.iear");

      string fileName;

      while (getline(inputTxtFile, fileName)) {

          // Sacamos cada nombre de fichero
          cout << "Empaquetando " << fileName << "..." << endl;

          // Abrimos fichero y guardamos su contenido
          ifstream fileToPack;
          uint32_t size;
          fileToPack.open(fileName, ios::in | ios::binary | ios::ate);

          if (fileToPack.is_open()){
            size = fileToPack.tellg();
            char * fileContent = new char [size];
            fileToPack.seekg(0, ios::beg);
            fileToPack.read(fileContent, size);
            // Guardamos en el fichero completo
            newIear.write(fileContent, size);
          }
          else{
            std::cout << "Error opening " << fileName << '\n' << endl;
          }

      }
      inputTxtFile.close();
    } // if inputTxtFile is_open
  } // if arguments correct




return 0;
}
