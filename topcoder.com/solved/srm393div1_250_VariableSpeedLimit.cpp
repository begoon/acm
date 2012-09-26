// BEGIN CUT HERE
// PROBLEM STATEMENT
// In order to make its roads safer, the government of a particular country has decided to introduce a speed limit that 
// varies throughout the day. At busy times, the speed limit will decrease to reduce the risk of a dangerous accident. 
// You need to drive a distance of journeyLength units and want to know how long it will take you.
// You are given details of the speed limit in a vector <int> speedLimit. Element i (zero-based) gives the speed limit in 
// DISTANCE UNITS/TIME UNITS that is in force between times T = i and T = i + 1. speedLimit describes the speed limit for 
// a full day, so after this the pattern repeats (i.e., if N is the number of elements in speedLimit, the speed limit 
// between times N and N+1  is given by speedLimit[0], etc.). You start your journey at time T = 0 and should assume that 
// you travel exactly at the speed limit for your entire journey. Return a double containing the amount of time it takes 
// to complete your journey.
// 
// DEFINITION
// Class:VariableSpeedLimit
// Method:journeyTime
// Parameters:int, vector <int>
// Returns:double
// Method signature:double journeyTime(int journeyLength, vector <int> speedLimit)
// 
// 
// NOTES
// -Your return value must be accurate to an absolute or relative tolerance of 1E-9.
// 
// 
// CONSTRAINTS
// -journeyLength will be between 1 and 100000 (10^5), inclusive.
// -speedLimit will contain between 1 and 50 elements, inclusive.
// -Each element of speedLimit will be between 1 and 100, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 100
// {50}
// 
// Returns: 2.0
// 
// Here the speed limit doesn't change. The journey therefore takes a time of DISTANCE/SPEED = 100/50 = 2 time units.
// 
// 1)
// 100
// {50,25}
// 
// Returns: 2.5
// 
// Now the speed limit drops to 25 every other time unit. You drive 50 units in the first time unit and 25 in the second. 
// You reach the end of your journey halfway through the third time unit.
// 
// 2)
// 1000
// {50,40,30,40,50}
// 
// Returns: 24.0
// 
// 
// 
// 3)
// 2058
// {80,43,57,23,28,45,60,75,73,80}
// 
// Returns: 37.4
// 
// 
// 
// 4)
// 17216
// {26,30,62,55,51,56,58,4,60,23,31}
// 
// Returns: 415.03333333333336
// 
// 5)
// 9839
// {45,90,13,4,81,50,81,10,64,86,69}
// 
// Returns: 182.8395061728395
// 
// END CUT HERE

#line 81 "problem.cpp"
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

class VariableSpeedLimit { 
  public: 
    double journeyTime(int journeyLength, vector <int> speedLimit)  { 
      int t = 0;
      int i = 0; 
      while (journeyLength - speedLimit[i] >= 0) {
        journeyLength -= speedLimit[i];
        t += 1;
        i += 1;
        i %= speedLimit.size();
      }
      double r = (double)t + (double)journeyLength/speedLimit[i];
      return r;
    } 
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 100; int Arr1[] = {50}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 2.0; verify_case(0, Arg2, journeyTime(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 100; int Arr1[] = {50,25}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 2.5; verify_case(1, Arg2, journeyTime(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 1000; int Arr1[] = {50,40,30,40,50}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 24.0; verify_case(2, Arg2, journeyTime(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 2058; int Arr1[] = {80,43,57,23,28,45,60,75,73,80}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 37.4; verify_case(3, Arg2, journeyTime(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 17216; int Arr1[] = {26,30,62,55,51,56,58,4,60,23,31}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 415.03333333333336; verify_case(4, Arg2, journeyTime(Arg0, Arg1)); }
	void test_case_5() { int Arg0 = 9839; int Arr1[] = {45,90,13,4,81,50,81,10,64,86,69}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 182.8395061728395; verify_case(5, Arg2, journeyTime(Arg0, Arg1)); }

// END CUT HERE
 
}; 

// BEGIN CUT HERE 
int main() {
  VariableSpeedLimit ___test; 
  ___test.run_test(-1);
  getchar();
} 
// END CUT HER
