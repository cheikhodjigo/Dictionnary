#include <iostream>
#include <string>
#include "tableau.h"
using namespace std;

namespace utility
{
    Tableau<string>& decouperString(string& a_decouper, Tableau<string>& a_retourner);
    bool langueEstValide(string& langue);
    bool motEstValide(string& mot);
    bool ajouterEstValide(Tableau<string>& entree);
    bool ajouterSynEstValide(Tableau<string>& entree);
    bool ajouterTradEstValide(Tableau<string>& entree);
    bool importerEstValide(Tableau<string>& entree);
    bool importerSynEtTradEstValide(Tableau<string>&entree);
    bool chercherEstValide(Tableau<string>& entree);
    bool chercherSynEstValide(Tableau<string>& entree);
    bool reecrireTexteValide(Tableau<string>& entree);
    bool commandeEstSupportee(Tableau<string>& entree);
    bool checkEnd(const string& mot);

}