// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// There are some chickens and some cows in Farmer John's yard.
// 
// 
// John's daughter Susie counted that all the animals in the yard have a total of 3 heads. 
// John's son Billy counted their legs and got a total of 8. 
// Using their answers, Farmer John easily determined that there have to be exactly 2 chickens and 1 cow.
// 
// 
// Write a method that will solve a general version of Farmer John's problem.
// You are given two ints heads and legs. Compute the number of chickens and the number of cows. Return a vector <int> 
// with two elements: first the number of chickens, then the number of cows. If there is no solution, return an empty 
// vector <int> instead.
// 
// 
// DEFINITION
// Class:OnTheFarmDivTwo
// Method:animals
// Parameters:int, int
// Returns:vector <int>
// Method signature:vector <int> animals(int heads, int legs)
// 
// 
// NOTES
// -If the solution exists, it is always unique.
// -A chicken has 1 head and 2 legs. A cow has 1 head and 4 legs.
// 
// 
// CONSTRAINTS
// -heads will be between 0 and 1,000,000, inclusive.
// -legs will be between 0 and 1,000,000, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 3
// 8
// 
// Returns: {2, 1 }
// 
// Two chickens and a cow have a total of three heads and eight legs.
// 
// 1)
// 10
// 40
// 
// Returns: {0, 10 }
// 
// Ten cows.
// 
// 2)
// 10
// 42
// 
// Returns: { }
// 
// This test case has no solution because the number of legs is too large (or the number of heads is too small).
// 
// 3)
// 1
// 3
// 
// Returns: { }
// 
// No set of animals can have one head and three legs.
// 
// 4)
// 0
// 0
// 
// Returns: {0, 0 }
// 
// END CUT HERE

#line 79 "problem.cpp"
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

class OnTheFarmDivTwo { 
  public: 
    vector <int> animals(int heads, int legs)  { 
      vector<int> r;
      if (legs & 1) return r;
      int cows = legs/2 - heads;
      if (cows < 0) return r;
      int chickens = heads - cows;
      if (chickens < 0) return r;
      r.push_back(chickens);
      r.push_back(cows);
      return r;
    } 
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); /* if ((Case == -1) || (Case == 2)) test_case_2(); */ /* if ((Case == -1) || (Case == 3)) test_case_3(); */ if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 8; int Arr2[] = {2, 1 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, animals(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 10; int Arg1 = 40; int Arr2[] = {0, 10 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, animals(Arg0, Arg1)); }
	// void test_case_2() { int Arg0 = 10; int Arg1 = 42; int Arr2[] = { }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, animals(Arg0, Arg1)); }
	// void test_case_3() { int Arg0 = 1; int Arg1 = 3; int Arr2[] = { }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, animals(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 0; int Arg1 = 0; int Arr2[] = {0, 0 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(4, Arg2, animals(Arg0, Arg1)); }

// END CUT HERE
 
}; 

// BEGIN CUT HERE 
int main() {
  OnTheFarmDivTwo ___test; 
  ___test.run_test(-1);
  getchar();
} 
// END CUT HER
