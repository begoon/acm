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

void solve_slow(istream& is, ostream& os) {
 int n, k;
 string s;
 is >> n >> k >> s;
 vector<int> dp(n, 0);
 for (int t = 1; t < n; ++t) {
   int m = numeric_limits<int>::max();
   for (int i = 1; i <= min(t, k); ++i)
     m = min(dp[t - i] + (s[t] == s[t - i] ? 0 : 1), m);
   dp[t] = m;
 }
 os << dp[n - 1] << endl;
}

void solve(istream& is, ostream& os) {
 int n, k;
 string s;
 is >> n >> k >> s;
 for (int i = 0; i < s.length(); ++i) s[i] -= 'A';
 vector<int> dp(n, 0);
 vector<int> a(26, -1);
 a[s[0]] = 0;
 for (int t = 1; t < n; ++t) {
   dp[t] = numeric_limits<int>::max();
   for (int i = 0; i < a.size(); ++i) {
     if (a[i] == -1) continue;
     int cost = s[t] == i ? 0 : 1;
     dp[t] = min(dp[t], dp[a[i]] + cost);
   }
   a[s[t]] = t;
   int j = t - k;
   if (j >= 0 && a[s[j]] == j)
     a[s[j]] = -1;
 }
 os << dp[n - 1] << endl;
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
   error << __FILE__ << "(" << line << "): error: test case " <<
problem << " FAILED" << endl;
   OutputDebugStringA(error.str().c_str());
#endif
   cerr << liner << "EXPECTED" << liner << endl << output;
   cerr << liner << "-ACTUAL-" << liner << endl << os.str()
        << liner << liner << liner << endl;
 } else
   cerr << "Case #" << problem << " OK (line " << line << ")" << endl;
}

#ifdef int
#undef int
#endif

void check() {
 while (true) {
   int n = (rand() % 100) + 2;
   string s(n, ' ');
   for (int i = 0; i < n; ++i)
     s[i] = (rand() % 26) + 'A';
   int k = (rand() % (n - 1)) + 1;
   ostringstream fmt;
   fmt << n << " " << k << endl << s << endl;
   istringstream is1(fmt.str());
   ostringstream os1;
   solve_slow(is1, os1);
   istringstream is2(fmt.str());
   ostringstream os2;
   solve(is2, os2);
   if (os1.str() != os2.str()) {
     cout << n << " " << k << " " << s << endl;
     cout << "[" << os1.str() << "]" << endl;
     cout << "[" << os2.str() << "]" << endl;
     return;
   }
 }
}

int main(int argc, char* argv[]) {
#ifdef TESTING_

// check();
problem = -1;
problem_filter = 0;

run(__LINE__,
"3 2 ABC\n"
,
"1\n"
);

run(__LINE__,
"10 2\n"
"ABABBCACBC\n"
,
"2\n"
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
