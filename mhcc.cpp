/*
	A tool to dump and insert text from My Healthy Cooking Coach (NDS).
	Coded by @priverop
*/

#include <stdint.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include <iomanip>
#include <codecvt>
#include <string>
#include <locale>
#include <algorithm>
#include <stdexcept>
using namespace std;

// https://stackoverflow.com/questions/3381614/c-convert-string-to-hexadecimal-and-vice-versa

string hexToString(const std::string& hex){
  int len = hex.length();
  std::string newString;
  for(int i=0; i<len; i+=2)
  {
      string byte = hex.substr(i,2);
      char chr = (char) (int)strtol(byte.c_str(), nullptr, 16);
      newString.push_back(chr);
  }
  return newString;
}

string StringToHex(const string& s, bool upper_case)
{
    ostringstream ret;

    for (string::size_type i = 0; i < s.length(); ++i)
        ret << std::hex << std::setfill('0') << std::setw(2) << (upper_case ? std::uppercase : std::nouppercase) << (int)s[i];

    return ret.str();
}

string encoder16(const std::string& word){
  string word16;
  string word16_hex;
  string word_hex = StringToHex(word, true);
  for (int i = 2; i <= word_hex.size(); i+=4) {
    word_hex.insert(i, "00");
  }
  return hexToString(word_hex);
}

/*
   - "--d" Dump file into text
   - "--i" Insert into new file
*/

int main(int argc, char* argv[]){

  /*
    1 - Abrimos fichero
    2 - Pasamos a hex
    3 - Buscamos PREP
    4 - Guardamos cabecera
    5 - Guardamos longitud
    6 - Cogemos la palabra (longitud * 4bytes)
    7 - Mostramos por pantalla

    - Con el insert hello world.
    - Cuando funcione, se genera el fichero a partir del .txt
    - Necesitaré hacerlo OOS para generar lo del fichero again. Pero...
  */

  // 1 - Abrimos fichero
  bool debug = true;
  ifstream::pos_type size;
  char * memblock;
  ifstream file;
  string prep = "1200000001000000";
  vector<int> longitudes;
  vector<string> palabras;
  string fileName = argv[1];

  file.open(fileName, ios::in | ios::binary | ios::ate);

    if (file.is_open())
    {
      size = file.tellg();
      memblock = new char [size];
      file.seekg (0, ios::beg);
      file.read (memblock, size);

      // 2 - Pasamos a hex
      string full_string = string(memblock, size);
      string hex_string = StringToHex(string(memblock, size), true);

      // 3 - Buscamos el primer PREP
      size_t prep_beg_position = hex_string.find(prep);
      size_t prep_end_position = prep_beg_position + 4*4;

      // 4 - Guardamos cabecera
      string header_file = hex_string.substr(0, prep_beg_position);

      while(prep_end_position <= size * 2){
        if(debug)
          cout << "prep_end_position: " << prep_end_position <<endl;
        // 5 - Guardamos longitud
        stringstream aux_stream;
        int long_word = 0;
        if(debug)
          cout << "longitud hex:" << hex_string.substr(prep_end_position, 2) << endl;
        aux_stream << hex_string.substr(prep_end_position, 2);
        aux_stream >> hex >> long_word;
        if(debug)
          cout << "longitud palabra: " << long_word <<endl;
        longitudes.push_back(long_word);

        // 6 - Cogemos la palabra (longitud * 4bytes)
        size_t word_position = prep_end_position + 8;
        if(debug)
          cout << "posicion_inicio_palabra: " <<  word_position << endl;
        string word_hex = hex_string.substr(word_position, long_word * 4);
        string word = hexToString(word_hex);
        if(debug)
          cout << "palabra: " << word << endl;
        palabras.push_back(word);

        // Actualizamos con la posición del final de la palabra
        prep_end_position = word_position + (long_word * 4);
        if(debug)
          cout << "posicion_final_palabra: " << prep_end_position << endl;
        // Avanzamos el PREP
        prep_end_position = prep_end_position + 4 * 4;
        if(debug)
          cout << "=====" << endl;
      }

      if(debug){
        cout << "=== END ===" << endl;

        vector<int>::iterator itLongitudes;
        for(itLongitudes = longitudes.begin(); itLongitudes != longitudes.end(); itLongitudes++){
          cout << *itLongitudes << endl;
        }
      }

      string option = argv[2];
      if(option.compare("--d") == 0){
        std::ofstream outfile (fileName + ".txt");
        vector<string>::iterator itPalabras;
        for(itPalabras = palabras.begin(); itPalabras != palabras.end(); itPalabras++){
          cout << *itPalabras << endl;
          outfile << *itPalabras << endl;
        }
        outfile.close();
      }

      if(option.compare("--i") == 0){
        string txtName = argv[3];
        vector<string> translated_words;
        vector<int> long_transd_words;

        // Leemos el fichero y lo volcamos a translated_words
        // Volcamos en long_transd_words la longitud de cada palabra
        ifstream textFile(txtName);
        string translated_word;
        while(getline(textFile, translated_word)){
          if(translated_word.size() > 0)
            translated_words.push_back(translated_word);
            long_transd_words.push_back(translated_word.size());
        }
        textFile.close();

        if(debug){
          vector<int>::iterator itLongitudes;
          for(itLongitudes = long_transd_words.begin(); itLongitudes != long_transd_words.end(); itLongitudes++){
            cout << *itLongitudes << endl;
          }

          vector<string>::iterator itPalabras;
          for(itPalabras = translated_words.begin(); itPalabras != translated_words.end(); itPalabras++){
            cout << *itPalabras << endl;
          }
        }

        // Creamos el fichero nuevo
        ofstream ofile(fileName + "_translated", ios::binary | ios::out);

        cout << "========" << endl;
        cout << "Fichero " << fileName + "_translated " << "creado con exito" << endl;
        ofile << hexToString(header_file);

        // Recorremos el vector de palabras
        vector<string>::iterator itPalabras;
        int index = 0;
        for(itPalabras = translated_words.begin(); itPalabras != translated_words.end(); itPalabras++){
          ofile << hexToString(prep);
          ofile << hexToString(StringToHex((char*)&long_transd_words[index], true));
          ofile << hexToString("000000");
          ofile << encoder16(translated_words[index]);

          index++;
        }

      }

      file.close();
     }

  return 0;
}
