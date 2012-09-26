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

int nb_bits(int n) {
  int r = 0;
  while (n) {
    n &= (n - 1);
    ++r;
  }
  return r;
}

double game(string f, int r) {
  int n = f.length();

  vector<int> p(n);
  for (int i = 0; i < r; i++) p[p.size() - i - 1] = 1;
  int remain = 0;
  int iter = 0;
  do {
    vector<int> h(r);
    vector<int> g;
    for (int i = 0; i < p.size(); ++i) if (p[i]) g.push_back(i);
    int alive = (1 << r) - 1;
    for (int t = n; t > 2; --t) {
      for (int i = 0; i < r; ++i) if (alive && (1 << i)) { 
        int prev = g[i];
        if (g[i] == 0)
          g[i] += 1;
        else if (g[i] == t - 1 || g[i] == t - 2)
          g[i] -= 1;
        else {
          if (f[g[i]] == 'W')
            g[i] -= 1;
          else if (f[g[i]] == 'B')
            g[i] += 1;
          else {
            if (t == n)
              g[i] -= 1;
            else
              g[i] = h[i];
          }
        }
        h[i] = prev;
      }

      for (int i = 0; i < r; ++i) if (alive & (1 << i))
        for (int j = i + 1; j < r; ++j) if (alive & (1 << j))
          if (g[i] == g[j]) {
            alive &= ~(1 << i);
            alive &= ~(1 << j);
          }
    }

    remain += nb_bits(alive);
    iter += 1;
  } while (next_permutation(p.begin(), p.end()));

  return (double)remain / iter;
}

class RabbitStepping { 
  public: 
    double getExpected(string field, int r)  { 
      return game(field, r);
    } 
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "WRBRW"; int Arg1 = 4; double Arg2 = 0.8; verify_case(0, Arg2, getExpected(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "WWB"; int Arg1 = 2; double Arg2 = 1.3333333333333333; verify_case(1, Arg2, getExpected(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "WW"; int Arg1 = 1; double Arg2 = 1.0; verify_case(2, Arg2, getExpected(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "BBBBBBBBBB"; int Arg1 = 4; double Arg2 = 0.9523809523809523; verify_case(3, Arg2, getExpected(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "RRBRRWRRBRRW"; int Arg1 = 8; double Arg2 = 0.9696969696969697; verify_case(4, Arg2, getExpected(Arg0, Arg1)); }

// END CUT HERE
 
}; 

// BEGIN CUT HERE 
int main() {
  RabbitStepping ___test; 
  ___test.run_test(-1);
  getchar();
} 
// END CUT HER
