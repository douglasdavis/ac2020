#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct entry_t {
  char* instruction;
  int num;
  int hits;
} entry_t;

size_t remove_newline(char* line) {
  size_t slen = strlen(line) - 1;
  if (*line && line[slen] == '\n') {
    line[slen] = '\0';
  }
  return slen;
}

void print_all_entries(struct entry_t* entries[]) {
  for (int i = 0; i < 633; ++i) {
    printf("%d %s\n", entries[i]->num, entries[i]->instruction);
  }
}

int main() {
  FILE* f;
  f = fopen("data/day8.dat", "r");
  size_t n = 16;
  char* line = (char*)malloc(n * sizeof(char));

  struct entry_t* entries[633];
  size_t itr = 0;
  while (getline(&line, &n, f) != -1) {
    remove_newline(line);
    char instruction[8];
    int num;
    sscanf(line, "%s %d", instruction, &num);
    entries[itr] = malloc(sizeof(struct entry_t));
    struct entry_t* (*p)[] = &entries;
    (*p)[itr]->instruction = (char*)malloc(8 * sizeof(char));
    strcpy((*p)[itr]->instruction, instruction);
    (*p)[itr]->num = num;
    (*p)[itr]->hits = 0;
    itr++;
  }

  int accumulator = 0;
  int second_hit = 0;
  int position = 0;
  while (second_hit == 0) {
    struct entry_t* (*p)[] = &entries;
    const char* instruction = (*p)[position]->instruction;
    int num = (*p)[position]->num;
    int hits = (*p)[position]->hits;
    printf("%s, %d, %d, %d\n", instruction, num, hits, accumulator);

    if (hits == 1) {
      puts("Stopping");
      second_hit = 1;
    }
    else {
      (*p)[position]->hits = hits + 1;
      if (strcmp(instruction, "nop") == 0) { /* the same */
        position += 1;
      }
      else if (strcmp(instruction, "acc") == 0) { /* accumulate */
        accumulator += num;
        position += 1;
      }
      else if (strcmp(instruction, "jmp") == 0) { /* jump */
        position += num;
      }
      else {
        puts("BAD");
      }
    }
  }

  printf("Accumulator: %d\n", accumulator);

  /* clean up memory */
  for (int i = 0; i < 633; ++i) {
    struct entry_t *(*p)[] = &entries;
    free((*p)[i]->instruction);
    free((*p)[i]);
  }

  fclose(f);
  free(line);
  return 0;
}
