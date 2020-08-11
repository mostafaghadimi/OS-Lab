#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main () {
  string line;
  ifstream myfile ("/proc/cpuinfo");
  if (myfile.is_open()) {
    while ( getline (myfile,line) ) {
      if(line.find("model name") != std::string::npos 
      || line.find("cpu MHz") != std::string::npos || 
      line.find("cache size") !=std::string::npos) 
      cout << line << '\n';
    }
    myfile.close();
  }

  else cout << "Unable to open file"; 

  return 0;
}
