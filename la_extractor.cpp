#include "HexTools.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char* argv[]){

  HexTools tools;

  if(argc < 2){
    cout << "Not enough arguments." << endl;
    cout << "USAGE: main fileToExtract" << endl;
  }
  else{
    string inputFileName = argv[1];
    ifstream inputFile;
    ifstream::pos_type size;
    char * memblock;

    inputFile.open(inputFileName, ios::in | ios::binary | ios::ate);

      if (inputFile.is_open())
      {
        size = inputFile.tellg();
        memblock = new char [size];

        unsigned int block_number = 0;
        uint32_t offset = 0x20; // Nos saltamos los 32bytes de la cabecera

        // Guardamos los primeros 4bytes tras la tabla de punteros para tomarlo como fin de bucle
        uint32_t first_pointer;
        inputFile.seekg(offset, ios::beg);
        inputFile.read (reinterpret_cast<char *>(&first_pointer), sizeof(first_pointer));

        uint32_t end_table;
        inputFile.seekg(first_pointer, ios::beg);
        inputFile.read (reinterpret_cast<char *>(&end_table), sizeof(end_table));

        const string folderName = "./extract";

        if (mkdir(folderName.c_str(), S_IRWXU | S_IRWXG | S_IRWXO) != 0)
        {
          cout << "Error creating extract folder" << endl;
          cout << "Please delete the folder" << endl;
        }
        else{
          cout << "== LUMINOUS ARC EXTRACTOR by Nex ==" << endl << endl;
          cout << "Iniciando la extracción..." << endl << endl;

          while(offset != first_pointer){

            // Almacenamos los 8 bytes del puntero del inicio del bloque
            uint32_t pointer_beg_block;
            inputFile.seekg(offset, ios::beg);
            inputFile.read (reinterpret_cast<char *>(&pointer_beg_block), sizeof(pointer_beg_block));

            offset += sizeof(pointer_beg_block);

            // Almacenamos los 8 bytes del tamaño de bloque
            uint32_t block_size;
            inputFile.seekg(offset, ios::beg);
            inputFile.read (reinterpret_cast<char *>(&block_size), sizeof(block_size));

            offset += sizeof(block_size);

            // Almacenamos el bloque
            char * block = new char [block_size];
            inputFile.seekg(pointer_beg_block, ios::beg);
            inputFile.read (block, block_size);
            // Nombre del archivo
            string fileName = string(block, sizeof(uint32_t));

            // Guardamos bloque en fichero
            std::ofstream outfile (folderName + "/" + fileName + to_string(block_number));
            outfile << string(block, block_size);
            cout << "Extrayendo bloque número " << to_string(block_number) << "..." << endl;
            cout << fileName << to_string(block_number) << " creado correctamente." << endl << endl;
            outfile.close();

            block_number++;

          } // while
        } // if mkdir
      } // if inputFile is_open
  } // if arguments correct




return 0;
}
