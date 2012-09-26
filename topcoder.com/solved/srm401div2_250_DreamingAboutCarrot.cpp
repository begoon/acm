// BEGIN CUT HERE
// PROBLEM STATEMENT
// John works at a company called "FIELD-Tech", and today, he was so tired after work that he fell asleep as soon as he 
// got home.  Unfortunately, even in his sleep, he was unable to forget about his work.  In one dream, he was asked to 
// help a carrot producing company deal with the following question: how many carrots grow on a line segment connecting 
// two given carrots?  The endpoints of the segment (i.e., the two given carrots) should not be included.  It's a rather 
// strange question, and to make it even stranger, the company's representatives (guys who have carrots instead of heads) 
// said that all the carrots grow on an infinite plane, and there is exactly one carrot at each point with integer 
// coordinates.  You must help tired John deal with this problem.
// 
// The coordinates of the two carrots are (x1, y1) and (x2, y2). Return the number of carrots that lie strictly on the 
// line segment connecting these carrots.
// 
// DEFINITION
// Class:DreamingAboutCarrots
// Method:carrotsBetweenCarrots
// Parameters:int, int, int, int
// Returns:int
// Method signature:int carrotsBetweenCarrots(int x1, int y1, int x2, int y2)
// 
// 
// CONSTRAINTS
// -x1, y1, x2, and y2 will each be between 0 and 50, inclusive.
// -(x1, y1) and (x2, y2) will represent different points.
// 
// 
// EXAMPLES
// 
// 0)
// 1
// 1
// 5
// 5
// 
// Returns: 3
// 
// There are three points inside of the segment: (2,2), (3,3) and (4,4).
// 
// 1)
// 0
// 0
// 1
// 1
// 
// Returns: 0
// 
// 2)
// 50
// 48
// 0
// 0
// 
// Returns: 1
// 
// 3)
// 0
// 0
// 42
// 36
// 
// Returns: 5
// 
// END CUT HERE

#line 66 "problem.cpp"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cmath>
using namespace std;

class DreamingAboutCarrots { 
  public: 
    int carrotsBetweenCarrots(int x1, int y1, int x2, int y2)  { 
      int min_x = min(x1, x2);
      int max_x = max(x1, x2);
      int r = 0;
      float i;
      for (int x = min_x + 1; x < max_x; ++x) {
        float y = ((float)(x2*y1 - x1*y2) - x*(y1-y2)) / (x2 - x1);
        if (std::modf(y, &i) < 0.0000001) r += 1;
      }
      return r;
      // $CARETPOSITION$ 
    } 
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 5; int Arg3 = 5; int Arg4 = 3; verify_case(0, Arg4, carrotsBetweenCarrots(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 0; int Arg1 = 0; int Arg2 = 1; int Arg3 = 1; int Arg4 = 0; verify_case(1, Arg4, carrotsBetweenCarrots(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 50; int Arg1 = 48; int Arg2 = 0; int Arg3 = 0; int Arg4 = 1; verify_case(2, Arg4, carrotsBetweenCarrots(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 0; int Arg1 = 0; int Arg2 = 42; int Arg3 = 36; int Arg4 = 5; verify_case(3, Arg4, carrotsBetweenCarrots(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE
 
}; 

// BEGIN CUT HERE 
int main() {
  DreamingAboutCarrots ___test; 
  ___test.run_test(-1);
  getchar();
} 
// END CUT HER
