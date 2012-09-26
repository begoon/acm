#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>
#include <limits>
#include <numeric>
#include <cstdlib>

int N, M;
std::vector<int> v;
int max_amount = -1;
const int big = std::numeric_limits<int>::max();
int min_count = big;

int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }

void search(int offset, int amount, int count) {
  if (amount == N) min_count = min(min_count, count); 
  max_amount = max(max_amount, amount);
  if (offset >= M) return;
  for (int i = 0; i < 3; ++i) 
    search(offset + 1, amount + i * v[offset], count + i);
}

int main(int argc, char* argv[]) {
  freopen("INPUT.TXT", "r", stdin);
  freopen("OUTPUT.TXT", "w", stdout);
  std::cin >> N >> M;
  v.resize(M, 0); 
  for (int i = 0; i < M; ++i) std::cin >> v[i];

  if (std::accumulate(v.begin(), v.end(), 0) * 2 < N) {
    std::cout << -1 << std::endl;
    return 0;
  }

  std::sort(v.begin(), v.end(), std::greater<int>());

  search(0, 0, 0);
  std::cout << (min_count == big ? 0 : min_count) << std::endl;

  return 0;
}

