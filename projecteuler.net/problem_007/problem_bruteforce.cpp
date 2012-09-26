#include <vector>
#include <iostream>
#include <cmath>

int n = 10001;
int N = n * n;

int main() {
  std::vector<bool> p(N, true);
  int l = std::sqrt((double)N) + 1;
  p[0] = p[1] = false;
  for (int i = 2; i <= l; ++i)
    if (p[i])
      for (int j = i * i; j <= N; j += i)
        p[j] = false;
  int c = 0;
  for (int i = 0; i < p.size(); ++i)
    if (p[i]) {
      c += 1;
      if (c == n) {
        std::cout << i << std::endl;
        return 0;
      }
    }
  std::cout << "Not found" << std::endl;
  return 0;
}

