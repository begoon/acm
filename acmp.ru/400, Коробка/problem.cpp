#include <iostream>
#include <vector>
#include <map>
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

struct hw { int h, w; };

void solve_bruteforce(istream& is, ostream& os) {
  vector<hw> v(6);
  for (int i = 0; i < v.size(); ++i) 
    is >> v[i].w >> v[i].h;

  // Use this array to generate all permutations of the glabs (6! iterations).
  vector<int> m(6);
  for (int i = 0; i < m.size(); ++i) 
    m[i] = i;

  do {
    vector<hw> p(6);
    for (int i = 0; i < p.size(); ++i)
      p[i] = v[m[i]];

    // This loop generates all possible swaps between height and weight 
    // for every slab (2^6 iterations for every outer loop).
    for (int i = 0; i < (1 << 6); ++i) {

      if ((p[0].w == p[1].w && p[0].w == p[2].w && p[0].w == p[3].w) &&
          (p[4].w == p[1].h && p[4].w == p[5].w && p[4].w == p[3].h) &&
          (p[0].h == p[4].h && p[0].h == p[5].h && p[0].h == p[2].h)) {
        os << "POSSIBLE" << endl;
        return;
      }

      swap(p[0].w, p[0].h);
      for (int j = 0; j < 5; ++j)
        if (i & (1 << j))
          swap(p[j].w, p[j].h);
    }
  } while (next_permutation(m.begin(), m.end()));

  os << "IMPOSSIBLE" << endl;
}

typedef pair<int, int> slab;

void solve(istream& is, ostream& os) {
  vector<slab> v(6);
  for (int i = 0; i < v.size(); ++i) {
    is >> v[i].first >> v[i].second;
    if (v[i].first > v[i].second)
      swap(v[i].first, v[i].second);
  }

  for (int i = 0; i < v.size(); ++i)
    for (int j = i + 1; j < v.size(); ++j)
      if (v[i] == v[j]) {
        v.erase(v.begin() + j);
        break;
      }

  assert(v.size() >= 3);
  if (v.size() > 3) {
    os << "IMPOSSIBLE" << endl;
    return;
  }

  sort(v.begin(), v.end());

  if (v[0].first == v[1].first && 
      v[0].second == v[2].first && 
      v[1].second == v[2].second)
    os << "POSSIBLE" << endl;
  else
    os << "IMPOSSIBLE" << endl;
}

const char* liner = "--------";
int problem;
int problem_filter;

void run(int line, const char* input, const char* output) {
  problem += 1;
  if (problem_filter != -1 && problem_filter != problem) return;

  stringstream is(input);
  stringstream os;
  solve(is, os);
  if (os.str() != output) {
    cerr << "Case #" << problem << ": FAILED (line " << line << ")" << endl;
#ifdef _DEBUG
    stringstream error;
    error << __FILE__ << "(" << line << "): error: test case " << problem << " FAILED" << endl;
    OutputDebugStringA(error.str().c_str());  
#endif
    cerr << liner << "EXPECTED" << liner << endl << output;
    cerr << liner << "-ACTUAL-" << liner << endl << os.str() 
         << liner << liner << liner << endl;
  } else 
    cerr << "Case #" << problem << " OK (line " << line << ")" << endl;
}

int main(int argc, char* argv[]) {
#ifdef TESTING_

problem = -1;
problem_filter = -1;

run(__LINE__,
"1345 2584\n"
"2584 683\n"
"2584 1345\n"
"683 1345\n"
"683 1345\n"
"2584 683\n"
,
"POSSIBLE\n"
);

run(__LINE__,
"1234 4567\n"
"1234 4567\n"
"4567 4321\n"
"4322 4567\n"
"4321 1234\n"
"4321 1234\n"
,
"IMPOSSIBLE\n"
);

#ifdef _DEBUG
getchar();
#endif

#else

ifstream is("INPUT.TXT");
ofstream os("OUTPUT.TXT");
// istream& is = cin;
// ostream& os = cout;

solve(is, os);

#endif

return 0;
}
