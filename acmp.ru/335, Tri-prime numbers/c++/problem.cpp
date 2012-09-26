#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>
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
#include <cstring>
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

ostream& print(const vector<int>& v, ostream& os) {
  copy(v.begin(), v.end(), ostream_iterator<vector<int>::value_type>(os, " "));
  return os;
}

ostream& print(const vector<vector<int> >& v, ostream& os) {
  for (vector<vector<int> >::const_iterator i = v.begin(); i != v.end(); ++i) {
    print(*i, os) << endl;
  }
  return os;
}

int ten(int n) {
  int r = 10;
  while (--n)
    r *= 10;
  return r;
}

bool is_prime(int n) {
  if (n == 1) return false;
  else if (n < 4) return true;
  else if (n % 2 == 0) return false;
  else if (n < 9) return true;
  else if (n % 3 == 0) return false;
  else {
    int r = std::sqrt(static_cast<double>(n));
    int f = 5;
    while (f <= r) {
      if (n % f == 0) return false;
      if (n % (f + 2) == 0) return false;
      f += 6;
    }
    return true;
  }
}

void solve_bruteforce(istream& is, ostream& os) {
  vector<int> primes(1000, 1);
  primes[0] = primes[1] = 0;
  for (int i = 2; i * i < primes.size(); ++i) {
    if (!primes[i]) continue;
    for (int j = i * 2; j < primes.size(); j += i)
      primes[j] = false;
  }
  int n; is >> n;
  int from = ten(n - 1);
  int to = ten(n);
  int ans = 0;
  for (int i = from; i < to; ++i) {
    ostringstream os;
    os << i;
    const string& v = os.str();
    bool good = true;
    for (int j = 0; good && j < v.length() - 2; ++j) {
      int n = atoi(v.substr(j, 3).c_str());
      bool prime = primes[n];
      if (n < 100 || !prime)
        good = false;
    }
    if (good)
      ans += 1;
  }
  os << ans << endl;
}

void solve(istream& is, ostream& os) {
  vector<int> primes(1000, 1);
  primes[0] = primes[1] = 0;
  for (int i = 2; i * i < primes.size(); ++i) {
    if (!primes[i]) continue;
    for (int j = i * 2; j < primes.size(); j += i)
      primes[j] = false;
  }

  int N; is >> N;

  vector< vector< vector<int> > > dp(N + 1, vector< vector<int> >(10, vector<int>(10, 0)));

  int M = 1000000009;
  for (int n = 3; n <= N; ++n) {
    for (int i = 0; i < 10; ++i) {
      for (int j = 0; j < 10; ++j) {
        dp[n][i][j] = 0;
        for (int k = 1; k <= 9; ++k) {
          if (primes[k * 100 + i * 10 + j]) {
            if (n == 3)
              dp[n][i][j] += 1;
            else
              dp[n][i][j] = (dp[n][i][j] + dp[n - 1][k][i]) % M;
          }
        }
      }
    }
  }
  int r = 0;
  for (int i = 0; i < 10; ++i)
    for (int j = 0; j < 10; ++j)
      r = (r + dp[N][i][j]) % M;
  os << r << endl;
}

#ifdef int
#undef int
#endif

#include <ctime>

void run(const string& test_name, const char* input, const char* output) {
  const char* liner = "--------";
  stringstream is(input);
  stringstream os;
  clock_t started = clock();
  solve(is, os);
  clock_t elapsed = clock() - started;
  if (os.str() != output) {
    cerr << "Case '" << test_name << "': FAILED" << endl;
    cerr << liner << "EXPECTED" << liner << endl << output;
    cerr << liner << "-ACTUAL-" << liner << endl << os.str() 
         << liner << liner << liner << endl;
  } else {
    cerr << "Case '" << test_name << "': OK";
    if (elapsed > CLOCKS_PER_SEC / 200)
      cerr << " time " << elapsed * (1.0/CLOCKS_PER_SEC) << "s";
    cerr << endl;
  }
}

void run_test(const string& test_name) {
  ifstream test(test_name.c_str());
  if (test.fail()) return;
  ostringstream input, output;
  string line;
  bool is_input = true;
  while (getline(test, line)) {
    if (line.substr(0, 5) == "~~~~~")
      is_input = false;
    else
      (is_input ? input : output) << line << endl;
  }
  run(test_name, input.str().c_str(), output.str().c_str());
}

int main(int argc, char* argv[]) {
#ifdef TESTING_

  string test_name; // = "test-0.tst";

  if (!test_name.empty()) {
    run_test(test_name);  
  } else {
    int case_id = 0;
    while (case_id < 100) {
      ostringstream fmt;
      fmt << "test-" << setfill('0') << setw(2) << case_id << ".tst";
      test_name = fmt.str();
      run_test(test_name);
      case_id += 1;
    }    
  }

#else

  ifstream is("input.txt");
  ofstream os("output.txt");

  // istream& is = cin;
  // ostream& os = cout;
  
  solve(is, os);

#endif

#ifdef _DEBUG
  getchar();
#endif

  return 0;
}
