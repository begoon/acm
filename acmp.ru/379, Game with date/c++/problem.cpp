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

const int days[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

void print_map(int m[12][31]) {
  for (int i = 0; i < 12; ++i) {
    for (int j = 0; j < 31; ++j)
      if (j + 1 <= days[i])
        cerr << (char)(m[i][j] ? m[i][j] : '.');
    cerr << endl;
  }
  cerr << endl;
}

void push(int f[12][31], queue<int>& s, int m, int d, int c) {
  if (f[m][d]) return;
  int sign = c == '+' ? 0x10000 : 0;
  f[m][d] = c;
  s.push(m * 256 + d + sign);
}

bool is_valid_date(int f[12][31], int m, int d) {
  if (m < 0 || m > 11) return false;
  if (d < 0 || d + 1 > days[m]) return false;
  assert(f[m][d] != 0);
  return true;
}

void solve(istream& is, ostream& os) {
  int day, month; is >> day >> month;

  int f[12][31];
  memset(f, 0, sizeof(f));

  for (int m = 11; m >= 0; --m) {
    for (int d = 30; d >= 0; --d) {
      if (m == 11 && d == 30) {
        f[m][d] = '+';
        continue;
      } else {
        int loss = true;
        if (is_valid_date(f, m + 1, d)) loss = loss && f[m + 1][d] == '+';
        if (is_valid_date(f, m + 2, d)) loss = loss && f[m + 2][d] == '+';
        if (is_valid_date(f, m, d + 1)) loss = loss && f[m][d + 1] == '+';
        if (is_valid_date(f, m, d + 2)) loss = loss && f[m][d + 2] == '+';
        f[m][d] = loss ? '-' : '+';
      }
    }
  }
  // print_map(f);
  os << (f[month - 1][day - 1] == '+' ? 1 : 2) << endl;
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
