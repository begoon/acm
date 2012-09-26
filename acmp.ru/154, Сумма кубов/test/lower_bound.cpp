#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
  int a[] = { 1, 3, 5, 6, 9 };
  assert(lower_bound(a, a + 5, 9) - a < 5);
  cout << *lower_bound(a, a + 5, 10) << endl;
  return 0;
}
