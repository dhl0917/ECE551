#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void breaker(FILE * f) {
  int c;
  int i;
  int freq[26] = {0};
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      i = c - 'a';
      freq[i] += 1;
    }
  }
  int max = 0;
  int maxindex = 0;
  for (int j = 0; j < 26; j++) {
    if (freq[j] > max) {
      maxindex = j;
      max = freq[i];
    }
  }
  int key = 0;
  key = 'a' + maxindex - 'e';
  if (key < 0) {
    key += 26;
  }
  fprintf(stdout, "%d\n", key);
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Wrong amount of Arguments.");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  breaker(f);
  if (fclose(f) != 0) {
    perror("Failed to close the FILE");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
