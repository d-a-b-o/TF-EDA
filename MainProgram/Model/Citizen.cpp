#include "Citizen.h"

Citizen::Citizen() {}

Citizen::Citizen(string _dni, string _names, string _surnames,
                 string _nationality, string _placeBirth, string _dateBirth,
                 string _dateDeath, string _address, string _phoneNumber,
                 string _email, string _maritalStatus)
    : DNI(_dni), names(_names), surnames(_surnames), nationality(_nationality),
      placeBirth(_placeBirth), dateBirth(_dateBirth), dateDeath(_dateDeath),
      address(_address), phoneNumber(_phoneNumber), email(_email),
      maritalStatus(_maritalStatus) {}

void Citizen::setDNI(string _dni) { DNI = _dni; }
void Citizen::setNames(string _names) { names = _names; }
void Citizen::setSurnames(string _surnames) { surnames = _surnames; }
void Citizen::setNationality(string _nationality) {
  nationality = _nationality;
}
void Citizen::setPlaceBirth(string _placeBirth) { placeBirth = _placeBirth; }
void Citizen::setDateBirth(string _dateBirth) { dateBirth = _dateBirth; }
void Citizen::setDateDeath(string _dateDeath) { dateDeath = _dateDeath; }
void Citizen::setAddress(string _address) { address = _address; }
void Citizen::setPhoneNumber(string _phoneNumber) {
  phoneNumber = _phoneNumber;
}
void Citizen::setEmail(string _email) { email = _email; }
void Citizen::setMaritalStatus(string _maritalStatus) {
  maritalStatus = _maritalStatus;
}

string Citizen::getDNI() { return DNI; }
string Citizen::getNames() { return names; }
string Citizen::getSurnames() { return surnames; }
string Citizen::getNationality() { return nationality; }
string Citizen::getPlaceBirth() { return placeBirth; }
string Citizen::getDateBirth() { return dateBirth; }
string Citizen::getDateDeath() { return dateDeath; }
string Citizen::getAddress() { return address; }
string Citizen::getPhoneNumber() { return phoneNumber; }
string Citizen::getEmail() { return email; }
string Citizen::getMaritalStatus() { return maritalStatus; }

string Citizen::toJson(const Citizen &citizen) {
  rapidjson::Document doc;
  rapidjson::Value &obj = doc.SetObject();
  auto addMember = [&obj, &doc](const char *key, const string &value) {
    using String = rapidjson::GenericStringRef<char>;
    obj.AddMember(String{key}, String{value.c_str()}, doc.GetAllocator());
  };
  addMember("DNI", citizen.DNI);
  addMember("names", citizen.names);
  addMember("surnames", citizen.surnames);
  addMember("nationality", citizen.nationality);
  addMember("placeBirth", citizen.placeBirth);
  addMember("dateBirth", citizen.dateBirth);
  addMember("dateDeath", citizen.dateDeath);
  addMember("address", citizen.address);
  addMember("phoneNumber", citizen.phoneNumber);
  addMember("email", citizen.email);
  addMember("maritalStatus", citizen.maritalStatus);
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  doc.Accept(writer);
  return buffer.GetString();
}

Citizen Citizen::fromJson(const string &json) {
  rapidjson::Document doc;
  doc.Parse(json.c_str());
  Citizen citizen;
  auto getString = [&doc](const char *key) { return doc[key].GetString(); };
  citizen.DNI = getString("DNI");
  citizen.names = getString("names");
  citizen.surnames = getString("surnames");
  citizen.nationality = getString("nationality");
  citizen.placeBirth = getString("placeBirth");
  citizen.dateBirth = getString("dateBirth");
  citizen.dateDeath = getString("dateDeath");
  citizen.address = getString("address");
  citizen.phoneNumber = getString("phoneNumber");
  citizen.email = getString("email");
  citizen.maritalStatus = getString("maritalStatus");
  return citizen;
}
