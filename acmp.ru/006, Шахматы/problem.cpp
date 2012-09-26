#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
  ifstream is("INPUT.TXT");
  ofstream os("OUTPUT.TXT");
  string a;
  getline(is, a);

  if (a.length() < 5 || a[2] != '-' ||
      a[0] < 'A' || a[0] > 'H' || a[3] < 'A' || a[3] > 'H' ||
      a[1] < '1' || a[1] > '8' || a[4] < '1' || a[4] > '8')
    os << "ERROR" << endl;
  else if (abs((a[0] - a[3]) * (a[1] - a[4])) != 2)
    os << "NO" << endl;
  else
    os << "YES" << endl;
    
  return 0;
}
