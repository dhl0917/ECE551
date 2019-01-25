#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  int len = strlen(inputName);
  char * outputName = malloc((len + 7 + 1) * sizeof(*outputName));
  for (int i = 0; i < len + 1; i++) {
    outputName[i] = inputName[i];
  }

  outputName = strcat(outputName, ".counts");
  return outputName;
}
