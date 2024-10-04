#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;

class Ville{
string nom;
int code_postal;
int prix_m2;
public:
Ville (string n, int cp, int p):nom{n}, code_postal{cp}, prix_m2{p} {}
friend std::ostream& operator<<(
  std::ostream& out, const Ville& v) {
  return out<<v.nom<<"/"<<v.code_postal<<"/"<<v.prix_m2;
}
};

auto main(int argc, char** argv)-> int{
   cpr::Response r = cpr::Get(cpr::Url{"http://127.0.0.1:8000/villes/1/"});
    r.status_code;                  // 200
    r.header["content-type"];       // application/json; charset=utf-8
    r.text;                         // JSON text string
std::cout<< r.text<< std::endl;
  json j = json::parse(r.text);
  
  const auto v= Ville{j["nom"], j["code_postal"], j["prix_m2"]};
  std::cout<<"ville :"<< v<< std::endl;

  return 0;
}
