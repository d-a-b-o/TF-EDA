#include "MainController.h"

using namespace std;

MainController::MainController() { loadIndexTable(); }

string MainController::addCitizen(Citizen &citizen) {
  citizen.setDNI(to_string(indexTable.getCurrentSize() + 10000000));

  indexTable.insert(Data(stoi(citizen.getDNI()), indexTable.getCurrentSize()));
  binarySave.write(citizen);

  return citizen.getDNI();
}

Citizen MainController::searchCitizen(size_t &DNI) {
  Data found = indexTable.search(DNI);

  if (found.key != DNI) {
    throw runtime_error("Invalid id " + to_string(DNI));
  }

  return binarySave.read(found.data);
}

void MainController::updateCitizen(Citizen &citizen) {
  Data found = indexTable.search(stoi(citizen.getDNI()));

  if (found.key != stoi(citizen.getDNI())) {
    throw runtime_error("Invalid id" + citizen.getDNI());
  }

  binarySave.overwrite(citizen, found.data);
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

  for (int i = 0; i < numRecords; ++i) {
    file.seekg(i * 250);
    int sizeStr;
    file.read(reinterpret_cast<char *>(&sizeStr), sizeof(sizeStr));

    vector<char> buffer(sizeStr);
    file.read(buffer.data(), sizeStr);

    string record(buffer.begin(), buffer.end());
    vector<string> cut = Tools::splitString(record, ';');

    if (!cut.empty()) {
      indexTable.insert(Data(stoi(cut[0]), i));
      binarySave.addNumRecords();
    }
  }

  file.close();
}
