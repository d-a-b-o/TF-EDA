#include "../Controller/MainController.h"

#include <exception>
#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/mime.h>
#include <pistache/net.h>
#include <pistache/router.h>

#include <memory>
#include <stdexcept>
#include <string>

using namespace std;

class Service {
private:
  // Número del puerto donde el servidor correrá
  uint16_t m_portNum;
  // Número de hilos para manejar peticiones concurrentes
  unsigned int m_numThreads;
  // Direccion del servidor
  Pistache::Address m_address;
  // Servidor Http
  shared_ptr<Pistache::Http::Endpoint> m_endPoint;
  // Enrutador para definir rutas Http
  Pistache::Rest::Router m_router;

  // Controlador para manejar la logica relacionada con Ciudadanos
  MainController dbController;

  // Configura las rutas Http
  void configureRoutes();

  using Request = Pistache::Rest::Request;
  using Response = Pistache::Http::ResponseWriter;

  // Manejan las operaciones especificas sobre los Ciudadanos
  void getCitizen(const Request &request, Response response);
  void updateCitizen(const Request &request, Response response);
  void createCitizen(const Request &request, Response response);

public:
  Service(uint16_t portNum = 8000, unsigned int numThreads = 1)
      : m_portNum(portNum), m_numThreads(numThreads),
        m_address("localhost", portNum),
        m_endPoint(make_shared<Pistache::Http::Endpoint>(m_address)) {}
  void run();
};

void Service::configureRoutes() {
  Pistache::Rest::Routes::Get(
      m_router, "/citizen/:DNI",
      Pistache::Rest::Routes::bind(&Service::getCitizen, this));
  Pistache::Rest::Routes::Put(
      m_router, "/citizen/:DNI",
      Pistache::Rest::Routes::bind(&Service::updateCitizen, this));
  Pistache::Rest::Routes::Put(
      m_router, "/citizen",
      Pistache::Rest::Routes::bind(&Service::createCitizen, this));
  Pistache::Rest::Routes::Post(
      m_router, "/citizen",
      Pistache::Rest::Routes::bind(&Service::createCitizen, this));
}

void Service::getCitizen(const Request &request, Response response) {
  try {
    size_t DNI = request.param(":DNI").as<size_t>();
    Citizen citizen = dbController.searchCitizen(DNI);
    response.send(Pistache::Http::Code::Ok, Citizen::toJson(citizen),
                  MIME(Application, Json));
  } catch (const runtime_error &bang) {
    response.send(Pistache::Http::Code::Not_Found, bang.what(),
                  MIME(Text, Plain));
  } catch (...) {
    response.send(Pistache::Http::Code::Internal_Server_Error, "Internal error",
                  MIME(Text, Plain));
  }
}

void Service::updateCitizen(const Request &request, Response response) {
  try {
    size_t DNI = request.param(":DNI").as<size_t>();
    string json = request.body();
    Citizen citizen = Citizen::fromJson(json);
    dbController.updateCitizen(citizen);
    response.send(Pistache::Http::Code::Ok,
                  "Citizen " + to_string(DNI) + " updated.", MIME(Text, Plain));
  } catch (const runtime_error &bang) {
    response.send(Pistache::Http::Code::Not_Found, bang.what(),
                  MIME(Text, Plain));
  } catch (...) {
    response.send(Pistache::Http::Code::Internal_Server_Error, "Internal error",
                  MIME(Text, Plain));
  }
}

void Service::createCitizen(const Request &request, Response response) {
  try {
    const string json = request.body();
    Citizen citizen = Citizen::fromJson(json);
    const string DNI = dbController.addCitizen(citizen);
    response.send(Pistache::Http::Code::Ok, "Citizen " + DNI + " created.",
                  MIME(Text, Plain));
  } catch (const runtime_error &bang) {
    response.send(Pistache::Http::Code::Not_Found, bang.what(),
                  MIME(Text, Plain));
  } catch (...) {
    response.send(Pistache::Http::Code::Internal_Server_Error, "Internal error",
                  MIME(Text, Plain));
  }
}

void Service::run() {
  cout << "Starting on port " << m_portNum << " with " << m_numThreads
       << " thread.\n";
  m_endPoint->init(Pistache::Http::Endpoint::options().threads(m_numThreads));
  configureRoutes();
  m_endPoint->setHandler(m_router.handler());
  m_endPoint->serve();
}

int main() {
  try {
    Service service;
    service.run();
  } catch (const exception &bang) {
    cerr << bang.what() << "\n";
    return 1;
  } catch (...) {
    return 1;
  }

  return 0;
}
