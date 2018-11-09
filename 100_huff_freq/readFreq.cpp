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
  if (!myFile) {
    std::cerr << "Open error\n";
    exit(EXIT_FAILURE);
  }

  char c;

  while ((c = std::getc(myFile)) != EOF) {
    int index = c;
    array[index] += 1;
  }
  array[256] = 1;
  fclose(myFile);

  return array;
}
