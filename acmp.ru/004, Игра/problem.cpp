#include <fstream>
using namespace std;

int main(int argc, char* argv[]) {
  ifstream is("INPUT.TXT");
  ofstream os("OUTPUT.TXT");
  int a;
  is >> a;
  os << a << 9 << 9-a << endl;
  return 0;
}
