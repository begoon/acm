#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;

int N;
vector<string> f;
int r;

void flood(int x, int y) {
  if (f[y][x] != '.') return;
  if (f[y - 1][x] == '#') r += 1;
  if (f[y + 1][x] == '#') r += 1;
  if (f[y][x + 1] == '#') r += 1;
  if (f[y][x - 1] == '#') r += 1;
  f[y][x] = '*';
  flood(x - 1, y);
  flood(x + 1, y);
  flood(x, y + 1);
  flood(x, y - 1);
}

int main(int argc, char* argv[]) {
  freopen("INPUT.TXT", "r", stdin);
  freopen("OUTPUT.TXT", "w", stdout);
  cin >> N;
  f.resize(N + 2);
  f[0] = string(N + 2, '#');
  f[N + 1] = string(N + 2, '#');
  for (int i = 1; i < N + 1; ++i) {
    string s;
    cin >> s;
    f[i] = string("#") + s + "#";
  }
  // for (int i = 0; i < f.size(); ++i) cout << f[i] << endl;
  flood(1, 1);
  flood(N, N);
  r -= 4;
  cout << r * 25 << endl;
  return 0;
}

