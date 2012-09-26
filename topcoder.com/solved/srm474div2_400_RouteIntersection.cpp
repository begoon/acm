// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// Little Dazdraperma likes to travel a lot. One day she made a route in an N-dimensional space. In this space each point 
// is represented by N coordinates. The coordinates are indexed from 1 to N, inclusive. She started from the origin, i.
// e., a point where each coordinate is 0. Then she did several moves of the following type:
// 
//  First she chose a coordinate index, i.e., a number between 1 and N, inclusive.
//  Then she jumped to a point where the coordinate with the chosen index is either increased or decreased by 1 and all 
// other coordinates remain the same.
// 
// Now Dazdraperma wonders whether she has ever visited the same point twice. You will be given a vector <int> coords and 
// a string moves representing her route. The i-th element of coords is the coordinate index she has chosen during her i-
// th move. If the coordinate with this index was increased during the i-th move, the i-th character of moves will be 
// '+', and it will be '-' if this coordinate was decreased.
// 
// 
// Return "VALID" if all points of her route were unique, including the first and the last points, and return "NOT VALID" 
// otherwise. Two points A and B in N-dimensional space are different if there's an index i such that A's coordinate with 
// index i and B's coordinate with index i are different.
// 
// DEFINITION
// Class:RouteIntersection
// Method:isValid
// Parameters:int, vector <int>, string
// Returns:string
// Method signature:string isValid(int N, vector <int> coords, string moves)
// 
// 
// CONSTRAINTS
// -N will be between 1 and 1000000000 (109), inclusive.
// -coords will contain between 1 and 50 elements, inclusive.
// -Each element of coords will be between 1 and N, inclusive.
// -moves will contain the same number of characters as the number of elements in coords.
// -Each character in moves will be either '+' or '-'.
// 
// 
// EXAMPLES
// 
// 0)
// 1
// {1}
// "+"
// 
// Returns: "VALID"
// 
// Dazdraperma starts at (0) and then jumps to (1). The answer is "VALID".
// 
// 1)
// 2
// {1,2,1,2}
// "++--"
// 
// Returns: "NOT VALID"
// 
// The route goes through 5 points:
// (0,0) -> (1,0) -> (1,1) -> (0,1) -> (0,0). The point (0,0) was visited twice.
// 
// 2)
// 3
// {1,2,3,1,2}
// "+++--"
// 
// Returns: "VALID"
// 
// (0,0,0) -> (1,0,0) -> (1,1,0) -> (1,1,1) -> (0,1,1) -> (0,0,1).
// 
// 3)
// 344447
// {132,51717,628,344447,628,51717,344447,2}
// "+-++-+--"
// 
// Returns: "NOT VALID"
// 
// The repeated point doesn't have to be the first or the last point in the route.
// 
// 4)
// 1
// {1,1}
// "+-"
// 
// Returns: "NOT VALID"
// 
// 
// 
// 5)
// 990630
// {833196,524568,361663,108056,28026,824639,269315,440977,440977,765458,
// 988451,242440,948414,130873,773990,765458,130873,28026,853121,553636,
// 581069,82254,735536,833196,898562,898562,940783,988451,540613,317306,
// 623194,940783,571384,988451,108056,514374,97664}
// "--+---+-+++-+-+---++-++-+---+-+--+-++"
// 
// Returns: "NOT VALID"
// 
// 
// 
// END CUT HERE

#line 101 "problem.cpp"
#include <string>
#include <vector>
#include <set>
#include <functional>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cmath>
using namespace std;

class RouteIntersection { 
  public: 
    string isValid(int N, vector <int> coords, string moves)  { 
      vector< map<int, int> > m(coords.size() + 1);
      m[0] = map<int, int>();
      for (int i = 1; i < coords.size() + 1; ++i) {
         m[i] = m[i - 1];
        int a = m[i][coords[i-1] - 1];
        a = a + (moves[i-1] == '+' ? 1 : -1);
        m[i][coords[i-1] - 1] = a;
        for (int j = 0; j < i; ++j) {
          bool match = true;
          for (map<int, int>::iterator x = m[i].begin(); x != m[i].end(); ++x) {
            if (x->second != m[j][x->first]) {
              match = false;
              break;
            } 
          }
          if (match)
            return "NOT VALID";
        }
      }
      return "VALID";
    } 
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arr1[] = {1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "+"; string Arg3 = "VALID"; verify_case(0, Arg3, isValid(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 2; int Arr1[] = {1,2,1,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "++--"; string Arg3 = "NOT VALID"; verify_case(1, Arg3, isValid(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 3; int Arr1[] = {1,2,3,1,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "+++--"; string Arg3 = "VALID"; verify_case(2, Arg3, isValid(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 344447; int Arr1[] = {132,51717,628,344447,628,51717,344447,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "+-++-+--"; string Arg3 = "NOT VALID"; verify_case(3, Arg3, isValid(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 1; int Arr1[] = {1,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "+-"; string Arg3 = "NOT VALID"; verify_case(4, Arg3, isValid(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arg0 = 990630; int Arr1[] = {833196,524568,361663,108056,28026,824639,269315,440977,440977,765458,
988451,242440,948414,130873,773990,765458,130873,28026,853121,553636,
581069,82254,735536,833196,898562,898562,940783,988451,540613,317306,
623194,940783,571384,988451,108056,514374,97664}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "--+---+-+++-+-+---++-++-+---+-+--+-++"; string Arg3 = "NOT VALID"; verify_case(5, Arg3, isValid(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
}; 

// BEGIN CUT HERE 
int main() {
  RouteIntersection ___test; 
  ___test.run_test(-1);
  getchar();
} 
// END CUT HER
