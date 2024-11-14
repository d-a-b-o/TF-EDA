#pragma once
#include "../Model/BinarySave.h"
#include "../Model/CuckooHashTable.h"
#include <cstddef>
#include <stdexcept>
#include <string>

using namespace std;

class MainController {
private:
  CuckooHashTable indexTable;
  BinarySave binarySave;

public:
  MainController();
  string addCitizen(Citizen &citizen);
  Citizen searchCitizen(size_t &DNI);
  void updateCitizen(Citizen &citizen);
  void loadIndexTable();
  int getNumRecords() { return binarySave.getNumRecords(); }
};
