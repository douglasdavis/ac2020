#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  NOP,
  ACC,
  JMP,
} opcode_t;

typedef struct entry_t {
  opcode_t op;
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

int run_program(struct entry_t* entries[], int* accumulator, int* terminated) {
  /* part 1 */
  *accumulator = 0;
  *terminated = 0;
  int second_hit = 0;
  int position = 0;
  while (second_hit == 0) {
    opcode_t op = entries[position]->op;
    int num = entries[position]->num;
    int hits = entries[position]->hits;
    if (position >= 633) {
      puts("TERMINATED");
      *terminated = 1;
      return 1;
    }
    else if (hits == 1) {
      second_hit = 1;
    }
    else {
      entries[position]->hits = hits + 1;
      if (op == NOP) {
        position += 1;
      }
      else if (op == ACC) {
        *accumulator += num;
        position += 1;
      }
      else if (op == JMP) {
        position += num;
      }
      else {
        puts("BAD");
      }
    }
  }
  return 0;
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
    opcode_t op;
    sscanf(line, "%s %d", instruction, &num);
    entries[itr] = malloc(sizeof(struct entry_t));
    switch(instruction[0]) {
    case 'n':
      op = NOP;
      break;
    case 'a':
      op = ACC;
      break;
    case 'j':
      op = JMP;
      break;
    default:
      exit(EXIT_FAILURE);
    }
    struct entry_t* (*p)[] = &entries;
    (*p)[itr]->op = op;
    (*p)[itr]->num = num;
    (*p)[itr]->hits = 0;
    itr++;
  }

  int accumulator = 0;
  int terminated = 0;

  run_program(entries, &accumulator, &terminated);
  printf("Part 1 Accumulator: %d\n", accumulator);

  /* clean up memory */
  for (int i = 0; i < 633; ++i) {
    struct entry_t *(*p)[] = &entries;
    free((*p)[i]);
  }

  fclose(f);
  free(line);
  return 0;
}
