#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  int len = strlen(inputName);
  char * outputName = malloc((len + 7 + 1) * sizeof(*outputName));
  for (int i = 0; i < len; i++) {
    outputName[i] = inputName[i];
  }

  return strcat(outputName, ".counts\0");
}
