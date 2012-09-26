#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>

using namespace std;

struct mask_t {
  const char* mask;
  int score;
} masks[] = {
  { "aa", 2 },
  { "aba", 2 },
  { "aab", 2 },
  { "abb", 2 },
  { "aaa", 3 },
  { "abac", 2 },
  { "baca", 2 },
  { "abab", 3 },
  { "aabb", 3 },
  { "abba", 4 },
  { "baaa", 3 },
  { "abaa", 3 },
  { "aaba", 3 },
  { "aaab", 3 },
  { "aaaa", 5 },
  { 0 },
};

int match(const string& s) {
  int max_score = 0;
  for (int i = 0; masks[i].score != 0; ++i) {
    int sz = strlen(masks[i].mask);
    if (sz != s.length()) continue;
    int a = 0, b = 0, c = 0;
    int score = masks[i].score;
    for (int j = 0; j < sz; ++j) {
      char ch = masks[i].mask[j];
      if (ch == 'a') {
        if (a == 0)
          a = s[j];
        else {
          if (s[j] != a)
            score = 0;
        }
      } else if (ch == 'b') {
        if (b == 0)
          b = s[j];
        else {
          if (s[j] != b)
            score = 0;
        }
      } else {
        if (c == 0)
          c = s[j];
        else {
          if (s[j] != c)
            score = 0;
        }
      }
    }
    if (score > max_score)
      max_score = score;
  }
  return max_score; 
}

int best = 0;

void doit(const string& s, int current, int i) {
  if (i == s.length()) {
    if (current > best) {
      best = current;
      return;
    }
  }

  for (int t = 2; t <= 4; ++t) {
    if (i + t > s.length()) continue;
    int v = match(s.substr(i, t));
    // cout << s.substr(i, t) << " " << v << endl;
    doit(s, current + v, i + t);
  }
}

int main(int argc, char* argv[]) {
  if (argc == 1) {
    freopen("INPUT.TXT", "r", stdin);
    freopen("OUTPUT.TXT", "w", stdout);
  }
  string s; cin >> s;
  doit(s, 0, 0);
  cout << best << endl;
  return 0;
}

