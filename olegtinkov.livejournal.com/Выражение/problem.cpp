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

enum {
  ADD = -1, SUB = -2, MULT = -3, DIV = -4
};

void print(vector<int>& p, vector<double>& c) {
  for (size_t i = 0; i < p.size(); ++i) {
    if (i > 0) cout << " ";
    if (p[i] == MULT)
      cout << "*";
    else if (p[i] == DIV)
      cout << "/";
    else if (p[i] == ADD)
      cout << "+";
    else if (p[i] == SUB)
      cout << "-";
    else {
      cout << c[p[i]];
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
      if (p[i] == ADD)
        r = a + b;
      else if (p[i] == SUB)
        r = b - a;
      else if (p[i] == MULT)
        r = a * b;
      else if (p[i] == DIV)
        r = b / a;
      else {
        print(p, c);
        assert(0);
      }
      q.push(r);
    }
  }
  if (q.size() != 1)
    assert(0);
  return q.top();
}

template <typename T>
string itoa(T a) {
  stringstream fmt;
  fmt << a;
  return fmt.str();
}

string to_infix(vector<int>& p, vector<double>& c) {
  stack<string> q;
  for (size_t i = 0; i < p.size(); ++i) {
    if (p[i] >= 0)
      q.push(itoa(c[p[i]]));
    else {
      if (q.size() < 2)
        assert(0);
      string a = q.top();
      q.pop();
      string b = q.top();
      q.pop();
      string op;
      if (p[i] == ADD) op = "+";
      else if (p[i] == SUB) op = "-";
      else if (p[i] == MULT) op = "*";
      else if (p[i] == DIV) op = "/";
      else
        assert(0);
      string r = string("(") + b + op + a + ")";
      q.push(r);
    }
  }
  if (q.size() != 1)
    assert(0);
  return q.top();
}

bool f(int pos, int d, vector<int>& p, vector<bool>& u, vector<double>& c, double& C, ostream& os) {
  if (p.size() >= u.size() * 2 - 1) {
    double v = eval(p, c);
    if (fabs(C - v) < EPS)  {
      string s = to_infix(p, c);
      os << s << endl;
    }
  }

  int op[4] = { ADD, SUB, MULT, DIV };

  if (d >= 2) {
    for (int i = 0; i < 4; ++i) {
      p.push_back(op[i]);
      if (f(pos + 1, d - 1, p, u, c, C, os))
        return true;
      p.pop_back();
    }
  }

  for (int i = 0; i < u.size(); ++i) if (!u[i]) {
    p.push_back(i);
    u[i] = true;
    if (f(pos + 1, d + 1, p, u, c, C, os))
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

  f(0, 0, p, u, c, C, os);
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
"4 24\n"
"1 3 4 6\n"
,
"(6/(1-(3/4)))\n"
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
