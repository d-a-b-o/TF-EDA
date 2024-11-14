#pragma once
#include <iostream>
#include <sys/types.h>
#include <vector>

using namespace std;

struct Data {
  u_int32_t key = 0;
  u_int32_t data = 0;
  u_int8_t numHash = 0;
  Data() : key(0), data(0), numHash(0) {}
  Data(u_int32_t initKey) : key(initKey), data(0), numHash(0) {}
  Data(u_int32_t initKey, u_int32_t initData)
      : key(initKey), data(initData), numHash(0) {}
};

class CuckooHashTable {
private:
  static const int MAX_COLLISIONS = 100;
  vector<vector<Data>> tables;
  u_int8_t numTables = 3;
  int tableSize = 10;
  size_t currentSize = 0;
  hash<u_int32_t> hashFn;

  size_t hashData(const Data &data);
  void rehash();

public:
  CuckooHashTable();
  int getCurrentSize();
  void insert(Data data);
  Data search(const u_int32_t &key);
  void print() {
    for (u_int8_t i = 0; i < numTables; i++) {
      cout << "Table " << static_cast<int>(i) << ":" << endl;
      for (size_t j = 0; j < tables[i].size(); j++) {
        if (tables[i][j].key != 0) {
          cout << "  Index " << j << ": Key = " << tables[i][j].key
               << ", Data = " << tables[i][j].data
               << ", NumHash = " << static_cast<int>(tables[i][j].numHash)
               << endl;
        }
      }
    }
  }
};
