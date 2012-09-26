#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <limits>
#include <algorithm>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cassert>
using namespace std;

template <typename T>
ostream& print(const T& a, bool eol = true) {
  copy(a.begin(), a.end(), ostream_iterator<typename T::value_type>(cerr, " "));
  if (eol) cerr << endl;
  return cerr;
}

ostream& print(const vector<vector<int> >& a, int w = 2) {
  for (int i = 0; i < (int)a.size(); ++i) {
    cerr << setw(2) << i << ": ";
    print(a[i]);
  }
  return cerr;
}

void solve(istream& is, ostream& os) {
  int Y, X;
  is >> Y >> X >> ws;
  vector<string> f(Y);
  for (int i = 0; i < Y; ++i) {
    getline(is, f[i]);
  }
  int r = 0;
  vector<int> c(Y + 1, 0);
  for (int x = X - 1; x >= 0; --x) {
    for (int y = 0; y < Y; ++y)
      c[y] = f[y][x] == '1' ? c[y] + 1 : 0;
    stack<pair<int, int> > s;
    int w = 0;
    for (int y = 0; y <= Y; ++y) {
      if (c[y] > w) {
        s.push(make_pair(y, w));
        w = c[y];
      }
      if (c[y] < w) {
        int y0, w0;
        do {
          assert(!s.empty());
          y0 = s.top().first;
          w0 = s.top().second;
          s.pop();
          if (w * (y - y0) > r)
            r = w * (y - y0);
          w = w0;
        } while (c[y] < w);
        w = c[y];
        if (w != 0)
          s.push(make_pair(y0, w0));
      }
    }
  }

  os << r << endl;
}

const char* liner = "--------";

void run(int i, const char* input, const char* output) {
  stringstream is(input);
  stringstream os;
  solve(is, os);
  if (os.str() != output) {
    cerr << "Case #" << i << ": FAILED" << endl;
    cerr << liner << "EXPECTED" << liner << endl << output;
    cerr << liner << "-ACTUAL-" << liner << endl << os.str() 
         << liner << liner << liner << endl;
  } else 
    cerr << "Case #" << i << " OK" << endl;
}

typedef vector< pair<const char*, const char*> > Cases;
void runner(Cases& cases, int i) {
  if (i != -1) run(i, cases[i].first, cases[i].second);
  else {
    for (int i = 0; i < (int)cases.size(); ++i)
      run(i, cases[i].first, cases[i].second);
  }
}

Cases cases;

namespace {
// Needed for stupid Sun compiler.
pair<const char*, const char*> make_pair(const char* a, const char* b) {
  return std::make_pair(a, b);
}
}

int main(int argc, char* argv[]) {
#ifdef TESTING_

cases.push_back(make_pair(
"3 3\n"
"111\n"
"110\n"
"101\n"
,
"4\n"
));

cases.push_back(make_pair(
"5 10\n"
"1011011111\n"
"0111111110\n"
"1111111111\n"
"1011111111\n"
"1101110111\n"
,
"21\n"
));

cases.push_back(make_pair(
"3 3\n"
"111\n"
"111\n"
"111\n"
,
"9\n"
));

cases.push_back(make_pair(
"7 7\n"
"1101101\n"
"1111110\n"
"1010100\n"
"0011100\n"
"1000010\n"
"1100111\n"
"1001110\n"
,
"6\n"
));

cases.push_back(make_pair(
"7 7\n"
"1101101\n"
"1111110\n"
"1011100\n"
"0011100\n"
"1000010\n"
"1100111\n"
"1001110\n"
,
"9\n"
));

cases.push_back(make_pair(
"2 2\n"
"00\n"
"10\n"
,
"1\n"
));

cases.push_back(make_pair(
"2 2\n"
"00\n"
"00\n"
,
"0\n"
));

cases.push_back(make_pair(
"2 2\n"
"11\n"
"11\n"
,
"4\n"
));

cases.push_back(make_pair(
"1 1\n"
"1\n"
,
"1\n"
));

cases.push_back(make_pair(
"1 1\n"
"0\n"
,
"0\n"
));

cases.push_back(make_pair(
"4 4\n"
"1111\n"
"1011\n"
"1111\n"
"1111\n"
,
"8\n"
));

cases.push_back(make_pair(
"4 4\n"
"1111\n"
"1111\n"
"1111\n"
"1111\n"
,
"16\n"
));

cases.push_back(make_pair(
"2 2\n"
"00\n"
"01\n"
,
"1\n"
));
cases.push_back(make_pair(
"2 2\n"
"01\n"
"00\n"
,
"1\n"
));

cases.push_back(make_pair(
"2 2\n"
"10\n"
"00\n"
,
"1\n"
));
cases.push_back(make_pair(
"2 2\n"
"01\n"
"10\n"
,
"1\n"
));

cases.push_back(make_pair(
"4 4\n"
"1011\n"
"1111\n"
"1111\n"
"1111\n"
,
"12\n"
));

runner(cases, -1);
getchar();

#else

ifstream is("INPUT.TXT");
ofstream os("OUTPUT.TXT");
solve(is, os);

#endif

}