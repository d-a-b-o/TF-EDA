#include "../Controller/MainController.h"
#include <cstddef>
#include <iostream>
#include <string>

using namespace std;

MainController mainController;

void insertar() {
  string nombres, apellidos, nacionalidad, fechaNacimiento, lugarNacimiento,
      direccion, telefono, correoElectronico, estadoCivil;
  Citizen newCitizen;
  system("clear");
  cin.ignore();
  cout << "=== AGREGAR CIUDADANO ===" << endl;
  cout << "Ingrese nombres: " << endl;
  getline(cin, nombres);
  newCitizen.setNames(nombres);
  cout << "Ingrese apellidos: " << endl;
  getline(cin, apellidos);
  newCitizen.setSurnames(apellidos);
  cout << "Ingrese nacionalidad: " << endl;
  getline(cin, nacionalidad);
  newCitizen.setNationality(nacionalidad);
  cout << "Ingrese lugar de nacimiento: " << endl;
  getline(cin, lugarNacimiento);
  newCitizen.setPlaceBirth(lugarNacimiento);
  cout << "Ingrese fecha de nacimiento: " << endl;
  getline(cin, fechaNacimiento);
  newCitizen.setDateBirth(fechaNacimiento);
  newCitizen.setDateDeath("00/00/0000");
  cout << "Ingrese dirección: " << endl;
  getline(cin, direccion);
  newCitizen.setAddress(direccion);
  cout << "Ingrese teléfono: " << endl;
  getline(cin, telefono);
  newCitizen.setPhoneNumber(telefono);
  cout << "Ingrese correo electrónico: " << endl;
  getline(cin, correoElectronico);
  newCitizen.setEmail(correoElectronico);
  cout << "Ingrese estado civil: " << endl;
  getline(cin, estadoCivil);
  newCitizen.setMaritalStatus(estadoCivil);

  string newDNI = mainController.addCitizen(newCitizen);

  cout << "=== DETALLES DEL CIUDADANO ===" << endl;
  cout << "DNI: " << newDNI << endl;
  cout << "Nombres: " << newCitizen.getNames() << endl;
  cout << "Apellidos: " << newCitizen.getSurnames() << endl;
  cout << "Nacionalidad: " << newCitizen.getNationality() << endl;
  cout << "Lugar de Nacimiento: " << newCitizen.getPlaceBirth() << endl;
  cout << "Fecha de Nacimiento: " << newCitizen.getDateBirth() << endl;
  cout << "Fecha de defunción: " << newCitizen.getDateDeath() << endl;
  cout << "Direccion: " << newCitizen.getAddress() << endl;
  cout << "Telefono: " << newCitizen.getPhoneNumber() << endl;
  cout << "Correo Electronico: " << newCitizen.getEmail() << endl;
  cout << "Estado Civil: " << newCitizen.getMaritalStatus() << endl;
  cin >> nombres;
}

void buscar() {
  size_t DNI;

  system("clear");
  cin.ignore();
  cout << "=== BUSCAR CIUDADANO ===" << endl;
  cout << "Ingrese DNI: " << endl;
  cin >> DNI;

  Citizen newCitizen = mainController.searchCitizen(DNI);
  cout << "=== DETALLES DEL CIUDADANO ===" << endl;
  cout << "DNI: " << newCitizen.getDNI() << endl;
  cout << "Nombres: " << newCitizen.getNames() << endl;
  cout << "Apellidos: " << newCitizen.getSurnames() << endl;
  cout << "Nacionalidad: " << newCitizen.getNationality() << endl;
  cout << "Lugar de Nacimiento: " << newCitizen.getPlaceBirth() << endl;
  cout << "Fecha de Nacimiento: " << newCitizen.getDateBirth() << endl;
  cout << "Fecha de defunción: " << newCitizen.getDateDeath() << endl;
  cout << "Direccion: " << newCitizen.getAddress() << endl;
  cout << "Telefono: " << newCitizen.getPhoneNumber() << endl;
  cout << "Correo Electronico: " << newCitizen.getEmail() << endl;
  cout << "Estado Civil: " << newCitizen.getMaritalStatus() << endl;
  cin >> DNI;
}
void actualizar() {
  string _DNI, nombres, apellidos, nacionalidad, fechaNacimiento,
      lugarNacimiento, direccion, telefono, correoElectronico, estadoCivil;
  size_t DNI;
  Citizen newCitizen;
  system("clear");
  cin.ignore();

  cout << "=== BUSCAR CIUDADANO ===" << endl;
  cout << "Ingrese DNI: " << endl;
  cin >> DNI;

  _DNI = mainController.searchCitizen(DNI).getDNI();

  if (_DNI != to_string(DNI)) {
    cout << "DNI invalido" << endl;
    return;
  }

  newCitizen.setDNI(_DNI);

  cin.ignore();

  cout << "=== ACTUALIZAR CIUDADANO ===" << endl;
  cout << "Ingrese nombres: " << endl;
  getline(cin, nombres);
  newCitizen.setNames(nombres);
  cout << "Ingrese apellidos: " << endl;
  getline(cin, apellidos);
  newCitizen.setSurnames(apellidos);
  cout << "Ingrese nacionalidad: " << endl;
  getline(cin, nacionalidad);
  newCitizen.setNationality(nacionalidad);
  cout << "Ingrese lugar de nacimiento: " << endl;
  getline(cin, lugarNacimiento);
  newCitizen.setPlaceBirth(lugarNacimiento);
  cout << "Ingrese fecha de nacimiento: " << endl;
  getline(cin, fechaNacimiento);
  newCitizen.setDateBirth(fechaNacimiento);
  newCitizen.setDateDeath("00/00/0000");
  cout << "Ingrese dirección: " << endl;
  getline(cin, direccion);
  newCitizen.setAddress(direccion);
  cout << "Ingrese teléfono: " << endl;
  getline(cin, telefono);
  newCitizen.setPhoneNumber(telefono);
  cout << "Ingrese correo electrónico: " << endl;
  getline(cin, correoElectronico);
  newCitizen.setEmail(correoElectronico);
  cout << "Ingrese estado civil: " << endl;
  getline(cin, estadoCivil);
  newCitizen.setMaritalStatus(estadoCivil);

  mainController.updateCitizen(newCitizen);

  cout << "=== DETALLES DEL CIUDADANO ===" << endl;
  cout << "DNI: " << newCitizen.getDNI() << endl;
  cout << "Nombres: " << newCitizen.getNames() << endl;
  cout << "Apellidos: " << newCitizen.getSurnames() << endl;
  cout << "Nacionalidad: " << newCitizen.getNationality() << endl;
  cout << "Lugar de Nacimiento: " << newCitizen.getPlaceBirth() << endl;
  cout << "Fecha de Nacimiento: " << newCitizen.getDateBirth() << endl;
  cout << "Fecha de defunción: " << newCitizen.getDateDeath() << endl;
  cout << "Direccion: " << newCitizen.getAddress() << endl;
  cout << "Telefono: " << newCitizen.getPhoneNumber() << endl;
  cout << "Correo Electronico: " << newCitizen.getEmail() << endl;
  cout << "Estado Civil: " << newCitizen.getMaritalStatus() << endl;
  cin >> nombres;
}

int main() {
  int opt;
  do {
    system("clear");
    cout << "Number of records: " << mainController.getNumRecords() << endl;
    cout << "Test Program" << endl;
    cout << "1. Insertar" << endl;
    cout << "2. Buscar" << endl;
    cout << "3. Actualizar" << endl;
    cin >> opt;
    switch (opt) {
    case 1:
      insertar();
      break;
    case 2:
      buscar();
      break;
    case 3:
      actualizar();
      break;
    default:
      break;
    }
  } while (opt != 0);
}
