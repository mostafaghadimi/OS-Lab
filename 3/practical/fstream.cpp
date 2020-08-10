#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
  string version;
  ifstream f;
  f.open("/proc/version", ios::in);
  getline(f, version);
  f.close();
  ofstream of;
  of.open("linux_version.txt", ios::out);
  of << version;
  of.close();
  return 0;
}
