#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  NOP,
  ACC,
  JMP,
} opcode_t;

size_t remove_newline(char* line) {
  size_t slen = strlen(line) - 1;
  if (*line && line[slen] == '\n') {
    line[slen] = '\0';
  }
  return slen;
}

int run_program2(const opcode_t* ops,
                 const int* nums,
                 int* hits,
                 int* accumulator) {
  memset(hits, 0, 633 * sizeof(int));
  *accumulator = 0;
  int position = 0;
  while (1) {
    opcode_t op = ops[position];
    int num = nums[position];
    int nhits = hits[position];
    if (position >= 633) {
      return 1;
    }
    else if (nhits == 1) {
      return 0;
    }
    else {
      hits[position] += 1;
      if      (op == NOP) position += 1;
      else if (op == ACC) {
        *accumulator += num;
        position += 1;
      }
      else if (op == JMP) position += num;
    }
  }
  return 0;
}

int main() {
  FILE* f;
  f = fopen("data/day8.dat", "r");
  size_t n = 16;
  char* line = (char*)malloc(n * sizeof(char));
  size_t itr = 0;

  opcode_t ops[633] = {0};
  int nums[633] = {0};
  int hits[633] = {0};

  while (getline(&line, &n, f) != -1) {
    remove_newline(line);
    char instruction[8];
    int num;
    opcode_t op;
    sscanf(line, "%s %d", instruction, &num);
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
    ops[itr] = op;
    nums[itr] = num;
    hits[itr] = 0;
    itr++;
  }

  int accumulator = 0;
  run_program2(ops, nums, hits, &accumulator);
  printf("Part 1: %d\n", accumulator);

  for (int i = 0; i < 633; ++i) {
    if (ops[i] == JMP) {
      ops[i] = NOP;
      int rp = run_program2(ops, nums, hits, &accumulator);
      if (rp == 1) printf("Part 2: %d\n", accumulator);
      ops[i] = JMP;
    }
    else if (ops[i] == NOP) {
      ops[i] = JMP;
      int rp = run_program2(ops, nums, hits, &accumulator);
      if (rp == 1) printf("Part 2: %d\n", accumulator);
      ops[i] = NOP;
    }
  }

  fclose(f);
  free(line);
  return 0;
}
