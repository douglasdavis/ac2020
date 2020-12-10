#include <ctype.h>
#include <string.h>
#include <stdio.h>

void clear_table(int* a) {
  memset(a, 0, sizeof(int) * 128);
}

int main() {
  FILE* f;
  f = fopen("data/day6.dat", "r");
  int lo = 97;
  int hi = 122;
  char input_line[32];
  int table[128] = {0};
  int sum = 0;
  while(fgets(input_line, sizeof(input_line), f)) {
    const char* l = input_line;
    if (strcmp("\n", l) == 0) {
      clear_table(table);
    }
    else {
      for (int i = 0; i < 32; ++i) {
        int ascii_val = (int)(input_line[i]);
        if (ascii_val >= lo && ascii_val <= hi) {
          table[ascii_val] = 1;
        }
      }
      for (int i = lo; i <= hi; ++i) {
        sum += table[i];
        printf("%d ", table[i]);
      }
      printf("\n");
    }
  }
  printf("%d\n", sum);
  fclose(f);
  return 0;
}
