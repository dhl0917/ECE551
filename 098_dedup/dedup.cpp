//#include <io.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
class HashMap
{
 private:
  std::vector<std::string> * table;
  size_t bucketSize;
  size_t elementNum;
  // double loadFactor;

 public:
  HashMap() : table(new std::vector<std::string>(20)), bucketSize(20), elementNum(0) {}
  double getLoadFactor() { return elementNum / ((1.0) * bucketSize); }
  void rehash(){
      //    std::cout << "need rehash" << std::endl;
      // exit(EXIT_FAILURE);
  };
  void add(std::string filename) {
    std::string line;
    std::ifstream s;
    std::hash<std::string> myHash;
    size_t index = 0;
    size_t counter = 0;
    size_t primeArray[10] = {3, 7, 13, 29, 61, 127, 251, 499, 997, 2003};
    s.open(filename);
    if (!s) {
      std::cerr << "Fail to open " << filename << std::endl;
      exit(EXIT_FAILURE);
    }
    while (std::getline(s, line)) {
      size_t hashValue = myHash(line);
      // hashValue = hashValue % bucketSize;
      index = index * primeArray[counter % 10] + hashValue;
      counter += 1;
    }
    index = index % bucketSize;
    if ((*table)[index].size() == 0) {
      (*table)[index] = filename;
      elementNum += 1;
      if (getLoadFactor() > 0.8) {
        //std::cout << getLoadFactor() << std::endl;
        rehash();  //not implemented yet!
      }
    }
    else {
      std::cout << "#Removing " << filename << "(duplicate of" << std::endl
                << (*table)[index] << ")." << std::endl
                << std::endl;
      std::cout << "rm " << filename << std::endl << std::endl;
    }
    s.close();
  }
  ~HashMap() { delete table; }
};

void readDir(char * basePath, HashMap & myHashMap) {
  DIR * dir;
  struct dirent * ptr;
  // int i = 0;
  char base[512];

  // pDir = opendir(path);
  // memset(base, '\0', sizeof(base));
  if ((dir = opendir(basePath)) == NULL) {
    std::cerr << "Open dir" << basePath << " error" << std::endl;
    exit(EXIT_FAILURE);
  }
  while ((ptr = readdir(dir)) != NULL) {
    if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0) {
      continue;
    }
    //file
    else if (ptr->d_type == 8) {
      myHashMap.add(std::string(basePath) + std::string(ptr->d_name));
    }
    //dir
    else if (ptr->d_type == 4) {
      memset(base, '\0', sizeof(base));
      strcpy(base, basePath);
      strcat(base, "/");
      // strcat(base, ptr->d_name);

      strcat(base, (std::string(basePath) + std::string("/") + std::string(ptr->d_name)).c_str());
      readDir(base, myHashMap);
    }
  }
  closedir(dir);
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    std::cerr << "Not enough arguments!\n" << std::endl;
    exit(EXIT_FAILURE);
  }
  /*
  std::vector<std::string> v;
  for (int i = 1; i < argc; i++) {
    v.push_back(argv[i]);
  }
  */
  /*
  std::string s("This is a test string");
  std::hash<std::string> myHash;
  size_t hashValue = myHash(s);
  std::cout << hashValue << std::endl;
  std::pair<std::string, size_t> p(s, hashValue);
  std::cout << p.first << std::endl;
  std::cout << p.second << std::endl;
  std::string ss("This is a test string");
  size_t hashValue2 = myHash(ss);
  if (hashValue == hashValue2) {
    std::cout << "rm ss" << std::endl;
  }
  */
  HashMap myHashMap;
  for (int i = 1; i < argc; i++) {
    readDir(argv[i], myHashMap);
  }

  return EXIT_SUCCESS;
}
