#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <numeric>
#include <limits>
#include <algorithm>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cassert>
#ifdef _DEBUG
#include <windows.h>
#endif
using namespace std;

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

const double EPS = 1e-9;

template <typename T>
T max(T a, T b, T c) {
  return max(a, max(b, c));
}

int main(int argc, char* argv[]) {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int H, W, N;
  scanf("%d %d %d", &H, &W, &N);
  int dp[100][100];
  memset(dp, 0, sizeof(dp));
  for (int h = 0; h < H; ++h) {
    for (int w = 0; w < W; ++w) {
      scanf("%d", &dp[h][w]);
      if (h > 0) dp[h][w] += dp[h - 1][w];
      if (w > 0) dp[h][w] += dp[h][w - 1];
      if (h > 0 && w > 0) dp[h][w] -= dp[h - 1][w - 1];
    }
  }
  for (int n = 0; n < N; ++n) {
    int y1, x1, y2, x2;
    scanf("%d %d %d %d", &y1, &x1, &y2, &x2);
    if (y1 > y2) swap(y1, y2);
    if (x1 > x2) swap(x1, x2);
    --y1; --x1; --y2; --x2;
    int v = dp[y2][x2];
    if (x1 > 0)
      v -= dp[y2][x1 - 1];
    if (y1 > 0)
      v -= dp[y1 - 1][x2];
    if (x1 > 0 && y1 > 0)
      v += dp[y1 - 1][x1 - 1];
    printf("%d\n", v);
  }
  return 0;
}
