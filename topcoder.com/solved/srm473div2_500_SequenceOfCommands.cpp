// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// You are standing on some arbitrary point in the infinite plane.
// 
// 
// You are given a vector <string> commands that contains the commands you have to execute.
// Each character of each element of commands is one command.
// The commands must be executed in the given order: first you execute all commands in the first element of commands one 
// by one, 
// then those in the second element, etc.
// 
// 
// There are only three types of commands: 'S' means "step forward", 'L' means "turn 90 degrees to the left", and 'R' 
// means "turn 90 degrees to the right". All your steps have the same length.
// 
// 
// You will be executing the commands forever: after you execute the last character of the last element of commands, you 
// will always start from the beginning again.
// 
// 
// We say that your path is bounded if there is some positive real number R such that while executing the infinite 
// sequence of steps you will never leave the circle with radius R steps and center at your starting location.
// 
// 
// Given the vector <string> commands, your method should determine whether your path will be bounded or not. Return the 
// string "bounded" (quotes for clarity) if the path is bounded and "unbounded" if it is not.
// 
// 
// DEFINITION
// Class:SequenceOfCommands
// Method:whatHappens
// Parameters:vector <string>
// Returns:string
// Method signature:string whatHappens(vector <string> commands)
// 
// 
// CONSTRAINTS
// -commands will contain between 1 and 50 elements, inclusive.
// -Each element in commands will contain between 1 and 50 characters, inclusive.
// -Each character in each element of commands will be one of 'S', 'L', and 'R'.
// 
// 
// EXAMPLES
// 
// 0)
// {"L"}
// 
// Returns: "bounded"
// 
// You are standing on the same spot forever, and in each step you take a turn 90 degrees to the left. This path is 
// clearly bounded.
// 
// 1)
// {"SRSL"}
// 
// Returns: "unbounded"
// 
// 
// Imagine that you start executing the commands facing to the north. While following this sequence you will repeatedly 
// execute the following steps: make a step to the north, rotate right, make a step to the east, and rotate left (to face 
// north again).
// 
// 
// Given enough time, this path will take you arbitrarily far away from the spot where you started, hence it is unbounded.
// 
// 
// 2)
// {"SSSS","R"}
// 
// Returns: "bounded"
// 
// While executing this sequence of commands, you will be walking along the boundary of a small square.
// 
// 3)
// {"SRSL","LLSSSSSSL","SSSSSS","L"}
// 
// Returns: "unbounded"
// 
// 
// 
// END CUT HERE

#line 85 "problem.cpp"
#include <string>
#include <vector>
#include <set>
#include <functional>
#include <queue>
#include <stack>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <cmath>
using namespace std;

class SequenceOfCommands { 
  public: 
    string whatHappens(vector <string> commands)  { 
      string p = accumulate(commands.begin(), commands.end(), string());
      int dx[4] = { 0, 1, 0, -1 };
      int dy[4] = { 1, 0, -1, 0 };
      int d = 0;
      int x = 0, y = 0;
      for (int t = 0; t < 4; ++t) {
        for (int i = 0; i < p.size(); ++i) {
          if (p[i] == 'S') {
            x += dx[d];
            y += dy[d];
          } else if (p[i] == 'R')
            d = (d + 1) % 4;
          else
            d = (d + 4 - 1) % 4;
        }
      }
      return x == 0 && y == 0 ? "bounded" : "unbounded";
    } 
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"L"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "bounded"; verify_case(0, Arg1, whatHappens(Arg0)); }
	void test_case_1() { string Arr0[] = {"SRSL"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "unbounded"; verify_case(1, Arg1, whatHappens(Arg0)); }
	void test_case_2() { string Arr0[] = {"SSSS","R"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "bounded"; verify_case(2, Arg1, whatHappens(Arg0)); }
	void test_case_3() { string Arr0[] = {"SRSL","LLSSSSSSL","SSSSSS","L"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "unbounded"; verify_case(3, Arg1, whatHappens(Arg0)); }

// END CUT HERE
 
}; 

// BEGIN CUT HERE 
int main() {
  SequenceOfCommands ___test; 
  ___test.run_test(-1);
  getchar();
} 
// END CUT HER
