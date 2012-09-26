#include <iostream>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
  double f = 1.15;
  int a = f * 100.0 + 0.1E-9;
  int b = f * 100.0;
  cout << "a = " << a << endl;
  cout << "b = " << b << endl;
  return 0;
}
