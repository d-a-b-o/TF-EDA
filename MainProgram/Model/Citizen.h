#pragma once
#include "../rapidjson/document.h"
#include "../rapidjson/stringbuffer.h"
#include "../rapidjson/writer.h"
#include <string>

using namespace std;

class Citizen {
private:
  string DNI;
  string names;
  string surnames;
  string nationality;
  string placeBirth;
  string dateBirth;
  string dateDeath;
  string address;
  string phoneNumber;
  string email;
  string maritalStatus;

public:
  Citizen();
  Citizen(string _dni, string _names, string _surnames, string _nationality,
          string _placeBirth, string _dateBirth, string _dateDeath,
          string _address, string _phoneNumber, string _email,
          string _maritalStatus);

  void setDNI(string _dni);
  void setNames(string _names);
  void setSurnames(string _surnames);
  void setNationality(string _nationality);
  void setPlaceBirth(string _placeBirth);
  void setDateBirth(string _dateBirth);
  void setDateDeath(string _dateDeath);
  void setAddress(string _address);
  void setPhoneNumber(string _phoneNumber);
  void setEmail(string _email);
  void setMaritalStatus(string _maritalStatus);

  string getDNI();
  string getNames();
  string getSurnames();
  string getNationality();
  string getPlaceBirth();
  string getDateBirth();
  string getDateDeath();
  string getAddress();
  string getPhoneNumber();
  string getEmail();
  string getMaritalStatus();

  static string toJson(const Citizen &citizen);
  static Citizen fromJson(const string &json);
};
