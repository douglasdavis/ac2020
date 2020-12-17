#include <stdlib.h>
#include <stdio.h>

#define N 31
#define TREE  '#'

int main(int argc, char *argv[]) {
  FILE* f;
  f = fopen("data/day3.dat", "r");
  int irow = 0;
  int ntree = 0;
  char in_row[N];
  int overall_cell = 0;
  int current_cell = 0;

  int n_right = atoi(argv[1]);
  printf("%d\n", n_right);

  while (fscanf(f, "%s", in_row) == 1) {
    irow++;
    /* uncomment for part 2 */
    /* if (irow%2 != 0) { */
    if (1) {
      if (overall_cell > 30) {
        current_cell = (overall_cell % 31);
      }
      else {
        current_cell = overall_cell;
      }
      char* row = in_row;
      if (row[current_cell] == TREE) {
        ntree++;
      }
      overall_cell += n_right;
    }
  }

  printf("%d\n", ntree);

  fclose(f);
  return 0;
}
