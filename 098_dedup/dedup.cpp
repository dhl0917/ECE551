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
#include <unordered_map>
#include <vector>
class HashMap
{
 private:
  std::vector<std::string> * table;
  size_t bucketSize;
  size_t elementNum;
  // double loadFactor;
  std::unordered_map<std::string, std::string> myDic;

 public:
  HashMap() {}
  ~HashMap() {}
  //Old constructor
  // HashMap() : table(new std::vector<std::string>(997)), bucketSize(997), elementNum(0) {}
  // ~HashMap() { delete table; }
  double getLoadFactor() { return elementNum / ((1.0) * bucketSize); }
  void rehash() {
    //    std::cout << "need rehash" << std::endl;
    // exit(EXIT_FAILURE);
    size_t n = bucketSize;
    std::vector<std::string> * temp = new std::vector<std::string>(bucketSize * 2 + 1);
    for (size_t i = 0; i < n; i++) {
      if ((*table)[i].size() != 0) {
        std::string filename = (*table)[i];
        std::string line;
        std::string passage;
        std::ifstream s;
        //        std::hash<std::string> myHash;
        size_t index = 0;
        s.open(filename);
        if (!s) {
          std::cerr << "Fail to open " << filename << std::endl;
          exit(EXIT_FAILURE);
        }
        while (std::getline(s, line)) {
          passage = passage + line;
        }
        index = hash(passage);
        index = index % ((*temp).size());
        if ((*temp)[index].size() == 0) {
          (*temp)[index] = filename;
          // elementNum += 1;
          // if (getLoadFactor() > 0.8) {
          //std::cout << getLoadFactor() << std::endl;
          // rehash();  //not implemented yet!
          // }
        }
        else {
          std::cout << "#Removing " << filename << " (duplicate of" << std::endl
                    << (*temp)[index] << ")." << std::endl
                    << std::endl;
          std::cout << "rm " << filename << std::endl << std::endl;
        }
        s.close();
      }
    }
    bucketSize = bucketSize * 2 + 1;
    std::swap(table, temp);
    delete temp;
  };
  size_t hash(const std::string & str) {
    size_t ans = 0;
    for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
      ans = ans * 29 + *it;
    }
    return ans;
  }
  void add(std::string filename) {
    std::string line;
    std::string passage;
    std::ifstream s;
    size_t index = 0;
    s.open(filename);
    if (!s) {
      std::cerr << "Fail to open " << filename << std::endl;
      exit(EXIT_FAILURE);
    }
    while (std::getline(s, line)) {
      /*
      size_t hashValue = myHash(line);
      // hashValue = hashValue % bucketSize;
      index = index * 29 + hashValue;
      // counter += 1;
      */

      //      index = index + hash(line);
      passage = passage + line;
    }
    index = hash(passage);
    index = index % bucketSize;
    if ((*table)[index].size() == 0) {
      (*table)[index] = filename;
      elementNum += 1;
      if (getLoadFactor() > 0.5) {
        rehash();
      }
    }
    else {
      std::cout << "#Removing " << filename << " (duplicate of" << (*table)[index] << ")."
                << std::endl
                << std::endl;
      std::cout << "rm " << filename << std::endl << std::endl;
    }
    s.close();
  }

  //};

  void run(std::string filename) {
    std::string line;
    std::string passage;
    std::ifstream s;
    s.open(filename);
    if (!s) {
      std::cerr << "Fail to open " << filename << std::endl;
      exit(EXIT_FAILURE);
    }
    while (std::getline(s, line)) {
      passage = passage + line;
    }
    // passage = line;
    if (myDic.count(passage) && myDic[passage] != filename) {
      std::cout << "#Removing " << filename << " (duplicate of" << myDic[passage] << ")."
                << std::endl
                << std::endl;
      std::cout << "rm " << filename << std::endl << std::endl;
    }
    else {
      myDic.insert({passage, filename});
      // for (auto & x : myDic)
      // std::cout << x.first << ":" << x.second << std::endl;
    }
    s.close();
  }

  void readDir(char * basePath) {
    DIR * dir;
    struct dirent * ptr;
    char base[1000];
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
        // add(std::string(basePath) + std::string("/") + std::string(ptr->d_name));
        run(std::string(basePath) + std::string("/") + std::string(ptr->d_name));
      }
      //dir
      else if (ptr->d_type == 4) {
        memset(base, '\0', sizeof(base));
        strcpy(base, basePath);
        strcat(base, "/");
        strcat(base, (ptr->d_name));
        readDir(base);
      }
    }
    closedir(dir);
  }
};

int main(int argc, char ** argv) {
  if (argc == 1) {
    std::cerr << "Not enough arguments!\n" << std::endl;
    exit(EXIT_FAILURE);
  }
  // std::hash<std::string> myhash;
  // size_t x = myhash("bacabccbb");
  //  size_t y = myhash("cccbccccc");

  HashMap myHashMap;
  std::cout << "#!/bin/bash" << std::endl;
  for (int i = 1; i < argc; i++) {
    myHashMap.readDir(argv[i]);
  }
  // std::cout << x << "\n" << y << std::endl;
  return EXIT_SUCCESS;
}
