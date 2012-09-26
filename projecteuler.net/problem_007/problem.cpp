#include <vector>
#include <iostream>
#include <cmath>

int n = 10001;

bool is_prime(int n) {
  if (n == 1) return false;
  else if (n < 4) return false;
  else if (n % 2 == 0) return false;
  else if (n < 9) return false;
  else if (n % 3 == 0) return false;
  else {
    int r = std::sqrt(static_cast<double>(n));
    int f = 5;
    while (f <= r) {
      if (n % f == 0) return false;
      if (n % (f + 2) == 0) return false;
      f += 6;
    }
    return true;
  }
}

int main() {
  int c = 1;
  int i = 1;
  do {
    i += 2;
    if (is_prime(i))
      c += 1;
  } while (c < n);
  std::cout << i << std::endl;
  return 0;
}

