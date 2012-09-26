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

const double EPS = 1.0E-9;

void print(vector<int>& p) {
  for (size_t i = 0; i < p.size(); ++i) {
    if (i > 0) cout << " ";
    if (p[i] == -2)
      cout << "*";
    else if (p[i] == -1)
      cout << "+";
    else {
      cout << "C" << p[i];
    }
  }
  cout << endl;
}

double eval(vector<int>& p, vector<double>& c) {
  stack<double> q;
  for (size_t i = 0; i < p.size(); ++i) {
    if (p[i] >= 0)
      q.push(c[p[i]]);
    else {
      if (q.size() < 2)
        return -1;
      double a = q.top();
      q.pop();
      double b = q.top();
      q.pop();
      double r;
      if (p[i] == -1)
        r = a + b;
      else if (p[i] == -2)
        r = (a*b)/(a+b);
      else
        return -1;
      q.push(r);
    }
  }
  if (q.size() != 1)
    return -1;
  return q.top();
}

bool f(int pos, int d, vector<int>& p, vector<bool>& u, vector<double>& c, double& C) {
  if (p.size() >= 2 && d == 1) {
    double v = eval(p, c);
    if (v < 0) {
      print(p);
      assert(!(v < 0));
    }
    if (fabs(C - v - EPS) < 0.01) 
      return true;
  }

  if (p.size() >= u.size() * 2 + 1)
    return false;

  if (d >= 2) {
    p.push_back(-2);
    if (f(pos + 1, d - 1, p, u, c, C))
      return true;
    p.pop_back();
    p.push_back(-1);
    if (f(pos + 1, d - 1, p, u, c, C))
      return true;
    p.pop_back();
  }

  for (int i = 0; i < u.size(); ++i) if (!u[i]) {
    p.push_back(i);
    u[i] = true;
    if (f(pos + 1, d + 1, p, u, c, C))
      return true;
    u[i] = false;
    p.pop_back();
  }
  return false;
}

void solve(istream& is, ostream& os) {
  int N;
  double C;
  is >> N >> C;
  vector<double> c(N);
  for (int i = 0; i < N; ++i) is >> c[i];

  vector<bool> u(N, false);
  vector<int> p;

  if (f(0, 0, p, u, c, C)) {
    os << "YES" << endl;
    return;
  }
  os << "NO" << endl;
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
"3 2\n"
"1 1 10\n"
,
"YES\n"
);

run(__LINE__,
"4 2.1\n"
"1 2 3 4\n"
,
"YES\n"
);

run(__LINE__,
"4 3.422\n"
"2 3 4 5\n"
,
"YES\n"
);

run(__LINE__,
"4 0.66\n" 
"1 2 3 4\n"
,
"YES\n"
);

run(__LINE__,
"5 3.71\n" 
"1 7 9 3 1\n" 
,
"YES\n"
);

run(__LINE__,
"5 0.506024096\n"
"2 7 3 1 0\n"
,
"YES\n"
);

run(__LINE__,
"4 1.7642\n"
"1 6 7 2\n"
,
"NO\n"
);

run(__LINE__,
"3 1.66\n"
"1 2 1\n"
,
"YES\n"
);

run(__LINE__,
"6 2.7\n"
"1 2 1 3 4 5\n"
,
"YES\n"
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
