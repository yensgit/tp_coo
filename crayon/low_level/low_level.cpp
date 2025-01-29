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
    std::unique_ptr<Ville> ville;
    string nom;
    int surface;

public:
Local(int v, string n, int s) : ville{std::make_unique<Ville>(v)}, nom{n}, surface{s} {}
Local(json d)
        : ville(std::make_unique<Ville>(d["ville"]["nom"], d["ville"]["code_postal"], d["ville"]["prix m2"])),
          nom{d["nom"]},
          surface{d["surface"]} {}
Local(int id) {
        cpr::Response r = cpr::Get(cpr::Url{"http://127.0.0.1:8000/locaux/" + to_string(id) + "/"});
        json j = json::parse(r.text);
        ville = make_unique<Ville>(j["ville"]);  
        nom = j["nom"];
        surface = j["surface"];
    }

    friend std::ostream& operator<<(std::ostream& out, const Local& l) {
        return out << *l.ville << "/" << l.nom << "/" << l.surface;
    }
};
class Objet{
string nom;
int prix;
public:
Objet (string n, int p):nom{n},prix{p} {}
friend std::ostream& operator<<(
  std::ostream& out, const Objet& ob) {
  return out<<ob.nom<<"/"<<ob.prix;
  }
Objet(json d):nom{d["nom"]},prix{d["prix"]} {}
Objet(int id) {
cpr::Response r = cpr::Get(cpr::Url{"http://127.0.0.1:8000/objet/" + to_string(id) + "/"}); 
json j = json::parse(r.text); 
nom = j["nom"]; prix = j["prix"]; }
};

class Machine{
string nom;
int n_serie;
int prix;
public:
Machine (string n, int ns, int p):nom{n}, n_serie{ns}, prix{p} {}
friend std::ostream& operator<<(
  std::ostream& out, const Machine& m) {
  return out<<m.nom<<"/"<<m.n_serie<<"/"<<m.prix;
  }
Machine(json d):nom{d["nom"]},n_serie{d["n_serie"]},prix{d["prix"]} {}
Machine(int id) {
cpr::Response r = cpr::Get(cpr::Url{"http://127.0.0.1:8000/machine/" + to_string(id) + "/"}); 
json j = json::parse(r.text); 
nom = j["nom"]; n_serie = j["n_serie"]; prix = j["prix"]; }
};
class Usine {
    std::unique_ptr<Local> local;
    std::vector<std::unique_ptr<Machine>> machines;

public:
    Usine(int l) : local{std::make_unique<Local>(l)} {}
    
    Usine(const json& d)
        : local(std::make_unique<Local>(d["local"]["ville"], d["local"]["nom"], d["local"]["surface"])) {
        for (const auto& m : d["machines"]) {
            machines.push_back(std::make_unique<Machine>(m));
        }
    }
    
    Usine(const std::string& id) {
        cpr::Response r = cpr::Get(cpr::Url{"http://127.0.0.1:8000/usine/" + id + "/"});
        json j = json::parse(r.text);
        local = std::make_unique<Local>(j["local"]);
        for (const auto& m : j["machines"]) {
            machines.push_back(std::make_unique<Machine>(m));
        }
    }

    void add_machine(std::unique_ptr<Machine> machine) {
        machines.push_back(std::move(machine));
    }

    friend std::ostream& operator<<(std::ostream& out, const Usine& u) {
        out << *u.local << " / Machines: ";
        for (const auto& m : u.machines) {
            out << "[" << *m << "] ";
        }
        return out;
    }
};


main(int argc, char** argv)-> int{
  
  ///////////////////////////VILLE//////////////////////////////////////////////
   cpr::Response r = cpr::Get(cpr::Url{"http://127.0.0.1:8000/villes/1/"});
  
    r.status_code;                  // 200
    r.header["content-type"];       // application/json; charset=utf-8
    r.text;                         // JSON text string
                         // JSON text string
  std::cout<< r.text<< std::endl;
  json j = json::parse(r.text);
  
    //////////////////////////OBJET//////////////////////////////////////////////
 cpr::Response r1 = cpr::Get(cpr::Url{"http://127.0.0.1:8000/objet/1/"});
  r1.status_code;                  // 200
    r1.header["content-type"];       // application/json; charset=utf-8
    r1.text;  
   std::cout<< r1.text<< std::endl;
  json j1 = json::parse(r1.text);
  
  //////////////////////////LOCAUX//////////////////////////////////////////////
  cpr::Response r2= cpr::Get(cpr::Url{"http://127.0.0.1:8000/locaux/1/"});
  r2.status_code;                  // 200
    r2.header["content-type"];       // application/json; charset=utf-8
    r2.text;  
   std::cout<< r2.text<< std::endl;
  json j2 = json::parse(r2.text);

    /////////////////////////MACHINE///////////////////////////////////////////// 

  cpr::Response r3= cpr::Get(cpr::Url{"http://127.0.0.1:8000/machine/1/"});
  r3.status_code;                  // 200
    r3.header["content-type"];       // application/json; charset=utf-8
    r3.text;  
   std::cout<< r3.text<< std::endl;
  json j3 = json::parse(r3.text);
  
    /////////////////////////USINE///////////////////////////////////////////// 
  
  
   /////////////////////////AFFICHAGE VILLE///////////////////////////////
  //Pour le constructeur avec attributs
  const auto v= Ville{j["nom"], j["code postal"], j["prix m2"]};
  std::cout<<"ville :"<< v<< std::endl;

  //Pour le constructeur json data
  const auto v1= Ville{j};
   std::cout<<"ville 1 :"<< v1<< std::endl;

  //Pour le construteur int id
   const auto v2 = Ville{2};
  std::cout << "ville 2 : " << v2 << std::endl; 
 /////////////////////////AFFICHAGE OBJET///////////////////////////////  
  //Pour le constructeur avec attributs
  const auto ob= Objet{j1["nom"], j1["prix"]};
  std::cout<<"objet :"<< ob<< std::endl;
  
  const auto ob1 = Objet{2};
  std::cout << "objet: " << ob1 << std::endl; 
   /////////////////////////AFFICHAGE LOCAUX///////////////////////////////
  
const auto l= Local{j2["ville"], j2["nom"], j2["surface"]};
  std::cout<<"local :"<< l<< std::endl;
   /////////////////////////AFFICHAGE MACHINE///////////////////////////////
const auto m1= Machine{j3["nom"], j3["n_serie"], j3["prix"]};
  std::cout<<"machine 1 :"<< m1<< std::endl;

  const auto m2 = Machine{2};
  std::cout << "machine 2: " << m2 << std::endl; 
 /////////////////////////AFFICHAGE USINE///////////////////////////////
  //////////////////////////USINE/////////////////////////////////////////////
  cpr::Response r4 = cpr::Get(cpr::Url{"http://127.0.0.1:8000/usine/1/"});
  json j4 = json::parse(r4.text);
  std::cout << "Usine JSON: " << j4 << std::endl;

  const auto u = Usine{j4};
  std::cout << "Usine : " << u << std::endl;

  const auto u1 = Usine{1}; 
  std::cout << "Usine 1 : " << u1 << std::endl;

 

  return 0;
}
