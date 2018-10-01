#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ** ReadFileToArray(FILE * f, int * sz) {
  char * line = NULL;
  size_t size = 0;
  char ** ptr = NULL;
  int i = 0;
  while ((getline(&line, &size, f)) >= 0) {
    ptr = realloc(ptr, (i + 1) * sizeof(*ptr));
    ptr[i] = line;
    line = NULL;
    i++;
  }
  *sz = i;
  free(line);
  return ptr;
}
char * findKey(char * string) {
  int i = 0;
  while (string[i] != '=') {
    i++;
  }
  char * key = malloc((i + 1) * sizeof(*key));
  for (int j = 0; j < i; j++) {
    key[j] = string[j];
  }
  key[i] = '\0';
  return key;
}
char * findValue(char * string) {
  int i = 0;
  int Dots;
  int Ends;
  /*
  while (string[i] != '\0') {
     if (string[i] == '=') {
        Dots = i;
        break;
       }
        i++;
  }
  */
  while (string[i] != '=') {
    i++;
  }
  Dots = i;
  i = 0;
  while (string[i] != '\n') {
    i++;
  }
  Ends = i;
  char * value = malloc((Ends - Dots) * sizeof(*value));
  for (int j = 0; j < Ends - Dots - 1; j++) {
    value[j] = string[j + Dots + 1];
  }
  value[Ends - Dots - 1] = '\0';
  return value;
}

void addToArray(char ** array, kvarray_t * pointerToKV, int sz) {
  pointerToKV->size = sz;
  pointerToKV->pointer_kvarray = malloc(sz * sizeof(*pointerToKV->pointer_kvarray));
  for (int i = 0; i < sz; i++) {
    pointerToKV->pointer_kvarray[i].key = findKey(array[i]);
    pointerToKV->pointer_kvarray[i].value = findValue(array[i]);
  }
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  int size = 0;
  kvarray_t * pointerToKVarray = malloc(sizeof(*pointerToKVarray));
  if (f == NULL) {
    fprintf(stderr, "Counld not open the k/v file!\n");
    exit(EXIT_FAILURE);
  }
  char ** arrayForReading = ReadFileToArray(f, &size);
  addToArray(arrayForReading, pointerToKVarray, size);
  for (int k = 0; k < size; k++) {
    free(arrayForReading[k]);
  }
  free(arrayForReading);
  fclose(f);
  return pointerToKVarray;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  int sz = pairs->size;
  for (int i = 0; i < sz; i++) {
    free(pairs->pointer_kvarray[i].key);
    free(pairs->pointer_kvarray[i].value);
  }
  free(pairs->pointer_kvarray);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  int sz = pairs->size;
  for (int i = 0; i < sz; i++) {
    fprintf(stdout,
            "key = '%s' value = '%s'\n",
            pairs->pointer_kvarray[i].key,
            pairs->pointer_kvarray[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  int sz = pairs->size;
  for (int i = 0; i < sz; i++) {
    if (!strcmp(pairs->pointer_kvarray[i].key, key)) {
      return pairs->pointer_kvarray[i].value;
    }
  }
  return NULL;
}
