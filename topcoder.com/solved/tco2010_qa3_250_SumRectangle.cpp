// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// A sum rectangle is a rectangle divided into a grid of unit squares.
// Each square contains a number, and the numbers in neighboring squares always satisfy the following property:
// 
// 
// 
// The number in any square S that is neither in the bottom row nor in the right column
// can be computed as the sum of the following three numbers:
// 
// 
// The number in the square directly below S.
// The number in the square directly to the right of S.
// The number in the other square adjacent to the previous two squares (the one diagonally down and to the right of S).
// 
// 
// 
// An example of a correctly filled sum rectangle:
// 
// 
// +----+----+----+----+----+
// | 88 | 57 | 33 | 10 |  5 |
// +----+----+----+----+----+
// | 18 | 13 | 11 | 12 | -7 |
// +----+----+----+----+----+
// |  1 |  4 | -2 |  1 | 18 |
// +----+----+----+----+----+
// 
// 
// For example, in the top left corner we have 88 = 18 + 57 + 13.
// 
// 
// We have a secret sum rectangle.
// You will be given a vector <int> leftColumn containing the leftmost number in each row of our rectangle, from the top 
// to the bottom.
// You will also be given an vector <int> topRow containing the topmost number in each column of our rectangle, from the 
// left to the right.
// Compute and return the number in the bottom right corner. If the input is such that this number cannot be determined 
// uniquely, return 0 instead.
// 
// 
// DEFINITION
// Class:SumRectangle
// Method:getCorner
// Parameters:vector <int>, vector <int>
// Returns:int
// Method signature:int getCorner(vector <int> leftColumn, vector <int> topRow)
// 
// 
// NOTES
// -You may assume that the return value will always fit into an int (i.e., a 32-bit signed integer data type).
// 
// 
// CONSTRAINTS
// -leftColumn will contain between 1 and 10 elements, inclusive.
// -Each element of leftColumn will be between 0 and 100, inclusive.
// -topRow will contain between 1 and 10 elements, inclusive.
// -Each element of topRow will be between 0 and 100, inclusive.
// -Element 0 of leftColumn will be equal to element 0 of topRow.
// 
// 
// EXAMPLES
// 
// 0)
// {88,18,1}
// {88,57,33,10,5}
// 
// Returns: 18
// 
// This is the rectangle from the problem statement. The lower right corner is uniquely determined by the left column and 
// the top row.
// 
// 1)
// {0,0,0,0}
// {0,0,0,0}
// 
// Returns: 0
// 
// The only correct way to fill this rectangle is to place a zero into each square.
// 
// 2)
// {6,1}
// {6,2}
// 
// Returns: 3
// 
// This is the smallest non-trivial case:
// 
// +----+----+
// |  6 |  2 |
// +----+----+
// |  1 | ?? |
// +----+----+
// 
// 
// END CUT HERE

#line 100 "problem.cpp"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cmath>
using namespace std;

class SumRectangle { 
  public: 
    int getCorner(vector <int> leftColumn, vector <int> topRow)  { 
      int w = topRow.size();
      int h = leftColumn.size();
      vector<vector<int> > m(h, vector<int>(w, 0));
      for (int i = 0; i < w; ++i) m[0][i] = topRow[i];
      for (int i = 0; i < h; ++i) m[i][0] = leftColumn[i];
      for (int x = 1; x < w; ++x) {
        for (int y = 1; y < h; ++y) {
          m[y][x] = m[y-1][x-1] - m[y-1][x] - m[y][x-1];
        }
      }
      return m[h-1][w-1];
      // $CARETPOSITION$ 
    } 
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {88,18,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {88,57,33,10,5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 18; verify_case(0, Arg2, getCorner(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {0,0,0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0,0,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(1, Arg2, getCorner(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {6,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {6,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(2, Arg2, getCorner(Arg0, Arg1)); }

// END CUT HERE
 
}; 

// BEGIN CUT HERE 
int main() {
  SumRectangle ___test; 
  ___test.run_test(-1);
  getchar();
} 
// END CUT HER
