#include <stdio.h>

#define N 200

int main(int argc, char *argv[]) {

  /* place to store ints */
  int all[N] = {0};

  /* read all the ints */
  FILE* f;
  int value;
  f = fopen("data/day1.dat", "r");
  int i = 0;
  while (fscanf(f, "%d", &value) == 1) {
    all[i] = value;
    i++;
  }
  fclose(f);

  /* brute force find the first answer */
  int answer1 = 0;
  for (int j = 0; j < N; ++j) {
    for (int k = 1; k < N; ++k) {
      if ((all[j] + all[k]) == 2020) {
        answer1 = all[j] * all[k];
        break;
      }
    }
  }

  /* brute force find the answer to part 2 */
  int answer2 = 0;
  for (int j = 0; j < N; ++j) {
    for (int k = 1; k < N; ++k) {
      for (int m = 2; m < N; ++m) {
        if ((all[j] + all[k] + all[m]) == 2020) {
          answer2 = all[j] * all[k] * all[m];
          break;
        }
      }
    }
  }

  /* report the answers */
  printf("%d\n", answer1);
  printf("%d\n", answer2);
  return 0;
}
