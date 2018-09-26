#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int rotate(FILE * f, char main[10][12]) {
  char matrix[10][12];
  for (int i = 0; i < 10; i++) {
    if (fgets(matrix[i], 12, f) != NULL) {
      if (strchr(matrix[i], '\n') == NULL) {
        fprintf(stderr, "The line is too long!\n");
        return 1;
      }
    }
  }
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      main[i][j] = matrix[9 - j][i];
    }
    main[i][10] = '\n';
    main[i][11] = '\0';
  }
  return 0;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "WRONG AMOUNT OF ARGUMENTS!\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file.\n");
    return EXIT_FAILURE;
  }
  char matrix[10][12];
  if (rotate(f, matrix)) {
    EXIT_FAILURE;
  }
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 12; j++) {
      fprintf(stdout, "%c", matrix[i][j]);
    }
  }
  EXIT_SUCCESS;
}
