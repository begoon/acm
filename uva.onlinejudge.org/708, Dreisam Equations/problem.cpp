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

string trim(string s) {
  s.erase(0, s.find_first_not_of(" "));
  s.resize(s.find_last_not_of(" ") + 1);
  return s;
}

string put_operations(string s) {
  int i;
  while ((i = s.find(' ')) != string::npos) {
    if (i == 0 || i == s.length() - 1)
      s.erase(i, 1);
    else if ((isdigit(s[i-1]) || s[i-1] == ')') && (isdigit(s[i+1]) || s[i+1] == '('))
      s[i] = '$';
    else
      s.erase(i, 1);
  }

  for (int i = 0; i < (int)s.length() - 1; ++i) {
    if (s[i] == ')' && (isdigit(s[i+1]) || s[i+1] == '(') ||
       (isdigit(s[i]) || s[i+1] == ')') && s[i+1] == '(') {
      s.insert(i + 1, "$");
      i -= 1;
    }
  }
  return s;
}

enum {
  kNumber, kOp, kLeft, kRight, kEqual, kStop
};

int next(const string& s, int& i, int& v) {
  v = -1;
  if (i >= (int)s.length()) return kStop;
  int c = s[i];
  i += 1;
  if (c == '(') return kLeft;
  if (c == ')') return kRight;
  if (c == '=') return kEqual;
  if (c == '+' || c == '-' || c == '*') {
    v = c;
    return kOp;
  }
  assert(isdigit(c));
  v = c - '0';
  while (i < (int)s.length() && isdigit(s[i])) {
    v = v * 10 + s[i] - '0';
    i += 1;
  }
  return kNumber;
}

bool eval(string s) {
  int left = -1;
  stack<int> q, o;
  int v;
  int i = 0;
  int lex;
  while ((lex = next(s, i, v)) != kStop) {
    if (q.empty()) {
      if (lex == kNumber)
        left = v;
      else  if (lex == kEqual) {
        q.push(0);
        o.push('+');
      }
    } else {
      if (lex == kLeft) {
        q.push(0);
        o.push('+');
      } else if (lex == kRight || lex == kNumber) {
        if (lex == kRight) {
          assert(q.size() >= 2);
          assert(o.size() >= 2);
          v = q.top();
          q.pop();
          o.pop();
        }
        if (o.top() == '+') q.top() += v;
        else if (o.top() == '-') q.top() -= v;
        else if (o.top() == '*') q.top() *= v;
        o.top() = '?';
      } else if (lex == kOp) {
        o.top() = v;
      }
    }
  }
  assert(q.size() == 1);
  assert(o.size() == 1);
  assert(o.top() == '?');

  return left == q.top();
}

bool f(int pos, string& s) {
  if (pos == string::npos) {
    return eval(s);
  } else {
    s[pos] = '+';
    if (f(s.find('$', pos + 1), s)) return true;
    s[pos] = '-';
    if (f(s.find('$', pos + 1), s)) return true;
    s[pos] = '*';
    if (f(s.find('$', pos + 1), s)) return true;
    s[pos] = '$';
  }
  return false;
}

void solve(istream& is, ostream& os) {
  int cnt = 1;
  do {
    string s;
    getline(is, s);
    if (s == "0") break;
    s = put_operations(s);
    os << "Equation #" << cnt << ":" << endl;
    os << (f(s.find('$'), s) ? s : string("Impossible.")) << endl << endl;
    cnt += 1;
  } while (true);
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
"10=2 3 4\n"
"3=((1))((2))\n"
"0\n"
,
"Equation #1:\n"
"10=2*3+4\n"
"\n"
"Equation #2:\n"
"3=((1))+((2))\n"
"\n"
);

run(__LINE__,
"10=2 3 4\n"
"0\n"
,
"Equation #1:\n"
"10=2*3+4\n"
"\n"
);

run(__LINE__,
" ( ( 13 ) ) =  (( ( 7) )( 5 3  )   )2  \n"
"0\n"
,
"Equation #1:\n"
"((13))=(((7))+(5+3))-2\n"
"\n"
);

run(__LINE__,
"3=((1))((2))\n"
"0\n"
,
"Equation #1:\n"
"3=((1))+((2))\n"
"\n"
);

run(__LINE__,
"30 =(((3 3 5)))\n"
"0\n"
,
"Equation #1:\n"
"30=(((3+3*5)))\n"
"\n"
);

run(__LINE__,
"888=(80) (800) (8)\n"
"0\n"
,
"Equation #1:\n"
"888=(80)+(800)+(8)\n"
"\n"
);

run(__LINE__,
"18=7 (5 3) 2\n"
"0\n"
,
"Equation #1:\n"
"18=7+(5-3)*2\n"
"\n"
);

run(__LINE__,
" (( 18 ) ) =7 (5 3) 2\n"
"0\n"
,
"Equation #1:\n"
"((18))=7+(5-3)*2\n"
"\n"
);

run(__LINE__,
"18= 7 (5 3) 2 \n"
"0\n"
,
"Equation #1:\n"
"18=7+(5-3)*2\n"
"\n"
);

run(__LINE__,
"5= 3 3\n"
"0\n"
,
"Equation #1:\n"
"Impossible.\n"
"\n"
);

run(__LINE__,
"5= ( (5 ))\n"
"0\n"
,
"Equation #1:\n"
"5=((5))\n"
"\n"
);

run(__LINE__,
"25= (5 (5 ) )\n"
"0\n"
,
"Equation #1:\n"
"25=(5*(5))\n"
"\n"
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
