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
using namespace std;

vector<string> tokenize(string s, string ch) {
  vector<string> ret;
  for (int p = 0, p2; p < s.size(); p = p2 + 1) {
    p2 = s.find_first_of(ch, p);
    if (p2 == -1) p2 = s.size();
    if (p2 - p > 0) ret.push_back(s.substr(p, p2 - p));
  }
  return ret;
}

bool check(int f, vector<string>& words, int width, int height) {
  int x = 0, y = 0;
  for (int i = 0; i < words.size(); ++i) {
    int w = words[i].length() * (f + 2);
    if (x > 0)
      w += f + 2;
    int h = f * 2;
    if (y + h > height) return false;
    while (x + w > width) {
      if (x > 0)
        w -= f + 2;
      y += h;
      if (y + f * 2 > height) return false;
      x = 0;
    }
    x += w;
  }
  return true;
}

class StringFragmentation {
public:
  int largestFontSize( string text, int width, int height ) {
    vector<string> words = tokenize(text, " ");
    int best = -1;
    for (int f = 8; ; ++f) {
      if (!check(f, words, width, height))
        return best;
      best = f;
    }
    return best;
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
			string text               = "ONE TWO THREE FOUR FIVE";
			int width                 = 150;
			int height                = 40;
			int expected__            = 9;

			clock_t start__           = clock();
			int received__            = StringFragmentation().largestFontSize(text, width, height);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			string text               = "ONE TWO THREE FOUR FIVE";
			int width                 = 150;
			int height                = 60;
			int expected__            = 10;

			clock_t start__           = clock();
			int received__            = StringFragmentation().largestFontSize(text, width, height);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			string text               = "ONE TWO THREE FOUR FIVE";
			int width                 = 150;
			int height                = 10000;
			int expected__            = 28;

			clock_t start__           = clock();
			int received__            = StringFragmentation().largestFontSize(text, width, height);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			string text               = "ONE TWO THREE FOUR FIVE";
			int width                 = 10000;
			int height                = 10000;
			int expected__            = 1250;

			clock_t start__           = clock();
			int received__            = StringFragmentation().largestFontSize(text, width, height);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			string text               = "ONE TWO THREE FOUR FIVE";
			int width                 = 50;
			int height                = 50;
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = StringFragmentation().largestFontSize(text, width, height);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 5: {
			string text               = "A";
			int width                 = 9;
			int height                = 14;
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = StringFragmentation().largestFontSize(text, width, height);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

      case 6: {
			string text               = "A";
			int width                 = 10000;
			int height                = 10000;
			int expected__            = 5000;

			clock_t start__           = clock();
			int received__            = StringFragmentation().largestFontSize(text, width, height);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
/*      case 7: {
			string text               = ;
			int width                 = ;
			int height                = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = StringFragmentation().largestFontSize(text, width, height);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string text               = ;
			int width                 = ;
			int height                = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = StringFragmentation().largestFontSize(text, width, height);
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
