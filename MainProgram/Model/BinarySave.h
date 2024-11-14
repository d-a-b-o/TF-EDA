#pragma once
#include "../Tools/Tools.h"
#include "Citizen.h"
#include <fstream>
#include <string>
#include <unistd.h>
#include <vector>

using namespace std;

class BinarySave {
private:
  int numRecords;
  const string DATA_ROUTE = "../Data/data.bin";
  const int RECORD_SIZE = 250;

public:
  int getNumRecords();
  void addNumRecords();

  Citizen read(streampos pos);
  void insert(Citizen &citizen, fstream &file);
  void write(Citizen &citizen);
  void overwrite(Citizen &citizen, streampos pos);
};
