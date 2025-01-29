/*#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <vector>
#include <memory>
using namespace std;
using json = nlohmann::json;

////////classe Ville////////
class Ville{
string nom;
int code_postal;
int prix_m2;
public:
//Constructeur avec attributs
Ville (string n, int cp, int p):nom{n}, code_postal{cp}, prix_m2{p} {}
friend std::ostream& operator<<(
  std::ostream& out, const Ville& v) {
  return out<<v.nom<<"/"<<v.code_postal<<"/"<<v.prix_m2;
}
//Constructeur avec json data
Ville (json d):nom{d["nom"]},code_postal{d["code postal"]},prix_m2{d["prix m2"]} {}
//Constructeur avec int id
Ville(int id) {
cpr::Response r = cpr::Get(cpr::Url{"http://127.0.0.1:8000/villes/" + to_string(id) + "/"}); 
json j = json::parse(r.text); 
nom = j["nom"]; code_postal = j["code postal"]; prix_m2 = j["prix m2"]; } 
};

////////classe Local////////
class Local {
    std::unique_ptr<Ville> ville;
    string nom;
    int surface;

public:
//Constructeur avec attributs
Local(int v, string n, int s) : ville{std::make_unique<Ville>(v)}, nom{n}, surface{s} {}
//Constructeur avec json data
Local(json d)
        : ville(std::make_unique<Ville>(d["ville"]["nom"], d["ville"]["code_postal"], d["ville"]["prix m2"])),
          nom{d["nom"]},
          surface{d["surface"]} {}
//Constructeur avec int id
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

////////classe Objet////////
class Objet{
string nom;
int prix;
public:
//Constructeur avec attributs
Objet (string n, int p):nom{n},prix{p} {}
friend std::ostream& operator<<(
  std::ostream& out, const Objet& ob) {
  return out<<ob.nom<<"/"<<ob.prix;
  }
//Constructeur avec json data
Objet(json d):nom{d["nom"]},prix{d["prix"]} {}
//Constructeur avec int id
Objet(int id) {
cpr::Response r = cpr::Get(cpr::Url{"http://127.0.0.1:8000/objet/" + to_string(id) + "/"}); 
json j = json::parse(r.text); 
nom = j["nom"]; prix = j["prix"]; }
};

////////classe Ressource////////
class Ressource{
std::unique_ptr<Objet> objet;

 public:
//Constructeur avec attributs
Ressource (int o): objet{std::make_unique<Objet>(o)} {}
friend std::ostream& operator<<(
  std::ostream& out, const Ressource& r) {
  return out<<*r.objet;
  }
//Constructeur avec json data
Ressource(nlohmann::json d1, nlohmann::json d2) : objet(std::make_unique<Objet>(d1["objet"]["nom"], d2["objet"]["prix"])) {}


};

////////classe QuantiteRessource////////
class QuantiteRessource{
std::unique_ptr<Ressource> ressource;
    int quantite;
public:
//Constructeur avec attributs
QuantiteRessource (int r, int q): ressource{std::make_unique<Ressource>(r)}, quantite{q} {}
friend std::ostream& operator<<(
  std::ostream& out, const QuantiteRessource& qr) {
  return out<<*qr.ressource<<"/"<<qr.quantite;
  }
//Constructeur avec json data
QuantiteRessource(json d): ressource(std::make_unique<Ressource>(d["ressource"]["nom"], d["ressource"]["prix"])),
          quantite{d["quantite"]} {}
//Constructeur avec int id
QuantiteRessource(int id) {
        cpr::Response r = cpr::Get(cpr::Url{"http://127.0.0.1:8000/quantite/" + to_string(id) + "/"});
        json j = json::parse(r.text);
        ressource = make_unique<Ressource>(j["ressource"]);  
        quantite = j["quantite"];
    }
};

////////classe Machine////////
class Machine{
string nom;
int n_serie;
int prix;
public:
//Constructeur avec attributs
Machine (string n, int ns, int p):nom{n}, n_serie{ns}, prix{p} {}
friend std::ostream& operator<<(
  std::ostream& out, const Machine& m) {
  return out<<m.nom<<"/"<<m.n_serie<<"/"<<m.prix;
  }
//Constructeur avec json data
Machine(json d):nom{d["nom"]},n_serie{d["n_serie"]},prix{d["prix"]} {}
//Constructeur avec int id
Machine(int id) {
cpr::Response r = cpr::Get(cpr::Url{"http://127.0.0.1:8000/machine/" + to_string(id) + "/"}); 
json j = json::parse(r.text); 
nom = j["nom"]; n_serie = j["n_serie"]; prix = j["prix"]; }
};

////////classe Usine////////
class Usine {
    std::unique_ptr<Local> local;
    std::vector<std::unique_ptr<Machine>> machines;

public:
    Usine(int l, int m) : local{std::make_unique<Local>(l)}, machines(m) {}

    friend std::ostream& operator<<(std::ostream& out, const Usine& u) {
        out << *u.local << "/";
        for (const auto& machine : u.machines) {
            out << *machine << " ";
        }
        return out;
    }

    Usine(json d) : local(std::make_unique<Local>(d["ville"]["nom"], d["ville"]["code_postal"], d["ville"]["prix m2"])), machines{} {
        if (d["machines"].is_array()) {
            for (const auto& machine_data : d["machines"]) {
                machines.push_back(std::make_unique<Machine>(machine_data));
            }
        } else {
            machines.push_back(std::make_unique<Machine>(d["machines"]));
        }
    }

    Usine(int id) {
        cpr::Response r = cpr::Get(cpr::Url{"http://127.0.0.1:8000/usine/" + std::to_string(id) + "/"});
        json j = json::parse(r.text);
        local = std::make_unique<Local>(j["local"]);  
        for (const auto& machine_data : j["machines"]) {
            machines.push_back(std::make_unique<Machine>(machine_data));
        }
    }
};

/*class Usine : public Local {
    std::vector<std::unique_ptr<Machine>> machines;

public:
    Usine(int v, string n, int s) : Local(v, n, s) {}
Usine(json d) : Local(d["ville"]), machines{}{
   // Usine(json d) : Local(d["ville"]["nom"], d["ville"]["code_postal"], d["ville"]["prix m2"]), machines{} {
       for (const auto& machine_data : d["machines"]) {
            machines.push_back(std::make_unique<Machine>(machine_data));
        }
    }

    Usine(int id) : Local(id) {
        cpr::Response r = cpr::Get(cpr::Url{"http://127.0.0.1:8000/usine/" + to_string(id) + "/"});
        json j = json::parse(r.text);
        for (const auto& machine_data : j["machines"]) {
            machines.push_back(std::make_unique<Machine>(machine_data));
        }
    }

    void add_machine(int machine_id) {
        machines.push_back(std::make_unique<Machine>(machine_id));
    }

    friend ostream& openwm3622b@u3-211-06d:~/Desktop/tp_coo/crayon/low_level$ ./build/low_level
{"nom": "TOULOUSE", "code postal": 31000, "prix m2": 1500}
{"nom": "bois", "prix": 10}
{"ville": 2, "nom": "CHEZ MARIAM", "surface": 50}
{"nom": "m1", "n_serie": 1, "prix": 1000}
{"machines": [1, 2], "ville": 2, "nom": "CHEZ MARIAM", "surface": 50}
{"quantite": 1000, "ressource": 1}
{"quantite": 50, "ressource": 2}
ville :TOULOUSE/31000/1500
ville 1 :TOULOUSE/31000/1500
ville 2 : Labège/3100/2000
objet :bois/10
objet: mine/15
local :Labège/3100/2000/CHEZ MARIAM/50
machine 1 :m1/1/1000
machine 2: m2/2/2000
quantite ressource :bois/10/1000
quantite ressource :mine/15/50
terminate called after throwing an instance of 'nlohmann::json_abi_v3_11_3::detail::type_error'
  what():  [json.exception.type_error.302] type must be number, but is null
Abandon
rator<<(ostream& out, const Usine& u) {
        //out << static_cast<const Local&>(u) << " | Machines: ";
      out << "Usine: " << static_cast<const Local&>(u) << "\n";

        for (const auto& machine : u.machines) {
            out << *machine << " ";
        }
        return out;
    }
}

////////classe Etape////////

////////classe Produit////////

////////classe Stock////////

auto main(int argc, char** argv)-> int{
  
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
  
  cpr::Response r4= cpr::Get(cpr::Url{"http://127.0.0.1:8000/usine/1/"});
  r4.status_code;                  // 200
    r4.header["content-type"];       // application/json; charset=utf-8
    r4.text;  
   std::cout<< r4.text<< std::endl;
  json j4= json::parse(r4.text);
    
    /////////////////////////QUANTITE RESSOURCE///////////////////////////////////////////// 

  cpr::Response r5= cpr::Get(cpr::Url{"http://127.0.0.1:8000/quantite/1/"});
  r5.status_code;                  // 200
    r5.header["content-type"];       // application/json; charset=utf-8
    r5.text;  
   std::cout<< r5.text<< std::endl;
  json j5 = json::parse(r5.text);

    cpr::Response r6= cpr::Get(cpr::Url{"http://127.0.0.1:8000/quantite/2/"});
  r6.status_code;                  // 200
    r6.header["content-type"];       // application/json; charset=utf-8
    r6.text;  
   std::cout<< r6.text<< std::endl;
  json j6 = json::parse(r6.text);

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
  //Affichage avec attributs
  const auto ob= Objet{j1["nom"], j1["prix"]};
  std::cout<<"objet :"<< ob<< std::endl;
  //Affichage avec int id
  const auto ob1 = Objet{2};
  std::cout << "objet: " << ob1 << std::endl; 
/////////////////////////AFFICHAGE LOCAUX///////////////////////////////
  //Affichage avec attributs
const auto l= Local{j2["ville"], j2["nom"], j2["surface"]};
  std::cout<<"local :"<< l<< std::endl;
/////////////////////////AFFICHAGE MACHINE///////////////////////////////
  //Affichage avec attributs
const auto m1= Machine{j3["nom"], j3["n_serie"], j3["prix"]};
  std::cout<<"machine 1 :"<< m1<< std::endl;

  //Affichage avec int id
  const auto m2 = Machine{2};
  std::cout << "machine 2: " << m2 << std::endl; 
 
/////////////////////////AFFICHAGE QUANTITE RESSOURCE///////////////////////////////
  //Affichage avec attributs
const auto qr= QuantiteRessource{j5["ressource"], j5["quantite"]};
  std::cout<<"quantite ressource :"<< qr<< std::endl;
  
//Affichage avec attributs
const auto qr2= QuantiteRessource{j6["ressource"], j6["quantite"]};
  std::cout<<"quantite ressource :"<< qr2<< std::endl;
  
/////////////////////////AFFICHAGE USINE///////////////////////////////
//Affichage avec attributs
    const auto u= Usine{j4["local"], j4["machines"]};
    std::cout << "Usine : " << u << std::endl;
   
  return 0;
}
*/
#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <vector>
#include <memory>
using namespace std;
using json = nlohmann::json;

////////classe Ville////////
class Ville {
    string nom;
    int code_postal;
    int prix_m2;

public:
    //Constructeur avec attributs
    Ville(string n, int cp, int p) : nom{n}, code_postal{cp}, prix_m2{p} {}

    friend std::ostream &operator<<(std::ostream &out, const Ville &v) {
        return out << v.nom << "/" << v.code_postal << "/" << v.prix_m2;
    }

    //Constructeur avec json data
    Ville(json d) : nom{d["nom"]}, code_postal{d["code postal"]}, prix_m2{d["prix m2"]} {}

    //Constructeur avec int id
    Ville(int id) {
        cpr::Response r = cpr::Get(cpr::Url{"http://127.0.0.1:8000/villes/" + to_string(id) + "/"});
        json j = json::parse(r.text);
        nom = j["nom"];
        code_postal = j["code postal"];
        prix_m2 = j["prix m2"];
    }
};

////////classe Local////////
class Local {
    std::unique_ptr<Ville> ville;
    string nom;
    int surface;

public:
    //Constructeur avec attributs
    Local(int v, string n, int s) : ville{std::make_unique<Ville>(v)}, nom{n}, surface{s} {}

    //Constructeur avec json data
    Local(json d)
            : ville(std::make_unique<Ville>(d["ville"]["nom"], d["ville"]["code_postal"], d["ville"]["prix m2"])),
              nom{d["nom"]},
              surface{d["surface"]} {}

    //Constructeur avec int id
    Local(int id) {
        cpr::Response r = cpr::Get(cpr::Url{"http://127.0.0.1:8000/locaux/" + to_string(id) + "/"});
        json j = json::parse(r.text);
        ville = make_unique<Ville>(j["ville"]);
        nom = j["nom"];
        surface = j["surface"];
    }

    friend std::ostream &operator<<(std::ostream &out, const Local &l) {
        return out << *l.ville << "/" << l.nom << "/" << l.surface;
    }
};

////////classe Objet////////
class Objet {
    string nom;
    int prix;

public:
    //Constructeur avec attributs
    Objet(string n, int p) : nom{n}, prix{p} {}

    friend std::ostream &operator<<(std::ostream &out, const Objet &ob) {
        return out << ob.nom << "/" << ob.prix;
    }

    //Constructeur avec json data
    Objet(json d) : nom{d["nom"]}, prix{d["prix"]} {}

    //Constructeur avec int id
    Objet(int id) {
        cpr::Response r = cpr::Get(cpr::Url{"http://127.0.0.1:8000/objet/" + to_string(id) + "/"});
        json j = json::parse(r.text);
        nom = j["nom"];
        prix = j["prix"];
    }
};

////////classe Ressource////////
class Ressource {
    std::unique_ptr<Objet> objet;

public:
    //Constructeur avec attributs
    Ressource(int o) : objet{std::make_unique<Objet>(o)} {}

    friend std::ostream &operator<<(std::ostream &out, const Ressource &r) {
        return out << *r.objet;
    }

    //Constructeur avec json data
    Ressource(nlohmann::json d1, nlohmann::json d2) : objet(std::make_unique<Objet>(d1["objet"]["nom"], d2["objet"]["prix"])) {}
};

////////classe QuantiteRessource////////
class QuantiteRessource {
    std::unique_ptr<Ressource> ressource;
    int quantite;

public:
    //Constructeur avec attributs
    QuantiteRessource(int r, int q) : ressource{std::make_unique<Ressource>(r)}, quantite{q} {}

    friend std::ostream &operator<<(std::ostream &out, const QuantiteRessource &qr) {
        return out << *qr.ressource << "/" << qr.quantite;
    }

    //Constructeur avec json data
    QuantiteRessource(json d) : ressource(std::make_unique<Ressource>(d["ressource"]["nom"], d["ressource"]["prix"])),
                                quantite{d["quantite"]} {}

    //Constructeur avec int id
    QuantiteRessource(int id) {
        cpr::Response r = cpr::Get(cpr::Url{"http://127.0.0.1:8000/quantite/" + to_string(id) + "/"});
        json j = json::parse(r.text);
        ressource = make_unique<Ressource>(j["ressource"]);
        quantite = j["quantite"];
    }
};

////////classe Machine////////
class Machine {
    string nom;
    int n_serie;
    int prix;

public:
    //Constructeur avec attributs
    Machine(string n, int ns, int p) : nom{n}, n_serie{ns}, prix{p} {}

    friend std::ostream &operator<<(std::ostream &out, const Machine &m) {
        return out << m.nom << "/" << m.n_serie << "/" << m.prix;
    }

    //Constructeur avec json data
    Machine(json d) : nom{d["nom"]}, n_serie{d["n_serie"]}, prix{d["prix"]} {}

    //Constructeur avec int id
    Machine(int id) {
        cpr::Response r = cpr::Get(cpr::Url{"http://127.0.0.1:8000/machine/" + to_string(id) + "/"});
        json j = json::parse(r.text);
        nom = j["nom"];
        n_serie = j["n_serie"];
        prix = j["prix"];
    }
};

////////classe Usine////////
class Usine : public Local {
  private:
    std::vector<std::unique_ptr<Machine>> machine;
    
  public:
    Usine(string nom_, json ville_, int surface_, json machine_, json stock_)
        : Local(nom_, ville_, surface_) {
        for (const auto& mach : machine_){
          machine.push_back(std::make_unique<Machine>(mach));
        }
        for (const auto& stk : stock_){
          stock.push_back(std::make_unique<Stock>(stk));
        }
    }

    friend std::ostream& operator<<(std::ostream& out, const Usine& usine_) {
      out << usine_.nom << " ; Ville: " << *usine_.ville
                << " ; Surface: " << usine_.surface;
      out << "; Machines:";
      for (const auto& mach : usine_.machine){
          out << " - " << *mach;
      }
      out << " ; Stocks:";
      for (const auto& stk : usine_.stock){
          out << " - " << *stk;
      }
      return out;
    }

    Usine(json data) : Local(data) {
      for (const auto& mach : data["machines"]){
        machine.push_back(std::make_unique<Machine>(mach));
      }
     
    }

    static void affichage(){
      unsigned int essai = 0;
      while(true){
        static unsigned int id = 1;
        string url_Usine = "http://localhost:8000/usine/api/"+to_string(id);
        auto response = cpr::Get(cpr::Url{url_Usine});
        if (response.status_code != 200) {
          essai++;
        }
        else {
          const auto Usine_ = Usine(
              json::parse(cpr::Get(cpr::Url{url_Usine}).text));
          std::cout << "Usine: " << Usine_ << "\n" << std::endl;
          essai=0;
        }
        if(essai==5){
          break;
        }
        id++;
      }
    }
};

auto main(int argc, char **argv) -> int {

    ///////////////////////////VILLE//////////////////////////////////////////////
    cpr::Response r = cpr::Get(cpr::Url{"http://127.0.0.1:8000/villes/1/"});
    json j = json::parse(r.text);

    //////////////////////////OBJET//////////////////////////////////////////////
    cpr::Response r1 = cpr::Get(cpr::Url{"http://127.0.0.1:8000/objet/1/"});
    json j1 = json::parse(r1.text);

    //////////////////////////LOCAUX//////////////////////////////////////////////
    cpr::Response r2 = cpr::Get(cpr::Url{"http://127.0.0.1:8000/locaux/1/"});
    json j2 = json::parse(r2.text);

    /////////////////////////MACHINE/////////////////////////////////////////////
    cpr::Response r3 = cpr::Get(cpr::Url{"http://127.0.0.1:8000/machine/1/"});
    json j3 = json::parse(r3.text);

    /////////////////////////USINE/////////////////////////////////////////////
    cpr::Response r4 = cpr::Get(cpr::Url{"http://127.0.0.1:8000/usine/1/"});
    json j4 = json::parse(r4.text);

    /////////////////////////QUANTITE RESSOURCE/////////////////////////////////////////////
    cpr::Response r5 = cpr::Get(cpr::Url{"http://127.0.0.1:8000/quantite/1/"});
    json j5 = json::parse(r5.text);

    ///////////////////////////AFFICHAGE VILLE///////////////////////////////
    const auto v = Ville{j["nom"], j["code postal"], j["prix m2"]};
    std::cout << "ville :" << v << std::endl;

    const auto v1 = Ville{j};
    std::cout << "ville 1 :" << v1 << std::endl;

    const auto v2 = Ville{2};
    std::cout << "ville 2 : " << v2 << std::endl;

    /////////////////////////AFFICHAGE OBJET///////////////////////////////
    const auto ob = Objet{j1["nom"], j1["prix"]};
    std::cout << "objet :" << ob << std::endl;

    const auto ob1 = Objet{2};
    std::cout << "objet: " << ob1 << std::endl;

    /////////////////////////AFFICHAGE LOCAUX///////////////////////////////
    const auto l = Local{j2["ville"], j2["nom"], j2["surface"]};
    std::cout << "local :" << l << std::endl;

    /////////////////////////AFFICHAGE MACHINE///////////////////////////////
    const auto m1 = Machine{j3["nom"], j3["n_serie"], j3["prix"]};
    std::cout << "machine 1 :" << m1 << std::endl;

    const auto m2 = Machine{2};
    std::cout << "machine 2: " << m2 << std::endl;

    /////////////////////////AFFICHAGE QUANTITE RESSOURCE///////////////////////////////
    const auto qr = QuantiteRessource{j5["ressource"], j5["quantite"]};
    std::cout << "quantite ressource :" << qr << std::endl;

    /////////////////////////AFFICHAGE USINE///////////////////////////////
   std::cout << "\nAffichage Usine: \n"<< endl;
  Usine::affichage();
    return 0;
}
