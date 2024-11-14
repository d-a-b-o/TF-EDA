#include "BinarySave.h"
#include <fstream>

using namespace std;

int BinarySave::getNumRecords() { return numRecords; }

void BinarySave::addNumRecords() { numRecords++; }

Citizen BinarySave::read(streampos position) {
  Citizen citizen;

  fstream file(DATA_ROUTE, ios::in | ios::binary);
  if (!file.is_open()) {
    return Citizen();
  }

  file.seekg(position * RECORD_SIZE);

  int sizeStr;
  file.read(reinterpret_cast<char *>(&sizeStr), sizeof(sizeStr));

  vector<char> buffer(sizeStr);
  file.read(buffer.data(), sizeStr);
  file.close();

  string record(buffer.begin(), buffer.end());

  vector<string> cut = Tools::splitString(record, ';');

  citizen.setDNI(cut[0]);
  citizen.setNames(cut[1]);
  citizen.setSurnames(cut[2]);
  citizen.setNationality(cut[3]);
  citizen.setPlaceBirth(cut[4]);
  citizen.setDateBirth(cut[5]);
  citizen.setDateDeath(cut[6]);
  citizen.setAddress(cut[7]);
  citizen.setPhoneNumber(cut[8]);
  citizen.setEmail(cut[9]);
  citizen.setMaritalStatus(cut[10]);

  return citizen;
}

void BinarySave::insert(Citizen &citizen, fstream &fileData) {
  string record = citizen.getDNI() + ";" + citizen.getNames() + ";" +
                  citizen.getSurnames() + ";" + citizen.getNationality() + ";" +
                  citizen.getPlaceBirth() + ";" + citizen.getDateBirth() + ";" +
                  citizen.getDateDeath() + ";" + citizen.getAddress() + ";" +
                  citizen.getPhoneNumber() + ";" + citizen.getEmail() + ";" +
                  citizen.getMaritalStatus() + ";";

  record += string(245 - record.length(), ' ') + ";";

  int sizeStr = record.size();

  fileData.write(reinterpret_cast<const char *>(&sizeStr), sizeof(sizeStr));
  fileData.write(record.c_str(), sizeStr);
  addNumRecords();
}

void BinarySave::write(Citizen &citizen) {
  fstream file(DATA_ROUTE, ios::out | ios::app | ios::binary);
  if (!file.is_open()) {
    return;
  }

  insert(citizen, file);

  file.close();
}

void BinarySave::overwrite(Citizen &citizen, streampos position) {
  fstream file(DATA_ROUTE, ios::in | ios::out | ios::binary);
  if (!file.is_open()) {
    return;
  }

  string record = citizen.getDNI() + ";" + citizen.getNames() + ";" +
                  citizen.getSurnames() + ";" + citizen.getNationality() + ";" +
                  citizen.getPlaceBirth() + ";" + citizen.getDateBirth() + ";" +
                  citizen.getDateDeath() + ";" + citizen.getAddress() + ";" +
                  citizen.getPhoneNumber() + ";" + citizen.getEmail() + ";" +
                  citizen.getMaritalStatus() + ";";

  record += string(245 - record.length(), ' ') + ";";

  int sizeStr = record.size();

  file.seekp(position * RECORD_SIZE);
  file.write(reinterpret_cast<const char *>(&sizeStr), sizeof(sizeStr));
  file.write(record.c_str(), sizeStr);

  file.close();
}
