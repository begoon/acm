#include <iostream>
using namespace std;
int main() {
  int r = 0;
  for (int i = 1; i < 1000; ++i)
    if ((i % 3) == 0 || (i % 5) == 0)
      r += i;
  cout << r << endl;
  return 0;
}

