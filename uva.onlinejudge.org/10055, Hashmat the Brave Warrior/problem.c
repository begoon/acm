#include <stdio.h>

int main(int argc, char* argv[]) {
  unsigned long long a, b, c;
  while (1) {
    if (scanf("%lu %lu", &a, &b) != 2) break;
    c = a > b ? a - b : b - a;
    printf("%lu\n", c);
  }
  return 0;
}

