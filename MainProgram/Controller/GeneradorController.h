#pragma once
#include "../Model/Citizen.h"
#include "../Tools/Tools.h"

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class GeneradorController {
private:
  map<string, vector<string>> mapNombres;
  map<string, vector<string>> mapDepartamentos;
  vector<string> lstDepartamentos;
  vector<string> lstApellidos;
  vector<string> lstCalles;
  vector<string> lstTipoCalle;
  vector<string> lstEstados;

public:
  GeneradorController();
  void loadMapNombres();
  void loadLstApellidos();
  void loadMapDepartamentos();
  string generarDni();
  string generarNombres();
  string generarApellidos();
  string generarNacionalidad();
  string generarLugarNacimiento();
  string generarFechaNacimiento();
  string generarFechaDefuncion();
  string generarDireccion();
  string generarTelefono();
  string generarCorreo(string &nombres, string &apellidos);
  string generarEstadoCivil();
  Citizen generarCiudadano();
};
