#include <stdio.h>

int get_val(const char* linep,
            size_t start_idx,
            size_t end_idx,
            int lo,
            int hi,
            char up_char,
            char dn_char) {
  int val;
  int div;
  char c;
  for (int i = start_idx; i < end_idx; ++i) {
    c = linep[i];
    div = (hi - lo + 1) / 2;
    if (c == dn_char) {
      hi = hi - div;
    }
    else if (c == up_char) {
      lo = lo + div;
    }
  }
  if (linep[end_idx] == dn_char) {
    val = lo;
  }
  else if (linep[end_idx] == up_char) {
    val = hi;
  }
  return val;
}

int get_id(const char* linep) {
  int row = get_val(linep, 0, 6, 0, 127, 'B', 'F');
  int col = get_val(linep, 7, 9, 0, 7,   'R', 'L');
  return row * 8 + col;
}

int main() {
  FILE* f;
  f = fopen("day5.dat", "r");
  char line[16];
  int row;
  int col;
  int maxid = 0;
  int seatid;
  int seats[861] = {0};
  while (fscanf(f, "%s", line) == 1) {
    seatid = get_id(line);
    seats[seatid] = 1;
    if (seatid > maxid) {
      maxid = seatid;
    }
  }
  for (int i = 0; i < 861; ++i) {
    if (seats[i] != 1) {
      printf("%d ", i);
    }
  }
  printf("%d\n", maxid);
  fclose(f);
  return 0;
}
