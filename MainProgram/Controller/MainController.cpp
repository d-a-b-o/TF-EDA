#include "MainController.h"

using namespace std;

MainController::MainController() { loadIndexTable(); }

string MainController::addCitizen(Citizen &citizen) {
  citizen.setDNI(to_string(indexTable.getCurrentSize() + 1));

  indexTable.insert(Data(stoi(citizen.getDNI())));
  binarySave.write(citizen);

  return citizen.getDNI();
}

Citizen MainController::searchCitizen(size_t &DNI) {
  Data found = indexTable.search(DNI);

  if (found.key != DNI) {
    throw runtime_error("Invalid id " + to_string(DNI));
  }

  return binarySave.read(found.key - 1);
}

void MainController::updateCitizen(Citizen &citizen) {
  Data found = indexTable.search(stoi(citizen.getDNI()));

  if (found.key != stoi(citizen.getDNI())) {
    throw runtime_error("Invalid id" + citizen.getDNI());
  }

  binarySave.overwrite(citizen);
}

void MainController::loadIndexTable() {
  fstream file("../Data/data.bin", ios::in | ios::binary);

  if (!file.is_open()) {
    return;
  }

  file.seekg(0, ios::end);
  streampos fileSize = file.tellg();
  int numRecords = fileSize / 250;
  file.seekg(0, ios::beg);

  const size_t blockSize = 1000000;
  vector<char> buffer(blockSize * 250);

  for (size_t i = 0; i < numRecords; i += blockSize) {
    size_t recordsToRead = std::min(blockSize, numRecords - i);
    file.read(buffer.data(), recordsToRead * 250);

    for (size_t j = 0; j < recordsToRead; ++j) {
      const char *recordStart = buffer.data() + j * 250;
      string record(recordStart, 250);
      vector<string> cut = Tools::splitString(record, ';');
      string temp = cut[0].substr(4, 8);
      cout << temp << endl;
      indexTable.insert(Data(stoi(temp)));
      binarySave.addNumRecords();
    }
  }
  file.close();
}
