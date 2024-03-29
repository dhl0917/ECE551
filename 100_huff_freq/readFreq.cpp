#include "readFreq.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  uint64_t * array = new uint64_t[257];
  // memset(array, 0, 257 * sizeof(*array));
  for (int i = 0; i < 257; i++) {
    array[i] = 0;
  }
  //std::ifstream myFile;
  //myFile.open(fname);
  FILE * myFile;
  myFile = fopen(fname, "r");
  if (myFile == NULL) {
    std::cerr << "Open error\n";
    exit(EXIT_FAILURE);
  }

  int c;

  while ((c = fgetc(myFile)) != EOF) {
    //    unsigned a = c;
    // std::cout << a << "\n";
    /*
    if (c < 0 || (int)c > 256) {
      fclose(myFile);
      delete[] array;
      std::cerr << "Invalid input";
      exit(EXIT_FAILURE);
    }
    */

    // int index = (int)(unsigned)c;
    int index = c;
    /*
    if (index < 0 || index > 255) {
      fclose(myFile);
      delete[] array;
      std::cerr << "Invalid input\n";
      exit(EXIT_FAILURE);
    }
    */
    if (index >= 0 && index <= 255) {
      array[index] += 1;
    }
  }
  if (c == EOF) {
    array[256] += 1;
  }
  fclose(myFile);

  return array;
}
