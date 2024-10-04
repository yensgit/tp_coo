#include <iostream>
#include <string>
#include <cpr/cpr.h>
using namespace std;

class Ville{
string nom;
int code_postal;
int prix_m2;
public:
Ville (string n, int cp, int p):nom{n}, code_postal{cp}, prix_m2{p} {}
friend std::ostream& operator<<(
  std::ostream& out, const Ville& v) {
  return out<<v.nom<<"/"<<v.code_postal<<"/"<<v.prix_m2;
};

auto main(int argc, char** argv)-> int{
   cpr::Response r = cpr::Get(cpr::Url{"https://api.github.com/repos/whoshuu/cpr/contributors"},
    r.status_code;                  // 200
    r.header["content-type"];       // application/json; charset=utf-8
    r.text;                         // JSON text string
  
  const auto v= Ville{"Labège", 31000, 2000};
  std::cout<<"ville :"<< v<< std::endl;
  std::cout<< r.text<< std::endl;
  return 0;
}
