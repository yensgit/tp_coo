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
Ville (json d):nom{d["nom"]},code_postal{d["code postal"]},prix_m2{d["prix m2"]} {}
Ville(int id) {
cpr::Response r = cpr::Get(cpr::Url{"http://127.0.0.1:8000/villes/" + to_string(id) + "/"}); 
json j = json::parse(r.text); 
nom = j["nom"]; code_postal = j["code postal"]; prix_m2 = j["prix m2"]; } 
};

class Local{
std::unique_ptr <Ville> ville;
string nom;
int surface;
public:
Local (int v, string n, int s):ville{std::make_unique<Ville>(v)}, nom{n}, surface{s} {}
friend std::ostream& operator<<(
  std::ostream& out, const Local& l) {
  return out<<*l.ville<<"/"<<l.nom<<"/"<<l.surface;
}
Local(json d):ville{d["ville"]},nom{d["nom"]},surface{d["surface"]} {}
};
auto main(int argc, char** argv)-> int{
   cpr::Response r = cpr::Get(cpr::Url{"http://127.0.0.1:8000/villes/1/"});
    r.status_code;                  // 200
    r.header["content-type"];       // application/json; charset=utf-8
    r.text;                         // JSON text string
  
  std::cout<< r.text<< std::endl;
  json j = json::parse(r.text);
 
  //Pour le constructeur avec attributs
  const auto v= Ville{j["nom"], j["code postal"], j["prix m2"]};
  std::cout<<"ville :"<< v<< std::endl;

  //Pour le constructeur json data
  const auto v1= Ville{j};
   std::cout<<"ville 1 :"<< v1<< std::endl;

  //Pour le construteur int id
   const auto v2 = Ville{2};
  std::cout << "ville 2 : " << v2 << std::endl; 

  //Pour le construteur int id
   const auto l= Local{j["ville"], j["nom"], j["surface"]};
  std::cout<<"local :"<< l<< std::endl;
  const auto l1= Local{j};
   std::cout<<"Local 1 :"<< l1<< std::endl;
  return 0;
}
