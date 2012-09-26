#include <string>
#include <vector>
#include <set>
#include <functional>
#include <numeric>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <list>
#include <stack>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <limits>
#include <iterator>
#include <cmath>
#include <ctime>
#include <cassert>
using namespace std;

bool simulate(vector<int>& p, int limit) {
  int n = p.size();
  vector<pair<int, int> > seats(n * 2, make_pair(-1, 0));
  for (int i = 0; i < p.size(); ++i)
    seats[i] = make_pair(p[i], 74);
  while (--limit) {
    int zeroes = 0;
    for (int i = seats.size() - 1; i >= 0; --i) {
      if (seats[i].first == -1) continue;
      if (!seats[i].second) {
        zeroes += 1;
        continue;
      }
      if (i + 1 == seats[i].first + n) {
        assert(seats[i].second > 0);
        seats[i].second -= 1;
        if (seats[i].second == 0)
          zeroes += 1;
      } else if (i + 1 < seats[i].first + n) {
        if (seats[i + 1].second == 0)
          swap(seats[i], seats[i + 1]);
      }
    }
    if (zeroes == n)
      return true;
  }
  return false;
}

void f(int pos, vector<int>& p, vector<int>& pattern, int used, int limit, int& count) {
  if (pos == p.size()) {
    if (simulate(p, limit))
      count += 1;
    return;
  }
  int n = p.size();
  int j = pattern[pos];
  if (j == -1) {
    assert((used & (1 << (j - 1))) == 0);
    for (int i = 0; i < n; ++i) {
      if (used & (1 << i)) continue;
      p[pos] = i + 1;
      f(pos + 1, p, pattern, used | (1 << i), limit, count);
    }
  } else {
    assert(used & (1 << (j - 1)));
    p[pos] = j;
    f(pos + 1, p, pattern, used, limit, count);
  }
}

class TheBoardingDivTwo {
public:
  int find( vector <int> pattern, int boardingTime ) {
    int count = 0;
    vector<int> p(pattern.size(), 0);
    int used = 0;
    for (int i = 0; i < pattern.size(); ++i)
      if (pattern[i] != -1)
        used |= 1 << (pattern[i] - 1);
    // used = 0;
    f(0, p, pattern, used, boardingTime, count);
    return count;
  }
};

// BEGIN CUT HERE
namespace moj_harness {
	int run_test_case(int);
	void run_test(int casenum = -1, bool quiet = false) {
		if (casenum != -1) {
			if (run_test_case(casenum) == -1 && !quiet) {
				cerr << "Illegal input! Test case " << casenum << " does not exist." << endl;
			}
			return;
		}
		
		int correct = 0, total = 0;
		for (int i=0;; ++i) {
			int x = run_test_case(i);
			if (x == -1) {
				if (i >= 100) break;
				continue;
			}
			correct += x;
			++total;
		}
		
		if (total == 0) {
			cerr << "No test cases run." << endl;
		} else if (correct < total) {
			cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << endl;
		} else {
			cerr << "All " << total << " tests passed!" << endl;
		}
	}
	
	int verify_case(int casenum, const int &expected, const int &received, clock_t elapsed) { 
		cerr << "Example " << casenum << "... "; 
		
		string verdict;
		vector<string> info;
		char buf[100];
		
		if (elapsed > CLOCKS_PER_SEC / 200) {
			sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}
		
		if (expected == received) {
			verdict = "PASSED";
		} else {
			verdict = "FAILED";
		}
		
		cerr << verdict;
		if (!info.empty()) {
			cerr << " (";
			for (int i=0; i<(int)info.size(); ++i) {
				if (i > 0) cerr << ", ";
				cerr << info[i];
			}
			cerr << ")";
		}
		cerr << endl;
		
		if (verdict == "FAILED") {
			cerr << "    Expected: " << expected << endl; 
			cerr << "    Received: " << received << endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case(int casenum) {
		switch (casenum) {
		case 0: {
			int pattern[]             = {-1, -1};
			int boardingTime          = 100;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = TheBoardingDivTwo().find(vector <int>(pattern, pattern + (sizeof pattern / sizeof pattern[0])), boardingTime);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int pattern[]             = {-1, 2, -1};
			int boardingTime          = 222;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = TheBoardingDivTwo().find(vector <int>(pattern, pattern + (sizeof pattern / sizeof pattern[0])), boardingTime);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int pattern[]             = {2, 1, 3, 5, 4, 6};
			int boardingTime          = 155;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = TheBoardingDivTwo().find(vector <int>(pattern, pattern + (sizeof pattern / sizeof pattern[0])), boardingTime);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int pattern[]             = {-1, -1, -1, -1, -1, -1, -1};
			int boardingTime          = 198;
			int expected__            = 233;

			clock_t start__           = clock();
			int received__            = TheBoardingDivTwo().find(vector <int>(pattern, pattern + (sizeof pattern / sizeof pattern[0])), boardingTime);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		case 4: {
			int pattern[]             = {-1, -1, -1, -1, -1, -1};
			int boardingTime          = 158;
			int expected__            = 88;

			clock_t start__           = clock();
			int received__            = TheBoardingDivTwo().find(vector <int>(pattern, pattern + (sizeof pattern / sizeof pattern[0])), boardingTime);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int pattern[]             = ;
			int boardingTime          = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TheBoardingDivTwo().find(vector <int>(pattern, pattern + (sizeof pattern / sizeof pattern[0])), boardingTime);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int pattern[]             = ;
			int boardingTime          = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TheBoardingDivTwo().find(vector <int>(pattern, pattern + (sizeof pattern / sizeof pattern[0])), boardingTime);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int pattern[]             = ;
			int boardingTime          = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TheBoardingDivTwo().find(vector <int>(pattern, pattern + (sizeof pattern / sizeof pattern[0])), boardingTime);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}
 

int main(int argc, char *argv[]) {
    if (argc == 1) {
        moj_harness::run_test();
    } else {
        for (int i=1; i<argc; ++i)
            moj_harness::run_test(atoi(argv[i]));
    }
    getchar();
}
// END CUT HERE
