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
  memset(array, 0, 257 * sizeof(*array));
  std::ifstream myFile(fname);
  if (!myFile) {
    std::cerr << "Open file error\n";
    exit(EXIT_FAILURE);
  }

  char c;
  // FILE * f;
  //  f = fopen(fname, "r");
  while (myFile.get(c)) {
    // while (c = fgetc(f)) {
    int index = c;
    array[index] += 1;
  }
  array[256] = 1;
  myFile.close();
  return array;
}
