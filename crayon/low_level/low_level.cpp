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
Ville(json d) {
    try {
        nom = d.at("nom").get<string>();
        code_postal = d.at("code postal").get<int>();
        prix_m2 = d.at("prix m2").get<int>();
    } catch (const json::exception& e) {
        throw std::runtime_error("Erreur dans le JSON pour Ville : " + std::string(e.what()));
    }
}

Ville(int id) {
    cpr::Response r = cpr::Get(cpr::Url{"http://127.0.0.1:8000/villes/" + to_string(id) + "/"});
    if (r.status_code != 200) {
        throw std::runtime_error("Erreur HTTP pour Ville avec id " + to_string(id) + ": " + r.text);
    }
    try {
        json j = json::parse(r.text);
        nom = j.at("nom").get<string>();
        code_postal = j.at("code postal").get<int>();
        prix_m2 = j.at("prix m2").get<int>();
    } catch (const json::exception& e) {
        throw std::runtime_error("Erreur dans le JSON pour Ville avec id " + to_string(id) + ": " + std::string(e.what()));
    }
}
 
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
Objet(json d) {
    try {
        nom = d.at("nom").get<string>();
        prix = d.at("prix").get<int>();
    } catch (const json::exception& e) {
        throw std::runtime_error("Erreur dans le JSON pour Objet : " + std::string(e.what()));
    }
}
Objet(int id) {
    cpr::Response r = cpr::Get(cpr::Url{"http://127.0.0.1:8000/objet/" + to_string(id) + "/"});
    if (r.status_code != 200) {
        throw std::runtime_error("Erreur HTTP pour Objet avec id " + to_string(id) + ": " + r.text);
    }
    try {
        json j = json::parse(r.text);
        nom = j.at("nom").get<string>();
        prix = j.at("prix").get<int>();
    } catch (const json::exception& e) {
        throw std::runtime_error("Erreur dans le JSON pour Objet avec id " + to_string(id) + ": " + std::string(e.what()));
    }
}

};
int main(int argc, char** argv) {
    try {
        cpr::Response r = cpr::Get(cpr::Url{"http://127.0.0.1:8000/villes/1/"});
        if (r.status_code != 200) {
            throw std::runtime_error("Erreur HTTP pour Ville : " + r.text);
        }
        json j = json::parse(r.text);
        Ville v1{j};
        std::cout << "Ville : " << v1 << std::endl;

        cpr::Response r1 = cpr::Get(cpr::Url{"http://127.0.0.1:8000/objet/1/"});
        if (r1.status_code != 200) {
            throw std::runtime_error("Erreur HTTP pour Objet : " + r1.text);
        }
        json j1 = json::parse(r1.text);
        Objet ob1{j1};
        std::cout << "Objet : " << ob1 << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    return 0;
}

