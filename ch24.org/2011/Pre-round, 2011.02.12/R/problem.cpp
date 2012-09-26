#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <numeric>
#include <limits>
#include <algorithm>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cassert>
#ifdef _DEBUG
#include <windows.h>
#endif
using namespace std;

string toInt1(int i) {
  string r(2, 1);
  r[0] = i & 0xff;
  return r;
}

string toInt2(int i) {
  string r(2, 0);
  r[0] = i & 0xff;
  r[1] = (i >> 8) & 0xff;
  return r;
}

string toInt4(int i) {
  string r(4, 0);
  r[0] = i & 0xff;
  r[1] = (i >> 8) & 0xff;
  r[2] = (i >> 16) & 0xff;
  r[3] = (i >> 24) & 0xff;
  return r;
}

void putInt4(string& r, int offset, int i) {
  r[offset + 0] = i & 0xff;
  r[offset + 1] = (i >> 8) & 0xff;
  r[offset + 2] = (i >> 16) & 0xff;
  r[offset + 3] = (i >> 24) & 0xff;
}

float numSeconds_v[10] = {
  0.4, 0.4, 1, 0.4, 0.4, 1, 1, 1, 1, 1
};

int numSeconds_i = 0;

void solve(istream& is, ostream& os) {
  // int sampleRate = 44100;     // CD-Quality Sound.
  int bitSize = 16;              // Bit Size is 16 (CD-Quality).
  int numChannels = 1;           // Stereo mode (2-channel).
  // float numSeconds = 0.3;     // We//re going to make a 1 second sample.
  int fileSize = 0;              // Just set it to zero for now.

  string wav;

  float numSeconds = numSeconds_v[numSeconds_i++];

  int totalSamples;

  vector<double> samples;
  is >> totalSamples;
  for (int i = 0; i < totalSamples; ++i) {
    double v;
    is >> v;
    samples.push_back(v);
  }

  fileSize = 0;

  // Determine the total number of samples 
  // int totalSamples = sampleRate * numSeconds;

  int sampleRate = (float)totalSamples / numSeconds;

  // Open the file.  This will fail if the file exists.

  // Write the header
  // Put #1, 1,  "RIFF"        // RIFF marker
  wav.append("RIFF");
  // Put #1, 5,  CInt(0)       // file-size (equals file-size - 8)
  wav.append(toInt4(fileSize));
  // Put #1, 9,  "WAVE"        // Mark it as type "WAVE"
  wav.append("WAVE");
  // Put #1, 13, "fmt "        // Mark the format section.
  wav.append("fmt ");
  // Put #1, 17, CLng(16)      // Length of format data.  Always 16
  wav.append(toInt4(16));
  // Put #1, 21, CInt(1)       // Wave type PCM
  wav.append(toInt2(1));
  // Put #1, 23, CInt(1)       // 1 channels
  wav.append(toInt2(1));
  // Put #1, 25, CLng(44100)   // 44.1 kHz Sample Rate (CD-Quality)
  wav.append(toInt4(sampleRate));
  // Put #1, 29, CLng(88200)   // (Sample Rate * Bit Size * Channels) / 8
  wav.append(toInt4(sampleRate * 8 / 1 / 8));
  // Put #1, 33, CInt(1)       // (Bit Size * Channels) / 8
  wav.append(toInt2(1));
  // Put #1, 35, CInt(16)      // Bits per sample (= Bit Size * Samples)
  wav.append(toInt2(8));
  // Put #1, 37, "data"        // "data" marker
  wav.append("data");
  // Put #1, 41, CInt(0)       // data-size (equals file-size - 44).
  wav.append(toInt4(0));

  // headerLength is the length of the header.  It is used for offsetting
  // the data position.
  int headerLength = 44;

  // Populate with 0 bit data.
  // This isn't a good reference for creating PCM data.  Since we are
  // just dumping 0 bit data, we//re dumping it in 32 bit chunks.
  // For dataPos = 1 to (totalSamples * 4) step 4
  // for (int dataPos = 0; dataPos < totalSamples * 4; dataPos += 4) {
  for (int i = 0; i < totalSamples; ++i) {
    double f = (samples[i] + 1) / 2.0 * 256;
    unsigned int v = f;
  
    wav.append(toInt1(v));

    // We//re doing 16-bit, so we need to write 2 bytes per channel.
    // Write both channels using a 32 bit integer.
    // Again, this isn//t a good reference.  Ignore this data writing
    // process.  It//s useless for anything but 0 bit data.
    // Put #1, dataPos + headerLength, CInt(0)  
   // Next
  }
  // Finalize the file.  Write the file size to the header.
  // fileSize = LOF(1)               // Get the actual file size.
  fileSize = wav.size();
  // Put #1, 5, CLng(fileSize - 8)   // Set first file size marker.
  putInt4(wav, 4, fileSize - 8);
  // Put #1, 41, CLng(fileSize - 44) // Set data size marker.
  putInt4(wav, 40, fileSize - 44);
  // Close #1 // Close the file.
  // End Sub

  static int nn = 1;
  ostringstream fmt;
  fmt << "test-" << nn + 10 << ".wav";
  nn += 1;
  ofstream f(fmt.str().c_str(), ios::binary|ios::out);
  f.write(wav.data(), wav.size());
  f.close();
}

#ifdef int
#undef int
#endif

#include <ctime>

void run(const string& test_name, const char* input, const char* output) {
  const char* liner = "--------";
  stringstream is(input);
  stringstream os;
  clock_t started = clock();
  solve(is, os);
  clock_t elapsed = clock() - started;
  if (os.str() != output) {
    cerr << "Case '" << test_name << "': FAILED" << endl;
    cerr << liner << "EXPECTED" << liner << endl << output;
    cerr << liner << "-ACTUAL-" << liner << endl << os.str() 
         << liner << liner << liner << endl;
  } else {
    cerr << "Case '" << test_name << "': OK";
    if (elapsed > CLOCKS_PER_SEC / 200)
      cerr << " time " << elapsed * (1.0/CLOCKS_PER_SEC) << "s";
    cerr << endl;
  }
}

void run_test(const string& test_name) {
  ifstream test(test_name.c_str(), ifstream::in);
  string input, output;
  string line;
  while (getline(test, line)) {
    if (line.substr(0, 5) == "~~~~~") {
      test >> ws;
      while (getline(test, line) && !line.empty())
        output += line + "\n";
    } else {
      input += line + "\n";
    }
  }
  run(test_name, input.c_str(), output.c_str());
}

int main(int argc, char* argv[]) {
#ifdef TESTING_

  string test_name; // = "test0.tst";

  if (!test_name.empty()) {
    run_test(test_name);  
  } else {
    if (system("cmd /c dir /on /b *.tst >tests.lst")) {
      cerr << "error: unable to find tests" << endl;
      exit(1);
    }
    ifstream tests("tests.lst", ifstream::in);

    while (tests >> test_name) {
      if (test_name.empty()) continue;
      run_test(test_name);
    }
  }

#else

  ifstream is("input.txt");
  ofstream os("output.txt");

  // istream& is = cin;
  // ostream& os = cout;
  
  solve(is, os);

#endif

#ifdef _DEBUG
  getchar();
#endif

  return 0;
}
