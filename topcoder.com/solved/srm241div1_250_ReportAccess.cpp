// BEGIN CUT HERE
// PROBLEM STATEMENT
// You are working on a large database that holds information about several different aspects of your company, such as 
// customers, partners, prospects, employees, products, etc.  Every user in the system has access to one or more types of 
// data.  For instance, a human resources worker might only have access to employee records, while a sales person might 
// have access to prospects, customers, and products.
// 
// You are in charge of writing reports that summarize large volumes of this information.  However, since the reports may 
// contain more than one type of data, you need to be determine which users should be allowed to view that report.  In 
// this case, assume that a user has permission to view a report if and only if they have permission to view all of the 
// types of data contained in that report.
// 
// You are given a list of usernames in vector <string> userNames.  You are given a list of what data types each user can 
// access in vector <string> allowedData, where each element of allowedData is a space-delimited list of the permitted 
// data types for that user.  Finally, you are given a vector <string> reportData, where each element of report indicates 
// a type of data included in the report.
// 
// You are to return a vector <string> indicating the user names of those users who should be able to access the report.  
// The list should be returned in alphabetical order.
// 
// 
// 
// DEFINITION
// Class:ReportAccess
// Method:whoCanSee
// Parameters:vector <string>, vector <string>, vector <string>
// Returns:vector <string>
// Method signature:vector <string> whoCanSee(vector <string> userNames, vector <string> allowedData, vector <string> 
// reportData)
// 
// 
// CONSTRAINTS
// -userNames will have between 1 and 50 elements, inclusive.
// -Each element of userNames will contain between 1 and 50 'a'-'z' characters, inclusive.
// -allowedData will contain the same number of elements as userNames.
// -Each element of allowedData will contain between 1 and 50 characters, inclusive.
// -Each element of allowedData will contain the characters 'a'-'z' or ' '.
// -reportData will contain between 1 and 5 elements, inclusive.
// -Each element of reportData will contain between 1 and 50 'a'-'z' characters, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// {"joe", "nick", "ted"}
// {"clients products", "products orders", "clients orders"}
// {"clients", "products"}
// 
// Returns: {"joe" }
// 
// Here, only joe has access to both required data types.
// 
// 1)
// {"kathy", "john", "dan", "steve", "cheryl", "tony"}
// {"users data", "data orders", "users permissions", "system users controls", "default", "admin users"}
// {"users"}
// 
// Returns: {"dan", "kathy", "steve", "tony" }
// 
// Here, we only need one type of permission to view the report.
// 
// 2)
// {"jim", "scott", "barbara"}
// {"users order products", "products shipping", "tracking products orders"}
// {"admin"}
// 
// Returns: { }
// 
// Everyone has a variety of permissions, but nobody has the proper permission.
// 
// END CUT HERE

#line 74 "problem.cpp"
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

set<string> tokenize_set(string s, string ch) {
  set<string> ret;
  for (int p = 0, p2; p < s.size(); p = p2 + 1) {
    p2 = s.find_first_of(ch, p);
    if (p2 == -1) p2 = s.size();
    if (p2 - p > 0) ret.insert(s.substr(p, p2 - p));
  }
  return ret;
}

class ReportAccess { 
  public: 
    vector <string> whoCanSee(vector <string> userNames, vector <string> allowedData, vector <string> reportData)  { 
      vector<string> r;
      for (int i = 0; i < allowedData.size(); ++i) {
        set<string> p = tokenize_set(allowedData[i], " ");
        bool all = true;
        for (int j = 0; j < reportData.size(); ++j)
          if (p.find(reportData[j]) == p.end()) {
            all = false;
            break;
          }
        if (all)
          r.push_back(userNames[i]);
      }
      sort(r.begin(), r.end());
      return r;
    } 
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {"joe", "nick", "ted"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"clients products", "products orders", "clients orders"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"clients", "products"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = {"joe" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(0, Arg3, whoCanSee(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {"kathy", "john", "dan", "steve", "cheryl", "tony"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"users data", "data orders", "users permissions", "system users controls", "default", "admin users"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"users"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = {"dan", "kathy", "steve", "tony" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(1, Arg3, whoCanSee(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"jim", "scott", "barbara"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"users order products", "products shipping", "tracking products orders"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"admin"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = { "" }; vector <string> Arg3; verify_case(2, Arg3, whoCanSee(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
}; 

// BEGIN CUT HERE 
int main() {
  ReportAccess ___test; 
  ___test.run_test(-1);
  getchar();
} 
// END CUT HER
