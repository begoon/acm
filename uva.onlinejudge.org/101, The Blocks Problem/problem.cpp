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

void solve(istream& is, ostream& os) {
  int n;
  is >> n;
  vector<vector<int> > q(n, vector<int>(1, 0));
  for (int i = 0; i < n; ++i) q[i][0] = i;
  while (true) {
    string cmd, subcmd;
    is >> cmd;
#if 0
    cout << cmd;
#endif
    if (cmd == "quit") break;
    int a, b;
    is >> a >> subcmd >> b;
#if 0
    cout << " " << a << " " << subcmd << " " << b << endl;
#endif
    if (a == b) continue;
    int a_stack = -1, a_pos = -1;
    for (int i = 0; i < n && a_stack == -1; ++i)
      for (int j = 0; j < q[i].size() && a_stack == -1; ++j)
        if (q[i][j] == a) {
          a_stack = i;
          a_pos = j;
        }
    assert(a_stack != -1);
    assert(a_pos != -1);
    int b_stack = -1, b_pos = -1;
    for (int i = 0; i < n && b_stack == -1; ++i)
      for (int j = 0; j < q[i].size() && b_stack == -1; ++j)
        if (q[i][j] == b) {
          b_stack = i;
          b_pos = j;
        }
    assert(b_stack != -1);
    assert(b_pos != -1);
    if (a_stack == b_stack) continue;
    if (cmd == "move" && subcmd == "onto") {
      for (int i = a_pos + 1; i < q[a_stack].size(); ) {
        int v = q[a_stack][i];
        q[v].push_back(v);
        q[a_stack].erase(q[a_stack].begin() + i);
      }
      for (int i = b_pos + 1; i < q[b_stack].size(); ) {
        int v = q[b_stack][i];
        q[v].push_back(v);
        q[b_stack].erase(q[b_stack].begin() + i);
      }
      q[b_stack].push_back(q[a_stack][a_pos]);
      q[a_stack].erase(q[a_stack].begin() + a_pos);
    }
    if (cmd == "move" && subcmd == "over") {
      for (int i = a_pos + 1; i < q[a_stack].size(); ) {
        int v = q[a_stack][i];
        q[v].push_back(v);
        q[a_stack].erase(q[a_stack].begin() + i);
      }
      q[b_stack].push_back(q[a_stack][a_pos]);
      q[a_stack].erase(q[a_stack].begin() + a_pos);
    }
    if (cmd == "pile" && subcmd == "onto") {
      for (int i = b_pos + 1; i < q[b_stack].size(); ) {
        int v = q[b_stack][i];
        q[v].push_back(v);
        q[b_stack].erase(q[b_stack].begin() + i);
      }
      for (int i = a_pos; i < q[a_stack].size(); ++i)
        q[b_stack].push_back(q[a_stack][i]);
      q[a_stack].erase(q[a_stack].begin() + a_pos, q[a_stack].end());
    }
    if (cmd == "pile" && subcmd == "over") {
      for (int i = a_pos; i < q[a_stack].size(); ++i)
        q[b_stack].push_back(q[a_stack][i]);
      q[a_stack].erase(q[a_stack].begin() + a_pos, q[a_stack].end());
    }
  }
  for (int i = 0; i < n; ++i) {
    os << i << ":";
    if (q[i].size() > 0)
      for (int j = 0; j < q[i].size(); ++j)
        os << " " << q[i][j];
    os << endl;
  }
}

const char* liner = "--------";
int problem;
int problem_filter;

#ifdef int
#undef int
#endif

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
"10\n"
"move 9 onto 1\n"
"move 8 over 1\n"
"move 7 over 1\n"
"move 6 over 1\n"
"pile 8 over 6\n"
"pile 8 over 5\n"
"move 2 over 1\n"
"move 4 over 9\n"
"quit\n"
,
"0: 0\n"
"1: 1 9 2 4\n"
"2:\n"
"3: 3\n"
"4:\n"
"5: 5 8 7 6\n"
"6:\n"
"7:\n"
"8:\n"
"9:\n"
);

#ifdef _DEBUG
getchar();
#endif

#else

// ifstream is("INPUT.TXT");
// ofstream os("OUTPUT.TXT");
istream& is = cin;
ostream& os = cout;

solve(is, os);

#endif

return 0;
}
