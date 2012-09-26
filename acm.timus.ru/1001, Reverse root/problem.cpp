#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
  double a;
  vector<double> v;
  while (cin >> a) v.push_back(sqrt(a));
  for (int i = v.size() - 1; i >= 0; --i)
    printf("%.4Lf\n", v[i]);
  return 0;
}


