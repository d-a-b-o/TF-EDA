#include "../Controller/GeneradorController.h"
#include "../Model/BinarySave.h"
#include "../Model/CuckooHashTable.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

GeneradorController genController;
BinarySave binSave;
CuckooHashTable indexTable;

void loadIndexTable() {
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
      cout << record << endl;
      vector<string> cut = Tools::splitString(record, ';');
      string temp = cut[0].substr(4, 8);
      indexTable.insert(Data(stoi(temp), i + j));
      binSave.addNumRecords();
    }
  }

  file.close();
}

void generar(int numRecords) {
  fstream file("../Data/data.bin", ios::out | ios::app | ios::binary);
  if (!file.is_open()) {
    cerr << "Fallo al abrir ../Data/data.bin \n";
    cin.get();
  }

  for (int i = 0; i < numRecords; i++) {
    Citizen ciudadano = genController.generarCiudadano();
    ciudadano.setDNI(to_string(indexTable.getCurrentSize() + 10000000));
    try {
      int dni = stoi(ciudadano.getDNI());

      if (indexTable.search(dni).key != dni) {
        // cout << i << "-" << dni << ": " << ciudadano.getNames() << endl;
        binSave.insert(ciudadano, file);
        Data data = Data(dni, binSave.getNumRecords());
        indexTable.insert(data);
        binSave.addNumRecords();
      } else {
        i--;
      }
    } catch (const invalid_argument &e) {
      cerr << "Error: invalid argument for stoi with value "
           << ciudadano.getDNI() << endl;
    } catch (const out_of_range &e) {
      cerr << "Error: out of range for stoi with value " << ciudadano.getDNI()
           << endl;
    }
  }

  file.close();
  cin.get();
}

int main() {
  loadIndexTable();

  int opt;

  do {
    cout << "numRecords: " << indexTable.getCurrentSize() << endl;
    cout << "======= MENU GENERADOR =======" << endl;
    cout << " [1] Generar 1000" << endl;
    cout << " [2] Generar 10000" << endl;
    cout << " [3] Generar 100000" << endl;
    cout << " [4] Generar 1000000" << endl;
    cout << " [5] Generar 10000000" << endl;
    cout << " [6] Generar 33000000" << endl;
    cout << " [0] Cerrar" << endl;
    cout << "           >";
    cin >> opt;

    switch (opt) {
    case 1:
      generar(1000);
      break;
    case 2:
      generar(10000);
      break;
    case 3:
      generar(100000);
      break;
    case 4:
      generar(1000000);
      break;
    case 5:
      generar(10000000);
      break;
    case 6:
      generar(33000000);
      break;
    default:
      break;
    }
  } while (opt != 0);

  cin.get();
}
