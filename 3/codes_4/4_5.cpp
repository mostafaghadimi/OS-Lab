#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main () {
  string line;
  ifstream myfile ("/proc/meminfo");
  if (myfile.is_open()) {
    while ( getline (myfile,line) ) {
      if(line.find("MemTotal") != std::string::npos 
      || line.find("MemFree") != std::string::npos || 
      line.find("MemAvailable") !=std::string::npos) 
      cout << line << '\n';
    }
    myfile.close();
  }

  else cout << "Unable to open file"; 

  return 0;
}
