#include <iostream>
#include <iomanip>
#include <iterator>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <algorithm>
#include <functional>
#include <cstring>
#include <cstdlib>
#include <cstring>

using namespace std;

int main(int argc, char* argv[]) {
  ifstream is("data.in");

  int T;
  is >> T;
  for (int t = 1; t <= T; ++t) {
    int N, M;
    is >> N >> M >> ws;
    set<string> v;
    int r = 0;
    for (int i = 0; i < N + M; ++i) {
      string s;
      getline(is, s);
      s += '/';
      for (int j = 1; j < s.length(); ++j)
        if (s[j] == '/') {
          string p = s.substr(0, j);
          if (i >= N)
            r += v.find(p) == v.end();
          v.insert(p);
        }
    }
    cout << "Case #" << t << ": " << r << endl;
  }

  return 0;
}
