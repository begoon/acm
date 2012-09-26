// BEGIN CUT HERE
// PROBLEM STATEMENT
// Rabbits often feel lonely, so one group of rabbits decided to gather together and play a game. 
// 
// The game is played on a horizontal row of N cells (N >= 2), numbered 0 to N - 1 from left to right. 
// Each cell is colored white, black or red. 
// You are given a string field of length N, 
// where the i-th character is the color of cell i ('W' for white, 'B' for black and 'R' for red). 
// 
// There are r rabbits playing the game. 
// The rabbits choose their starting cells randomly such that no two rabbits are on the same cell. 
// Each subset of r distinct cells has the same probability of being chosen as their starting cells. 
// The size of the field is the number of cells it contains (which is initially N). 
// The following is repeated while the size of the field is greater than 2: 
// 
// 
// 	Each rabbit steps onto a neighboring cell. 
// 	Since each cell potentially has up to two neighboring cells, 
// 	the following rules are used to determine which cell the rabbit will choose: 
// 	
// 		If a rabbit is on cell 0, she must step onto cell 1. 
// 		If a rabbit is on cell size - 1 or size - 2, she must step onto the left neighboring cell. 
// 		All other rabbits choose which neighboring cell to step onto according to the color of the cell they are currently 
// on: 
// 		
// 			White: She must step onto the left neighboring cell. 
// 			Black: She must step onto the right neighboring cell. 
// 			Red: If this is her first move, she must step onto the left neighboring cell. 
// 			Otherwise, she must return to the cell she was on immediately before she was on the current cell. 
// 		
// 		
// 	
// 	
// 	After all rabbits finished their steps, for each cell that contains more than one rabbit, all rabbits on that cell 
// will be removed from the field. 
// 	The rightmost cell will disappear (causing the size of the field to decrease by 1). 
// 	By the rules above, this cell will always be empty. 
// 
// 
// When the game ends, 0, 1 or 2 rabbits will remain on the field. 
// Return the expected number of rabbits left on the field when the game ends. 
// 
// 
// 
// DEFINITION
// Class:RabbitStepping
// Method:getExpected
// Parameters:string, int
// Returns:double
// Method signature:double getExpected(string field, int r)
// 
// 
// NOTES
// -The returned value must have an absolute or relative error less than 1e-9. 
// 
// 
// CONSTRAINTS
// -field will contain between 2 and 17 characters, inclusive. 
// -Each character in field will be either 'W', 'B', or 'R'. 
// -r will be between 1 and N, inclusive, where N is the number of characters in field. 
// 
// 
// EXAMPLES
// 
// 0)
// "WRBRW"
// 4
// 
// Returns: 0.8
// 
// The initial positions of the rabbits are cells 
// { 0, 1, 2, 3 }, { 0, 1, 2, 4 }, { 0, 1, 3, 4 }, { 0, 2, 3, 4 }, or { 1, 2, 3, 4 }. 
// For example, if { 0, 1, 2, 4 } is chosen, 
// they will step as follows and 2 rabbits will remain on the field: 
// 
// 
// 
// 
// 1)
// "WWB"
// 2
// 
// Returns: 1.3333333333333333
// 
// 2)
// "WW"
// 1
// 
// Returns: 1.0
// 
// No moves will be performed, and one rabbit will remain alone on the field. 
// 
// 
// 3)
// "BBBBBBBBBB"
// 4
// 
// Returns: 0.9523809523809523
// 
// 4)
// "RRBRRWRRBRRW"
// 8
// 
// Returns: 0.9696969696969697
// 
// END CUT HERE

#line 109 "problem.cpp"
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <stack>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <functional>
#include <numeric>
#include <cmath>
using namespace std;

// The last value is C(30, 61)
long long C(int m, int n) {
  long long p = 1;
  for (int i = 1; i <= m; i++) {
    p *= n - i + 1;
    p /= i;
  }
  return p;
}

class RabbitStepping { 
  public: 
    double getExpected(string field, int r)  {
      if (r & 1) return 1.0;
      int n = field.length();
      int from = max(1, r - n/2 - 1) | 1;
      int to = min(r, n/2);
      int total = C(r, n);
      int v = 0;
      for (int i = from; i <= to; i += 2) {
        v += C(i, n/2) * C(r - i, n - n/2);
      }
      return 2.0 * v / total;
    } 
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4();  if ((Case == -1) || (Case == 5)) test_case_5();}
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "WRBRW"; int Arg1 = 4; double Arg2 = 0.8; verify_case(0, Arg2, getExpected(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "WWB"; int Arg1 = 2; double Arg2 = 1.3333333333333333; verify_case(1, Arg2, getExpected(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "WW"; int Arg1 = 1; double Arg2 = 1.0; verify_case(2, Arg2, getExpected(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "BBBBBBBBBB"; int Arg1 = 4; double Arg2 = 0.9523809523809523; verify_case(3, Arg2, getExpected(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "RRBRRWRRBRRW"; int Arg1 = 8; double Arg2 = 0.9696969696969697; verify_case(4, Arg2, getExpected(Arg0, Arg1)); }
	void test_case_5() { string Arg0 = "WRRRBW"; int Arg1 = 6; double Arg2 = 2.0; verify_case(5, Arg2, getExpected(Arg0, Arg1)); }

// END CUT HERE
 
}; 

// BEGIN CUT HERE 
int main() {
  RabbitStepping ___test; 
  ___test.run_test(-1);
  getchar();
} 
// END CUT HER
