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

int pow(int a, int n) {
  int r = 1;
  while (n)
    if (n & 1) {
      r *= a;
      --n;
    } else {
      a *= a;
      n >>= 1;
    }
  return r;
}

const long long MOD = 1000000007;

long long dp[7][16384];
bool forbidden[7][7];

int M, N, K;

void f(int row, int col, int mask, int new_mask, int val) {
  if (col == N) {
    dp[row][new_mask] = (dp[row][new_mask] + val) % MOD;
    return;
  }
  if (forbidden[row][col]) {
    f(row, col + 1, mask, new_mask, val);
    return;
  }
  int top = (mask >> col * 2) & 0x03;
  int left = (new_mask >> (col - 1) * 2) & 0x03;
  for (int i = 0; i < 4; ++i) {
    new_mask |= i << col * 2;
    if ((row == 0 || forbidden[row - 1][col] || top != i) &&
        (col == 0 || forbidden[row][col - 1] || left != i))
      f(row, col + 1, mask, new_mask, val);
    new_mask ^= i << col * 2;
  }
}

void solve(istream& is, ostream& os) {
  int T;
  is >> T;
  for (int t = 1; t <= T; ++t) {
    is >> M >> N >> K;
    M += 1;  // number of rows
    N += 1;  // number of columns

    memset(dp, 0, sizeof(dp));
    memset(forbidden, 0, sizeof(forbidden));

    for (int k = 0, x, y; k < K; ++k) {
      is >> y >> x; --y; --x;
      forbidden[y][x] = true;
    }

    f(0, 0, 0, 0, 1);
    for (int m = 1; m < M; ++m)
      for (int mask = 0; mask < (1 << 2*N); ++mask)
        if (dp[m - 1][mask] > 0)
          f(m, 0, mask, 0, dp[m - 1][mask]);

    long long ans = 0;
    for (int i = 0; i < (1 << 2*N); ++i)
      ans = (ans + dp[M-1][i]) % MOD;

    os << "Case " << t << ": " << ans << endl;
  }
}

void solve_crap(istream& is, ostream& os) {
  int T;
  is >> T;
  for (int t = 1; t <= T; ++t) {
    int M, N, K;
    is >> M >> N >> K;
    M += 1;  // number of rows
    N += 1;  // number of columns
  
#if 0
    cout << "M = " << M << ", N = " << N << ", K = " << K << endl;
#endif    
    vector<vector<bool> > forbidden(M, vector<bool>(N, false));
    vector<int> forbidden_mask(M, 0);
    for (int k = 0, x, y; k < K; ++k) {
      is >> y >> x; --y; --x;
      forbidden[y][x] = true;
      forbidden_mask[y] |= 0x03 << x * 2;
    }
#if 0
    cout << "FORBIDDEN MASK:" << endl;
    for (int i = 0; i < forbidden_mask.size(); ++i)
      cout << dec << i << ": " << hex << forbidden_mask[i] << ", ";
    cout << dec << endl;
#endif    

    int C = pow(4, N);
#if 0    
    cout << "C = " << C << endl;
#endif    
    vector<vector<long long> > dp(M, vector<long long>(C, 0));
    for (int m = 0; m < M; ++m) {
#if 1
      cout << "m = " << m << endl;
#endif      
      vector<bool> used_i(C, false);
      for (int ii = 0; ii < C; ++ii) {
#if 1
        cout << "ii = " << ii << " ";
#endif      
        int i = ii & ~forbidden_mask[m];
        if (used_i[i]) continue;
        used_i[i] = true;

        for (int j = 0; j < C; ++j) {
          bool good = true;

          for (int n = 0; n < N && good; ++n) {
            if (n > 0 && forbidden[m][n - 1]) continue;
            if (m > 0 && forbidden[m - 1][n]) continue;
            int mask = 0x03 << (n * 2);
            if (n > 0 && ((i & mask) >> 2) == (i & (mask >> 2))) good = false;
            else if (m > 0 && (i & mask) == (j & mask)) good = false;
          }
          if (good) {
            if (m == 0)
              dp[m][i] = 1;
            else
              dp[m][i] += dp[m - 1][j];
            dp[m][i] %= MOD;
          }
        }
      }
    }
#if 0    
    cout << "DP:" << endl;
    for (int i = 0; i < M; ++i) {
      copy(dp[i].begin(), dp[i].end(), ostream_iterator<int>(cout, " "));
      cout << endl;
    }
#endif    
    long long ans = 0;
    for (int i = 0; i < C; ++i)
      ans = (ans + dp[M - 1][i]) % MOD;
    os << "Case " << t << ": " << ans << endl;
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
"2\n"
"1 1\n"
"1\n"
"2 1\n"
"0 0\n"
"0\n"
,
"Case 1: 36\n"
"Case 2: 4\n"
);

run(__LINE__,
"1\n"
"6 6\n"
"0\n"
,
"Case 1: 780059730\n"
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
