#include <stdio.h>
#include <string.h>
#include <ctype.h>

int check_if_good(const char* line) {
  const char* a[7] = {
    "byr:",
    "iyr:",
    "eyr:",
    "hgt:",
    "hcl:",
    "ecl:",
    "pid:",
  };
  for (size_t i = 0; i < 7; ++i) {
    if (!(strstr(line, a[i]))) {
      return 0;
    }
  }
  return 1;
}

int main(int argc, char *argv[]) {
  FILE* f;
  f = fopen("day4.dat", "r");
  char* line;
  char input_line[128];
  int n_good = 0;
  char whole_passport[512] = {0};
  while (fgets(input_line, 128, f)) {
    line = input_line;
    if (strcmp(line, "\n") == 0) {
      /* if we hit a blank line check what the passport we have
         contructed */
      n_good += check_if_good(whole_passport);

      /* then reset for next batch of lines */
      memset(whole_passport, 0, sizeof(whole_passport));
    }
    else {
      line[strcspn(line, "\n")] = 0;
      if (!(strcmp(whole_passport, "") == 0)) {
        strcat(whole_passport, " ");
      }
      strcat(whole_passport, line);
    }
  }
  /* last line */
  n_good += check_if_good(whole_passport);
  printf("%d\n", n_good);
  fclose(f);
  return 0;
}
