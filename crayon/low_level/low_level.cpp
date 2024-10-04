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

auto main()-> int{
  const auto v= Ville("Labège", 31000, 2000)
  std::cout<<"ville :"<< v<< std::endl;
  std::cout<< r.text<< std::endl;
  return 0;
}
