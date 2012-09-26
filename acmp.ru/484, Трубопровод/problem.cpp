#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int T = 40;

vector<int> fib(T + 1, 0);
vector<int> fsum(T + 1, 0);

int level(int n) {
  for (int i = 1; ; ++i) {
    if (fsum[i - 1] < n && n <= fsum[i])
      return i;
  }
}

string path(int n) {
  string p;
  for (int j = n; j >= 2;) {
    int l = level(j);
    if (j <= fsum[l - 1] + fib[l - 1]) {
      p += "l";
      j -= fsum[l - 3];
    } else {
      p += "r";
      j -= fsum[l - 1];
      if (j > 2)
        p += "u";
    }
    j -= 2;
  }
  return p;
}

int main() {
  std::ifstream is("INPUT.TXT");
  std::ofstream os("OUTPUT.TXT");
  int n; is >> n;

  fib[1] = 1;
  fib[2] = 2;
  for (int i = 3; i <= T; ++i)
    fib[i] = fib[i - 1] + fib[i - 2];
    
  for (int i = 1; i <= T; ++i)
    fsum[i] = fsum[i - 1] + fib[i];

  string p = path(n);

  vector<int> r(1, 1);

  int t = 1;
  for (int i = 0; i < p.length(); ++i) {
    int jump = p[i] == 'r' ? 1 : 0;
    int l = level(t);
    int next_level_start = fsum[l] + 1;
    int current_level_offset = t - (fsum[l - 1] + 1);
    for (int j = T; j >= 1; --j) {
      int f = fib[j];
      if (f <= current_level_offset) {
        jump += fib[j + 1];
        current_level_offset -= f;
      }
    }
    t = next_level_start + jump;
    r.push_back(t);
  }

  for (int i = r.size() - 1; i >= 0; --i) {
    os << r[i];
    if (i > 0) os << " ";
  }
  os << endl;

  return 0;
}
