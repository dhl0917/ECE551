#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    char * line = NULL;
    size_t size = 0;
    char ** ptr = NULL;
    //malloc(sizeof(*ptr));
    int count = 0;
    //    mystr = malloc(*mystr);
    while (getline(&line, &size, stdin) >= 0) {
      ptr = realloc(ptr, (count + 1) * sizeof(*ptr));
      ptr[count] = line;
      line = NULL;
      count += 1;
    }
    free(line);
    sortData(ptr, count);
    for (int j = 0; j < count; j++) {
      fprintf(stdout, "%s", ptr[j]);
      free(ptr[j]);
    }
    free(ptr);
  }
  else {
    for (int x = 1; x < argc; x++) {
      FILE * f = fopen(argv[x], "r");
      if (f == NULL) {
        fprintf(stderr, "Open %d file error", x);
        return EXIT_FAILURE;
      }
      char * line = NULL;
      size_t size = 0;
      char ** ptr = NULL;
      //malloc(sizeof(*ptr));
      int count = 0;
      //    mystr = malloc(*mystr);
      while (getline(&line, &size, f) >= 0) {
        ptr = realloc(ptr, (count + 1) * sizeof(*ptr));
        ptr[count] = line;
        line = NULL;
        count += 1;
      }
      free(line);
      sortData(ptr, count);
      for (int j = 0; j < count; j++) {
        fprintf(stdout, "%s", ptr[j]);
        free(ptr[j]);
      }
      free(ptr);
      fclose(f);
    }
  }
  return EXIT_SUCCESS;
}
