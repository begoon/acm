#include <cstdlib>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <cassert>
using namespace std;

vector<int> dividers;
int N;

int cube(int x) { return x * x * x; }
int cube_root(int x) { return std::pow((double)x, 1.0/3) + 10E-9; }

int iterations = 0;

vector<int> cubes;
vector<int> roots;

int max_cube = -1;

void pre_calc_cubes() {
  int i = 1;  
  while (1) {
    int cube = i * i * i;
    if (cube > 2E9) break;
    cubes.push_back(cube);
    roots.push_back(i);
    max_cube = cube;
    i += 1;
  }
}

vector<vector<bool> > cache(10, vector<bool>(8000000, true));

bool divide(int n, int from) {
  assert(n >= 0);
  if (dividers.size() > 8) return false;
  if (n == 0) {
    for (int i = 0; i < dividers.size(); ++i) {
      if (i > 0) cout << " ";
      cout << dividers[i];
    }
    cout << endl;
    return true;
  }
  if (n < cache[0].size() && dividers.size() < cache.size()) {
    bool v = cache[dividers.size()][n];
    if (!v) {
      return false;
    }
  }  
  if (n > max_cube)
    // If 'n' is greater than the maximal cube we have, we simply
    // take the maximal cube.
    from = cubes.size() - 1;
  else {
    // Binary search for an element which is equal or greater than 'n'.
    // We search in the range from the beginning up to the last used cube.
    from = int(lower_bound(cubes.begin(), cubes.begin() + from + 1, n) - cubes.begin());
    assert(from < cubes.size());
    assert(cubes[from] >= n);
    if (cubes[from] > n) {
      from -= 1;
      assert(from >= 0);
    }
  }
  for (int i = from; i >= 0; --i) {
    iterations += 1;
    int r = n - cubes[i];
    assert(r >= 0);
    dividers.push_back(roots[i]);
    if (divide(r, from))
      return true;
    if (r < cache[0].size() && dividers.size() < cache.size())
      cache[dividers.size()][r] = false;
    dividers.pop_back();
  }
  return false;
}

int main(int argc, char* argv[]) {
  if (argc == 1) {
    freopen("INPUT.TXT", "r", stdin);
    freopen("OUTPUT.TXT", "w", stdout);
  }
  pre_calc_cubes();
  cin >> N;
  if (!divide(N, cubes.size() - 1)) 
    cout << "IMPOSSIBLE" << endl;
#if 0
  cout << "iterations = " << iterations << endl;
#endif
  return 0;
}
