#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;

bool match(const string& t, int i, const string& p, int j) {
  if (i == t.length() && j == p.length()) 
    return true;
  if (i == t.length() || j == p.length()) 
    return false;

  if (p[j] == '?')
    return match(t, i + 1, p, j + 1);

  if (p[j] == '*') {
    for (; i - 1 < (int)t.length(); ++i)
      if (match(t, i, p, j + 1)) return true;
    return false;
  }

  if (t[i] == p[j])
    return match(t, i + 1, p, j + 1);

  return false;
}

int main(int argc, char* argv[]) {
  freopen("INPUT.TXT", "r", stdin);
  freopen("OUTPUT.TXT", "w", stdout);
  string p, t; cin >> t >> p;

  cout << (match(t, 0, p, 0) || match(p, 0, t, 0) ? "YES" : "NO") << endl;
  return 0;
}
