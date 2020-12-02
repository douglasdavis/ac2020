#include <stdio.h>
#include <string.h>

typedef struct {
  int min;
  int max;
  char c;
  char* s;
} entry_t;

int is_valid_part_one(const entry_t* entry) {
  int n = 0;
  char* s = entry->s;
  for (size_t i = 0; i < strlen(s); ++i) {
    n += s[i] == entry->c;
  }
  return n >= entry->min && n <= entry->max;
}

int is_valid_part_two(const entry_t* entry) {
  char* s = entry->s;
  int t1 = s[entry->min - 1] == entry->c;
  int t2 = s[entry->max - 1] == entry->c;
  return (t1 + t2) == 1;
}

int main(int argc, char *argv[]) {
  int total_good1 = 0;
  int total_good2 = 0;
  FILE* f;
  f = fopen("day2.dat", "r");
  int i = 0;
  int min;
  int max;
  char c;
  char s[50];
  while (fscanf(f, "%d-%d %c: %s", &min, &max, &c, s) == 4) {
    entry_t entry;
    entry.min = min;
    entry.max = max;
    entry.c = c;
    entry.s = s;
    total_good1 += is_valid_part_one(&entry);
    total_good2 += is_valid_part_two(&entry);
  }
  fclose(f);
  printf("%d\n", total_good1);
  printf("%d\n", total_good2);
  return 0;
}
