#include "GeneradorController.h"

GeneradorController::GeneradorController() {
  loadMapNombres();
  cout << "Nombres Map size after loading: " << mapNombres.size() << endl;
  loadMapDepartamentos();
  cout << "Departamentos Map size after loading: " << mapDepartamentos.size()
       << endl;
  loadLstApellidos();
  cout << "Apellidos Lst size after loading: " << lstApellidos.size() << endl;
  lstCalles = {"Azangaro",      "La Merced", "Ingenieros",
               "Javier Prado",  "Huerfanos", "Emancipacion",
               "Flora Tristan", "Sauce",     "Velasco Astete",
               "Chacarilla",    "Benavides", "Carabaya"};
  lstTipoCalle = {"Calle", "Avenida", "Jiron", "Pasaje"};
  lstEstados = {"Soltero", "Casado", "Viudo", "Divorciado"};
}

void GeneradorController::loadMapNombres() {
  ifstream file("../Data/nombres.csv");
  string linea;

  while (getline(file, linea)) {
    vector<string> cut = Tools::splitString(linea, ',');
    string nombre = cut[0];
    string genero = cut[1];
    mapNombres[genero].push_back(nombre);
  }
}

void GeneradorController::loadLstApellidos() {
  ifstream file("../Data/apellidos.csv");
  string linea;

  while (getline(file, linea))
    lstApellidos.push_back(linea);
}

void GeneradorController::loadMapDepartamentos() {
  ifstream file("../Data/departamentos.csv");
  string linea;

  while (getline(file, linea)) {
    vector<string> cut = Tools::splitString(linea, ',');
    string departamento = cut[0];
    string provincias = cut[1];

    lstDepartamentos.push_back(departamento);
    mapDepartamentos[departamento] = Tools::splitString(provincias, ';');
  }
}

string GeneradorController::generarDni() {
  string dni = "";

  return dni;
}

string GeneradorController::generarNombres() {
  string genero =
      (Tools::getRandomNumber(0, 1) == 0) ? "MASCULINO" : "FEMENINO";
  int num = mapNombres.at(genero).size() - 1;
  int posPrimerNombre = Tools::getRandomNumber(0, num);
  int posSegundoNombre = Tools::getRandomNumber(0, num);
  string primerNombre = mapNombres.at(genero)[posPrimerNombre];
  string segundoNombre = mapNombres.at(genero)[posSegundoNombre];
  string nombres = primerNombre + " " + segundoNombre;

  return nombres;
}

string GeneradorController::generarApellidos() {
  int posPrimerApellido = Tools::getRandomNumber(0, lstApellidos.size() - 1);
  int posSegundoApellido = Tools::getRandomNumber(0, lstApellidos.size() - 1);
  string primerApellido = lstApellidos[posPrimerApellido];
  string segundoApellido = lstApellidos[posSegundoApellido];
  string apellidos = primerApellido + " " + segundoApellido;

  return apellidos;
}

string GeneradorController::generarNacionalidad() {
  string nacionalidad = "Peruana";

  return nacionalidad;
}

string GeneradorController::generarLugarNacimiento() {
  string departamento = Tools::selectRandomElement(lstDepartamentos);

  return departamento;
}

string GeneradorController::generarFechaNacimiento() {
  string dia = to_string(Tools::getRandomNumber(1, 29));
  string mes = to_string(Tools::getRandomNumber(1, 12));
  string anio = to_string(Tools::getRandomNumber(1900, 2024));
  string fechaNacimiento = dia + "/" + mes + "/" + anio;

  return fechaNacimiento;
}

string GeneradorController::generarFechaDefuncion() {
  string fechaDefuncion = "00/00/0000";

  return fechaDefuncion;
}

string GeneradorController::generarDireccion() {
  string numeroCalle = to_string(Tools::getRandomNumber(1, 9999));
  string nombreCalle = Tools::selectRandomElement(lstCalles);
  string tipoCalle = Tools::selectRandomElement(lstTipoCalle);
  string departamento = Tools::selectRandomElement(lstDepartamentos);
  int posProvincia =
      Tools::getRandomNumber(0, mapDepartamentos.at(departamento).size() - 1);
  string provincia = mapDepartamentos.at(departamento)[posProvincia];

  string direccion = tipoCalle + " " + nombreCalle + " " + numeroCalle + " " +
                     provincia + ", " + departamento;

  return direccion;
}

string GeneradorController::generarTelefono() {
  string telefono = "9";

  for (int i = 0; i < 8; i++)
    telefono += to_string(Tools::getRandomNumber(0, 9));

  return telefono;
}

string GeneradorController::generarCorreo(string &nombres, string &apellidos) {
  int posSpaceNombres = nombres.find(' ');
  int posSpaceApellidos = apellidos.find(' ');

  string correo = nombres.substr(0, posSpaceNombres) + "." +
                  apellidos.substr(0, posSpaceApellidos) + "@example.com";

  return correo;
}

string GeneradorController::generarEstadoCivil() {
  string estadoCivil = Tools::selectRandomElement(lstEstados);

  return estadoCivil;
}

Citizen GeneradorController::generarCiudadano() {
  string DNI = generarDni();
  string nombres = generarNombres();
  string apellidos = generarApellidos();
  string nacionalidad = generarNacionalidad();
  string lugarNacimiento = generarLugarNacimiento();
  string fechaNacimiento = generarFechaNacimiento();
  string fechaDefuncion = generarFechaDefuncion();
  string direccion = generarDireccion();
  string telefono = generarTelefono();
  string correo = generarCorreo(nombres, apellidos);
  string estadoCivil = generarEstadoCivil();

  return Citizen(DNI, nombres, apellidos, nacionalidad, lugarNacimiento,
                 fechaNacimiento, fechaDefuncion, direccion, telefono, correo,
                 estadoCivil);
}
