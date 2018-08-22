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

  const string FOOTER = "454E4454000000000000000000000000";

  if(argc < 2){
    cout << "Not enough arguments." << endl;
    cout << "USAGE: main fileToExtract" << endl;
  }
  else{
    string inputFileName = argv[1];
    ifstream inputFile;
    uint32_t size;
    const string folderName = "./extract";
    unsigned int block_number = 0;
    uint32_t offset = 0x20; // Nos saltamos los 32bytes de la cabecera (0x20 = 32)
    string fileName;

    inputFile.open(inputFileName, ios::in | ios::binary | ios::ate);

      if (inputFile.is_open())
      {
        size = inputFile.tellg();
        cout << "== LUMINOUS ARC EXTRACTOR by Nex ==" << endl << endl;
        cout << "Iniciando la extracción..." << endl << endl;

        // Guardamos los primeros 4bytes tras la tabla de punteros para tomarlo como fin de bucle
        uint32_t first_pointer;
        inputFile.seekg(offset, ios::beg);
        inputFile.read (reinterpret_cast<char *>(&first_pointer), sizeof(first_pointer));

        uint32_t end_table;
        inputFile.seekg(first_pointer, ios::beg);
        inputFile.read (reinterpret_cast<char *>(&end_table), sizeof(end_table));

        if (mkdir(folderName.c_str(), S_IRWXU | S_IRWXG | S_IRWXO) != 0)
        {
          cout << "Error creating extract folder" << endl;
          cout << "Please delete the folder" << endl;
        }
        else{

          // Guardamos la cabecera del fichero
          char header[offset];
          inputFile.seekg(0, ios::beg);
          inputFile.read(header, offset);
          fileName = "Header";

          bTools.createBinaryFile(folderName + "/" + to_string(block_number) + " - " + fileName,
          string(header, offset));

          block_number++;

          uint32_t pointer_beg_block;
          uint32_t block_size;

          while(offset != first_pointer){

            // Almacenamos los 8 bytes del puntero del inicio del bloque

            inputFile.seekg(offset, ios::beg);
            inputFile.read (reinterpret_cast<char *>(&pointer_beg_block), sizeof(pointer_beg_block));

            offset += sizeof(pointer_beg_block);

            // Almacenamos los 8 bytes del tamaño de bloque

            inputFile.seekg(offset, ios::beg);
            inputFile.read (reinterpret_cast<char *>(&block_size), sizeof(block_size));

            offset += sizeof(block_size);

            // Almacenamos el bloque
            char * block = new char [block_size];
            inputFile.seekg(pointer_beg_block, ios::beg);
            inputFile.read (block, block_size);
            // Nombre del archivo
            fileName = string(block, sizeof(uint32_t));

            // Guardamos bloque en fichero
            cout << "Extrayendo bloque número " << to_string(block_number) << "..." << endl;

            bTools.createBinaryFile(folderName + "/" + to_string(block_number) + " - " + fileName,
            string(block, block_size));

            block_number++;

          } // while

          // Guardamos el footer del fichero
          uint32_t pointer_beg_footer = pointer_beg_block+block_size;
          uint32_t footer_size = size - pointer_beg_footer;

          char footer[footer_size];
          inputFile.seekg(pointer_beg_footer, ios::beg);
          inputFile.read(footer, footer_size);
          fileName = "Footer";

          bTools.createBinaryFile(folderName + "/" + to_string(block_number) + " - " + fileName,
          string(footer, footer_size));

        } // if mkdir
      } // if inputFile is_open
  } // if arguments correct




return 0;
}
