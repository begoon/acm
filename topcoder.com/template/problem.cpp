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

class PerfectSequences {
public:
  string fixIt( vector <int> seq ) {

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
	
	int verify_case(int casenum, const string &expected, const string &received, clock_t elapsed) { 
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
			cerr << "    Expected: \"" << expected << "\"" << endl; 
			cerr << "    Received: \"" << received << "\"" << endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case(int casenum) {
		switch (casenum) {
		case 0: {
			int seq[]                 = {1,3,4};
			string expected__         = "Yes";

			clock_t start__           = clock();
			string received__         = PerfectSequences().fixIt(vector <int>(seq, seq + (sizeof seq / sizeof seq[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int seq[]                 = {1,2,3};
			string expected__         = "No";

			clock_t start__           = clock();
			string received__         = PerfectSequences().fixIt(vector <int>(seq, seq + (sizeof seq / sizeof seq[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int seq[]                 = {1,4,2,4,2,4};
			string expected__         = "No";

			clock_t start__           = clock();
			string received__         = PerfectSequences().fixIt(vector <int>(seq, seq + (sizeof seq / sizeof seq[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int seq[]                 = {1000000,1,1,1,1,2};
			string expected__         = "Yes";

			clock_t start__           = clock();
			string received__         = PerfectSequences().fixIt(vector <int>(seq, seq + (sizeof seq / sizeof seq[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			int seq[]                 = {8};
			string expected__         = "Yes";

			clock_t start__           = clock();
			string received__         = PerfectSequences().fixIt(vector <int>(seq, seq + (sizeof seq / sizeof seq[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 5: {
			int seq[]                 = {2,0,2};
			string expected__         = "No";

			clock_t start__           = clock();
			string received__         = PerfectSequences().fixIt(vector <int>(seq, seq + (sizeof seq / sizeof seq[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int seq[]                 = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = PerfectSequences().fixIt(vector <int>(seq, seq + (sizeof seq / sizeof seq[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int seq[]                 = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = PerfectSequences().fixIt(vector <int>(seq, seq + (sizeof seq / sizeof seq[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int seq[]                 = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = PerfectSequences().fixIt(vector <int>(seq, seq + (sizeof seq / sizeof seq[0])));
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
