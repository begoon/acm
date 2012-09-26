#include <iostream>
#include <vector>
#include <map>
#include <set>
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

int time_to_int(const string& t) {
  istringstream is(t.c_str());
  int h, m, s;
  char c;
  is >> h >> c >> m >> c >> s;
  h -= 1;
  return h * 60 * 60 + m * 60 + s;
}

string int_to_time(int t) {
  int h = t / (60 * 60);
  t %= 60 * 60;
  int m = t / 60;
  t %= 60;
  int s = t;
  char fmt[1024];
  sprintf(fmt, "%d:%02d:%02d", h + 1 , m, s);
  return fmt;
}

#ifdef max
#undef max
#endif

void fake() {
  while (true) {
    int N = 3;
    int total = 10; // * 60 * 60;
    vector<int> e(N);
    for (int i = 0; i < e.size(); ++i) e[i] = rand() % total;

    vector<int> t = e;    
    sort(t.begin(), t.end());
    t.push_back(t[0] + total);
    int best_time = t[0];
    int biggest_gap = 0;
    for (int i = 0; i < t.size() - 1; ++i) {
      if (t[i + 1] - t[i] > biggest_gap) {
        biggest_gap = t[i + 1] - t[i];
        best_time = t[i];
      }
    }
    best_time %= total;

    int ans_fast = best_time;
    
    t = e;
    sort(t.begin(), t.end());
    int best = numeric_limits<int>::max();
    best_time = -1;
    for (vector<int>::iterator a = t.begin(); a != t.end(); ++a) {
      int all = 0;
      for (vector<int>::iterator b = t.begin(); b != t.end(); ++b) {
        if (*a == *b) continue;
        if (*b < *a)
          all += *a - *b;
        else
          all += total - *b + *a;
      }
      if (all < best) {
        best = all;
        best_time = *a;
      }
    }
    assert(best_time != -1);
    
    int ans_bruteforce = best_time;

    if (ans_bruteforce != ans_fast) {
      copy(e.begin(), e.end(), ostream_iterator<int>(cout, " "));
      cout << endl;
      cout << "bruteforce: " << ans_bruteforce << ", fast: " << ans_fast << endl;
      exit(1);
    }
  }
}

void solve_1(istream& is, ostream& os) {
  fake();
  int N;
  is >> N;
  vector<int> t(N);
  for (vector<int>::iterator i = t.begin(); i != t.end(); ++i) {
    string v;
    is >> v;
    *i = time_to_int(v);
  }
  int total = 12 * 60 * 60;
  sort(t.begin(), t.end());
  t.push_back(t[0] + total);
  int best_time = t[0];
  int biggest_gap = 0;
  for (int i = 0; i < t.size() - 1; ++i) {
    if (t[i + 1] - t[i] > biggest_gap) {
      biggest_gap = t[i + 1] - t[i];
      best_time = t[i];
    }
  }
  best_time %= total;
  os << int_to_time(best_time) << endl;
}

void solve(istream& is, ostream& os) {
  int N;
  is >> N;
  vector<int> t(N);
  for (vector<int>::iterator i = t.begin(); i != t.end(); ++i) {
    string v;
    is >> v;
    *i = time_to_int(v);
  }
  sort(t.begin(), t.end());
  int best = numeric_limits<int>::max();
  int best_time = -1;
  int total = 12 * 60 * 60;
  for (vector<int>::iterator a = t.begin(); a != t.end(); ++a) {
    int all = 0;
    for (vector<int>::iterator b = t.begin(); b != t.end(); ++b) {
      if (*a == *b) continue;
      if (*b < *a)
        all += *a - *b;
      else
        all += total - *b + *a;
    }
    if (all < best) {
      best = all;
      best_time = *a;
    }
  }
  assert(best_time != -1);
  os << int_to_time(best_time) << endl;
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

  string test_name; // = "test0.tst";

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
