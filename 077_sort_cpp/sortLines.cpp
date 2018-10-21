#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

std::ostream & operator<<(std::ostream & s, std::vector<std::string> & v) {
  for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); ++it) {
    s << *it << std::endl;
  }
  return s;
}

std::vector<std::string> * readFromStd() {
  std::string line;
  std::vector<std::string> * pointToVector = new std::vector<std::string>;
  while (std::getline(std::cin, line)) {
    (*pointToVector).push_back(line);
  }
  return pointToVector;
}
std::vector<std::string> * readFromFile(char * filename) {
  std::string line;
  std::vector<std::string> * pointToVector = new std::vector<std::string>;
  std::ifstream s;
  s.open(filename);
  if (!s) {
    std::cout << "Fail to open " << filename;
    exit(EXIT_FAILURE);
  }
  while (std::getline(s, line)) {
    pointToVector->push_back(line);
  }
  s.close();
  return pointToVector;
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    std::vector<std::string> * pointTolines = readFromStd();
    std::sort(pointTolines->begin(), pointTolines->end());
    std::cout << *pointTolines;
    delete pointTolines;
  }
  else {
    for (int i = 1; i < argc; i++) {
      std::vector<std::string> * pointTolines = readFromFile(argv[i]);
      std::sort(pointTolines->begin(), pointTolines->end());
      std::cout << *pointTolines;
      delete pointTolines;
    }
  }
  return EXIT_SUCCESS;
}
