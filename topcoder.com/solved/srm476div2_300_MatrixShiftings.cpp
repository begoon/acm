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

int min(int a, int b) { return a < b ? a : b; }

class MatrixShiftings {
public:
  int minimumShifts( vector <string> matrix, int value ) {
    int ans = numeric_limits<int>::max();
    bool found = false;
    for (int i = 0; i < matrix.size(); ++i) {
      for (int j = 0; j < matrix[0].length(); ++j) {
        if (value + '0' != matrix[i][j]) continue;
        ans = min(ans, min(i, matrix.size() - i) + min(j, matrix[0].length() - j));
        found = true;
      }
    }
    return found ? ans : -1;
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
			string matrix[]           = {"136",
 "427",
 "568",
 "309"};
			int value                 = 2;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = MatrixShiftings().minimumShifts(vector <string>(matrix, matrix + (sizeof matrix / sizeof matrix[0])), value);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			string matrix[]           = {"0000",
 "0000",
 "0099"};
			int value                 = 9;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = MatrixShiftings().minimumShifts(vector <string>(matrix, matrix + (sizeof matrix / sizeof matrix[0])), value);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			string matrix[]           = {"0123456789"};
			int value                 = 7;
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = MatrixShiftings().minimumShifts(vector <string>(matrix, matrix + (sizeof matrix / sizeof matrix[0])), value);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			string matrix[]           = {"555",
 "555"};
			int value                 = 1;
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = MatrixShiftings().minimumShifts(vector <string>(matrix, matrix + (sizeof matrix / sizeof matrix[0])), value);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			string matrix[]           = {"12417727123",
 "65125691886",
 "55524912622",
 "12261288888"};
			int value                 = 9;
			int expected__            = 6;

			clock_t start__           = clock();
			int received__            = MatrixShiftings().minimumShifts(vector <string>(matrix, matrix + (sizeof matrix / sizeof matrix[0])), value);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string matrix[]           = ;
			int value                 = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = MatrixShiftings().minimumShifts(vector <string>(matrix, matrix + (sizeof matrix / sizeof matrix[0])), value);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string matrix[]           = ;
			int value                 = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = MatrixShiftings().minimumShifts(vector <string>(matrix, matrix + (sizeof matrix / sizeof matrix[0])), value);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string matrix[]           = ;
			int value                 = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = MatrixShiftings().minimumShifts(vector <string>(matrix, matrix + (sizeof matrix / sizeof matrix[0])), value);
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
