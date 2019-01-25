#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char * getName(const char * name) {
  int len = strlen(name);
  char * myName = malloc((len + 1) * sizeof(*myName));
  strcpy(myName, name);
  return myName;
}
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * myCounts = malloc(sizeof(*myCounts));
  myCounts->size = 0;
  myCounts->pointerToArray = NULL;
  myCounts->unknownTimes = 0;
  return myCounts;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name != NULL) {
    for (int i = 0; i < c->size; i++) {
      if (!strcmp(c->pointerToArray[i].name, name)) {
        c->pointerToArray[i].times += 1;
        return;
      }
    }
    c->size += 1;
    c->pointerToArray = realloc(c->pointerToArray, c->size * sizeof(*c->pointerToArray));
    c->pointerToArray[c->size - 1].name = getName(name);
    c->pointerToArray[c->size - 1].times = 1;
  }
  else {
    c->unknownTimes += 1;
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (int i = 0; i < c->size; i++) {
    fprintf(outFile, "%s: %d\n", c->pointerToArray[i].name, c->pointerToArray[i].times);
  }
  if (c->unknownTimes > 0) {
    fprintf(outFile, "<unknown>: %d\n", c->unknownTimes);
  }
  fclose(outFile);
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (int i = 0; i < c->size; i++) {
    free(c->pointerToArray[i].name);
  }
  free(c->pointerToArray);
  free(c);
}
