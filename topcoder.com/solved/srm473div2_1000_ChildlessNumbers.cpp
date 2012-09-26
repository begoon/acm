// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// Let D(X) denote the sum of digits of the positive integer X.
// For example, D(4007) = 4 + 0 + 0 + 7 = 11.
// 
// 
// 
// Take any positive integer X, and let Y = X / D(X). If Y is an integer, we say that Y is the parent of X (and that X is 
// a child of Y).
// For example, if X=12 then X / D(X) = 12 / (1+2) = 4, hence 4 is the parent of 12.
// 
// 
// 
// Note that multiple numbers can have the same parent. For example, 4 is also the parent of 36, as 36/(3+6) = 36/9 = 4.
// 
// 
// 
// We say that a number Y is childless if there is no positive integer X such that Y is the parent of X.
// 
// 
// 
// You are given two ints A and B. Find and return the count of all childless numbers that lie between A and B, inclusive.
// 
// 
// DEFINITION
// Class:ChildlessNumbers
// Method:howMany
// Parameters:int, int
// Returns:int
// Method signature:int howMany(int A, int B)
// 
// 
// CONSTRAINTS
// -A will be between 1 and 1,000,000,000, inclusive.
// -B will be between A and 1,000,000,000, inclusive.
// -B-A will be between 0 and 10,000, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 4
// 7
// 
// Returns: 0
// 
// Each of the numbers {4,5,6,7} has at least one child.
// For example, 54 / (5+4) = 6, hence 6 is not childless.
// 
// 1)
// 37
// 37
// 
// Returns: 0
// 
// E.g., 333 / (3+3+3) = 37.
// 
// 2)
// 61
// 65
// 
// Returns: 3
// 
// In this range there are three childless numbers: 62, 63, and 65.
// 
// For the other two we have 732 / (7+3+2) = 732/12 = 61 and 320 / (3+2+0) = 320/5 = 64.
// 
// 3)
// 275
// 300
// 
// Returns: 1
// 
// The only childless number in this range is 276.
// 
// END CUT HERE

#line 80 "problem.cpp"
#include <string>
#include <vector>
#include <set>
#include <functional>
#include <queue>
#include <stack>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cmath>
using namespace std;

int digits_sum(long long n) {
  int r = 0;
  while (n > 0) {
    r += n % 10;
    n /= 10;
  }
  return r;
}

class ChildlessNumbers { 
  public: 
    int howMany(int A, int B)  { 
      int r = 0;
      for (long long y = A; y <= B; ++y) {
        for (int i = 1; i <= 100; ++i) {
          long long x = y * i;
          int s = digits_sum(x);
          if (s == i) {
            r += 1;
            break;
          }
        }
      }
      return B - A + 1 - r;
    } 
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 4; int Arg1 = 7; int Arg2 = 0; verify_case(0, Arg2, howMany(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 37; int Arg1 = 37; int Arg2 = 0; verify_case(1, Arg2, howMany(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 61; int Arg1 = 65; int Arg2 = 3; verify_case(2, Arg2, howMany(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 275; int Arg1 = 300; int Arg2 = 1; verify_case(3, Arg2, howMany(Arg0, Arg1)); }

// END CUT HERE
 
}; 

// BEGIN CUT HERE 
int main() {
  ChildlessNumbers ___test; 
  ___test.run_test(-1);
  getchar();
} 
// END CUT HER
