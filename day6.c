#include <ctype.h>
#include <string.h>
#include <stdio.h>

void clear_things(char* b) {
  memset(b, 0, sizeof(char) * 256);
}

size_t count_em(const char* s, int n_people) {
  int table[256] = {0};
  size_t c = strlen(s);
  if (c < 1) return 0;
  for (size_t i = 0; i < c; ++i) {
    char ch = s[i];
    size_t ach = (size_t)ch;
    table[ach] += 1;
  }
  int thesum = 0;
  for (int j = 97; j < 123; ++j) {
    if (table[j] == n_people) {
      thesum += 1;
    }
  }
  return thesum;
}

int main() {
  FILE* f;
  f = fopen("data/day6.dat", "r");
  char input_line[64];
  char whole_thing[256];
  int sum = 0;
  int n_people = 0;
  while(fgets(input_line, sizeof(input_line), f)) {
    const char* l = input_line;
    if (strcmp("\n", l) == 0) {
      sum += count_em(whole_thing, n_people);
      clear_things(whole_thing);
      n_people = 0;
    }
    else {
      n_people += 1;
      strcat(whole_thing, strtok(input_line, "\n"));
    }
  }
  sum += count_em(whole_thing, n_people);
  printf("%d\n", sum);
  fclose(f);
  return 0;
}
