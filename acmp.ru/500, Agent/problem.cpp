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

void solve(istream& is, ostream& os) {
  int N; is >> N;
  map<int, int> agents;
  while (N--) {
    int age; is >> age;
    is >> agents[age];
  }
  vector< pair<int, int> > dp(1);
  for (map<int, int>::iterator i = agents.begin(); i != agents.end(); ++i) {
    if (i == agents.begin()) continue;
    int v = i->second;
    if (i == ++agents.begin())
      dp.push_back(make_pair(v, v));
    else
      dp.push_back(make_pair(min(dp.back().first + v, dp.back().second + v),
                             dp.back().first));
  }
  os << dp.back().first << endl;
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
