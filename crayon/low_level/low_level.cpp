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

class Local {
 private:
  string nom_local;
  unique_ptr<Ville> p_ville;
  int surface_local;
  int ville;

 public:
  Local(string nom_local_, int surface_local_, int ville_)
      : nom_local(nom_local_), ville(ville_), surface_local(surface_local_) {
    p_ville = make_unique<Ville>(ville);
  }

  Local(const json& data)
      : nom_local(data["nom_local"]),
        surface_local(data["surface_local"]),
        ville(data["ville"]) {
    p_ville = make_unique<Ville>(ville);
  }

  Local(int id) {
    cpr::Response r = cpr::Get(
        cpr::Url{"http://127.0.0.1:8000/local/" + to_string(id) + "/"});

    json j = json::parse(r.text);
    nom_local = j["nom_local"];
    surface_local = j["surface_local"];
    ville = j["ville"];
    p_ville = make_unique<Ville>(ville);
    
  }
  void afficher1() const {
    cout << "Nom du local: " << nom_local << endl;
    cout << "Surface du local: " << surface_local << " m2" << endl;
    cout << "ID de la ville: " << ville << endl;}

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
//pour l'affichage du local
  const auto l= Local{1};
    l.afficher1();
  return 0;
}
