#include <iostream>
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
  return out<<v.nom<<"/"<<v.code_postal<<"/"<<v.prix_m2<<" euros par m²";
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
        return out << *l.ville << "/" << l.nom << "/" << l.surface << " m²";
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
  return out<<ob.nom<<"/"<<ob.prix<<" euros";
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
  return out<<m.nom<<"/"<<m.n_serie<<"/"<<m.prix<<" euros";
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

    friend ostream& operator<<(ostream& out, const Usine& u) {
        //out << static_cast<const Local&>(u) << " | Machines: ";
      out << "Usine: " << static_cast<const Local&>(u) << "\n";

        for (const auto& machine : u.machines) {
            out << *machine << " ";
        }
        return out;
    }
};*/

////////classe Etape////////
class Etape{
int nom;
std::unique_ptr<QuantiteRessource> quantite;
std::unique_ptr<Machine> machine;
int duree;
std::unique_ptr<Etape> etapesuiv;

public:
//Constructeur avec attributs
Etape (int n, int qr, int m, int d, int es): nom{n}, quantite{std::make_unique<QuantiteRessource>(qr)}, machine{std::make_unique<Machine>(m)}, duree{d}, etapesuiv{std::make_unique<Etape>(es)} {}
friend std::ostream& operator<<(
  std::ostream& out, const Etape& e) {
  return out<<e.nom<<"/"<<*e.quantite<<"/"<<*e.machine<<"/"<<e.duree<<"/"<<*e.etapesuiv;
  }
//Constructeur avec json data
Etape(json d): nom{d["nom"]}, quantite(std::make_unique<QuantiteRessource>(d["quantite"]["ressource"], d["quantite"]["quantite"])),
machine(std::make_unique<Machine>(d["machine"]["nom"], d["machine"]["n_serie"], d["machine"]["prix"])),
          duree{d["duree"]},
etapesuiv(std::make_unique<Etape>(d["etapesuiv"]["nom"])) {}
//Constructeur avec int id
Etape(int id) {
        cpr::Response r = cpr::Get(cpr::Url{"http://127.0.0.1:8000/etape/" + to_string(id) + "/"});
        json j = json::parse(r.text);
      nom = j["nom"];
      quantite = make_unique<QuantiteRessource>(j["quantite"]);
      machine = make_unique<Machine>(j["machine"]); 
      duree = j["duree"];
      etapesuiv = make_unique<Etape>(j["etapesuiv"]); 
    }
};
////////classe Produit////////
class Produit {

std::unique_ptr<Objet> objet;
std::unique_ptr<Etape> etape;

 public:
    // Constructeur avec attributs
    Produit(int o, int e): objet{std::make_unique<Objet>(o)}, etape{std::make_unique<Etape>(e)} {}
friend std::ostream& operator<<(
  std::ostream& out, const Produit& p) {
  return out<<*p.objet<<"/"<<*p.etape;
  }
//Constructeur avec json data
Produit(json d): objet(std::make_unique<Objet>(d["objet"])),
          etape(std::make_unique<Etape>(d["etape"])) {}
//Constructeur avec int id
Produit(int id) {
        cpr::Response r = cpr::Get(cpr::Url{"http://127.0.0.1:8000/produit/" + to_string(id) + "/"});
        json j = json::parse(r.text);
        objet = make_unique<Objet>(j["objet"]);  
        etape = make_unique<Etape>(j["etape"]); 
    }
};
        

////////classe Stock////////
class Stock {

std::unique_ptr<Usine> usine;
std::unique_ptr<Ressource> ressource;
int nombre;

 public:
    // Constructeur avec attributs
    Stock(int u, int r,int n): usine{std::make_unique<Usine>(u)}, ressource{std::make_unique<Ressource>(r)},nombre{n} {}
friend std::ostream& operator<<(
  std::ostream& out, const Stock& s) {
  return out<<*s.usine<<"/"<<*s.ressource<<"/"<<s.nombre;
  }
//Constructeur avec json data
Stock(json d): usine(std::make_unique<Usine>(d["usine"])),
          ressource(std::make_unique<Ressource>(d["ressource"])) {}
//Constructeur avec int id
Stock(int id) {
        cpr::Response r = cpr::Get(cpr::Url{"http://127.0.0.1:8000/stock/" + to_string(id) + "/"});
        json j = json::parse(r.text);
        usine = make_unique<Usine>(j["usine"]);  
        ressource = make_unique<Ressource>(j["ressource"]); 
   nombre = j["nombre"]; 
    }
};
auto main(int argc, char** argv)-> int{
  
  std::cout<<"AFFICHAGE AVEC LES REQUETES HTTP EN UTILISANT CPR \n"<< << std::endl;
  ///////////////////////////VILLE//////////////////////////////////////////////
   cpr::Response r = cpr::Get(cpr::Url{"http://127.0.0.1:8000/villes/1/"});
  
    r.status_code;                  // 200
    r.header["content-type"];       // application/json; charset=utf-8
    r.text;                         // JSON text string
                         // JSON text string
  std::cout<< r.text<< std::endl;
  json j = json::parse(r.text);

     cpr::Response r12 = cpr::Get(cpr::Url{"http://127.0.0.1:8000/villes/2/"});
  
    r12.status_code;                  // 200
    r12.header["content-type"];       // application/json; charset=utf-8
    r12.text;                         // JSON text string
                         // JSON text string
  std::cout<< r12.text<< std::endl;
  json j12 = json::parse(r12.text);
  
  //////////////////////////LOCAUX//////////////////////////////////////////////
  cpr::Response r1= cpr::Get(cpr::Url{"http://127.0.0.1:8000/locaux/1/"});
  r1.status_code;                  // 200
    r1.header["content-type"];       // application/json; charset=utf-8
    r1.text;  
   std::cout<< r1.text<< std::endl;
  json j1 = json::parse(r1.text);
  
    //////////////////////////OBJET//////////////////////////////////////////////
 cpr::Response r2 = cpr::Get(cpr::Url{"http://127.0.0.1:8000/objet/1/"});
  r2.status_code;                  // 200
    r2.header["content-type"];       // application/json; charset=utf-8
    r2.text;  
   std::cout<< r2.text<< std::endl;
  json j2 = json::parse(r2.text);

   cpr::Response r13 = cpr::Get(cpr::Url{"http://127.0.0.1:8000/objet/2/"});
  r13.status_code;                  // 200
    r13.header["content-type"];       // application/json; charset=utf-8
    r13.text;  
   std::cout<< r13.text<< std::endl;
  json j13 = json::parse(r13.text);
  
     cpr::Response r14 = cpr::Get(cpr::Url{"http://127.0.0.1:8000/objet/3/"});
  r14.status_code;                  // 200
    r14.header["content-type"];       // application/json; charset=utf-8
    r14.text;  
   std::cout<< r14.text<< std::endl;
  json j14 = json::parse(r14.text);
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

      /////////////////////////ETAPE///////////////////////////////////////////// 

  cpr::Response r7= cpr::Get(cpr::Url{"http://127.0.0.1:8000/etape/1/"});
  r7.status_code;                  // 200
    r7.header["content-type"];       // application/json; charset=utf-8
    r7.text;  
   std::cout<< r7.text<< std::endl;
  json j7 = json::parse(r7.text);

    cpr::Response r8= cpr::Get(cpr::Url{"http://127.0.0.1:8000/etape/2/"});
  r8.status_code;                  // 200
    r8.header["content-type"];       // application/json; charset=utf-8
    r8.text;  
   std::cout<< r8.text<< std::endl;
  json j8 = json::parse(r8.text);

   /////////////////////////PRODUIT///////////////////////////////////////////// 
  
  cpr::Response r9= cpr::Get(cpr::Url{"http://127.0.0.1:8000/produit/3/"});
  r9.status_code;                  // 200
    r9.header["content-type"];       // application/json; charset=utf-8
    r9.text;  
   std::cout<< r9.text<< std::endl;
  json j9= json::parse(r9.text);
  
  //////////////////////////STOCK//////////////////////////////////////////////
  
  cpr::Response r10= cpr::Get(cpr::Url{"http://127.0.0.1:8000/stock/1/"});
  r10.status_code;                  // 200
    r10.header["content-type"];       // application/json; charset=utf-8
    r10.text;  
   std::cout<< r10.text<< std::endl;
  json j10 = json::parse(r10.text);
  
 cpr::Response r11= cpr::Get(cpr::Url{"http://127.0.0.1:8000/stock/2/"});
  r11.status_code;                  // 200
    r11.header["content-type"];       // application/json; charset=utf-8
    r11.text;  
   std::cout<< r11.text<< std::endl;
  json j11 = json::parse(r11.text);

  std::cout<<"\n AFFICHAGE AVEC LES CONSTRUCTEURS \n"<< << std::endl;
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
/////////////////////////AFFICHAGE LOCAUX///////////////////////////////
  //Affichage avec attributs
const auto l= Local{j1["ville"], j1["nom"], j1["surface"]};
std::cout<<"local :"<< l<< std::endl;
 /////////////////////////AFFICHAGE OBJET///////////////////////////////  
  //Affichage avec attributs
const auto ob= Objet{j2["nom"], j2["prix"]};
std::cout<<"objet :"<< ob<<" kg"<< std::endl;
  //Affichage avec int id
const auto ob1 = Objet{2};
std::cout << "objet: " << ob1 <<" m"<< std::endl; 

  
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
/*/////////////////////////AFFICHAGE USINE///////////////////////////////
    //Affichage avec int id
  const auto u = Usine{1};
  std::cout << "Usine : " << u << std::endl;
  
   /////////////////////////AFFICHAGE ETAPE///////////////////////////////                             //Nous avons commenté cette partie car, à partir de quantité de ressource, nous n'arrivons plus à afficher les éléments des classes
    //Affichage avec int id                                                                            //Usine, Etape, Produit et Stock avec les const auto. On a pu les afficher autrement avec les requêtes HTTP en faisnat usage de cpr comme
  const auto e1 = Etape{j7["nom"], j7["resource"], j7["machine"], j7["duree"], j7["etapesuiv"]};       //vous pourrez le voir à la compilation mais pour les const auto, on a l'erreur suivante que nous n'avons pas réussi à débugger.
  std::cout << "etape 1: " << e1 << std::endl;                                                         //En utilisant l'affichage avec les attributs, on a :
                                                                                                       //terminate called after throwing an instance of 'nlohmann::json_abi_v3_11_3::detail::type_error'
    //Affichage avec int id                                                                            //what():  [json.exception.type_error.302] type must be string, but is null
  const auto e2 = Etape{2};                                                                            //Abandon
  std::cout << "etape 2: " << e2 << std::endl;                                                         //En utilisant l'affichage avec json data ou int id, on a :
                                                                                                       //terminate called after throwing an instance of 'nlohmann::json_abi_v3_11_3::detail::type_error'
  /////////////////////////AFFICHAGE PRODUIT///////////////////////////////                            //what():  [json.exception.type_error.305] cannot use operator[] with a string argument with number
    //Affichage avec attributs                                                                         //Abandon
const auto p= Produit{j9["objet"], j9["etape"]};
  std::cout<<"produit :"<< p<< std::endl;
  
    //Affichage avec int id
  const auto p1 = Produit{3};
  std::cout << "produit id: " << p1 << std::endl;

   /////////////////////////AFFICHAGE STOCK///////////////////////////////
    //Affichage avec int id
  const auto s1 = Stock{1};
  std::cout << "stock 1 : " << s1 << std::endl;

    //Affichage avec int id
  const auto s2 = Stock{2};
  std::cout << "stock 2 : " << s2 << std::endl;
  */
  

   
  return 0;
}
