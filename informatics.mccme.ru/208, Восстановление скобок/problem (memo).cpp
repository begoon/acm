#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
using namespace std;

int cache[81][81];

int f(const string& s, int i, int depth) {
  if (i >= s.length())
    return depth > 0 ? 0 : 1;
  if (cache[i][depth]) return cache[i][depth];
  char c = s[i];
  int r = 0;
  if (c == '(' || c == '?')
    r += f(s, i + 1, depth + 1);
  if (c == ')' || c == '?')
    if (depth > 0) 
      r += f(s, i + 1, depth - 1);
  cache[i][depth] = r;
  return r;
}

int main(int argc, char* argv[]) {
  string s; cin >> s;
  int sz = s.length();
  if (sz == 0 || (sz & 1)) {
    cout << 0 << endl;
    return 0;
  }
  memset(cache, 0, sizeof(cache));
  cout << f(s, 0, 0) << endl;
  return 0;
}
