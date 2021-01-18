/*
    INF3105 Structure de donnees
    Cette classe est la main classe du tp2
    Auteur: CHEIKH OMAR DJIGO-DJIC22119708
*/

#include <iostream>
#include "tableau.h"
#include "dictionnaire.h"
#include "utility.hpp"

using namespace std; 
using namespace utility;

/**
 * La methode main du projet 
 * @return le code d'erreur si une erreur c'est produite.
*/
int main(){
    // Déclaration de variable local
    Dictionnaire dict;
    string mot;
    Tableau<string> entree; 

    // Début du code
    getline(cin, mot);
    entree = decouperString(mot,entree);
    while(!commandeEstSupportee(entree)){
        getline(cin, mot);
        entree = decouperString(mot,entree);
    }
    while(entree[0].compare("Quitter")){
        if(!entree[0].compare("Ajouter")){
            if(ajouterEstValide(entree))
                dict.AjouterMot(entree[2],entree[1]);
            else
                cout << "Parametre Invalide!" << endl;
        }else if(!entree[0].compare("AjouterSynonyme")){
            if(ajouterSynEstValide(entree)){
                for(int i = 3;i<entree.taille();i++){
                    dict.AjouterSynonyme(entree[2],entree[i],entree[1]);
                }
            }else{
                cout << "Parametre Invalide!" << endl;
            }
        }else if(!entree[0].compare("AjouterTraduction")){
            if(ajouterTradEstValide(entree)){
                for(int i = 4;i<entree.taille();i++){
                    dict.AjouterTraduct(entree[1],entree[3],entree[2],entree[i]);
                }
            }else{
                cout << "Parametre Invalide!" << endl;
            }
        }else if(!entree[0].compare("Importer")){
            if(importerEstValide(entree)){
                dict.importer(entree[1],entree[2]);
            }else{
                cout << "Parametre Invalide!" << endl;
            }
        }else if(!entree[0].compare("ImporterSynonyme")){
            if(importerSynEtTradEstValide(entree)){
                dict.importerSynonyme(entree[1],entree[2],entree[3]);
            }else{
                cout << "Parametre Invalide!" << endl;
            }
        }else if(!entree[0].compare("ImporterTraduction")){
            if(importerSynEtTradEstValide(entree)){
                dict.importerTraduction(entree[1],entree[2],entree[3]);
            }else{
                cout << "Parametre Invalide!" << endl;
            }
        }else if(!entree[0].compare("Chercher")){
            if(chercherEstValide(entree)){
                if(entree.taille() == 2){
                    if(!entree[1].compare("*"))
                        dict.chercherMot(entree[1]);
                    else if (motEstValide(entree[1]))
                        dict.chercherMot(entree[1]);
                    else if (langueEstValide(entree[1]))
                        dict.chercherLangue(entree[1]);
                }else{
                    dict.chercher(entree[1],entree[2]);
                }
            }else{
                cout << "Parametre Invalide!" << endl;
            }
        }else if (!entree[0].compare("Supprimer")){
            if(chercherEstValide(entree)){
                if(entree.taille() == 2){
                    if(!entree[1].compare("*"))
                        dict.supprimerMot(entree[1]);
                    else if (motEstValide(entree[1]))
                        dict.supprimerMot(entree[1]);
                    else if (langueEstValide(entree[1]))
                        dict.supprimerLangue(entree[1]);
                }else{
                    dict.supprimer(entree[1],entree[2]);
                }
            }else{
                cout << "Parametre Invalide!" << endl;
            }
        }else if (!entree[0].compare("ChercherSynonyme")){
            if(chercherSynEstValide(entree)){
                dict.chercherSynonyme(entree[1],entree[2]);
            }else{
                cout << "Parametre Invalide!" << endl;
            }
        }else if (!entree[0].compare("SupprimerSynonyme")){
            if(chercherSynEstValide(entree)){
                dict.supprimerSynonyme(entree[1],entree[2]);
            }else{
                cout << "Parametre Invalide!" << endl;
            }
        }else if (!entree[0].compare("ChercherTraduction")){
            if(chercherSynEstValide(entree)){
                dict.chercherTraduction(entree[1],entree[2]);
            }else{
                cout << "Parametre Invalide!" << endl;
            }
        }else if (!entree[0].compare("SupprimerTraduction")){
            if(chercherSynEstValide(entree)){
                dict.supprimerTraduction(entree[1],entree[2]);
            }else{
                cout << "Parametre Invalide!" << endl;
            }
        }else if(!entree[0].compare("ReecrireTexte")){
            if(reecrireTexteValide(entree)){

            }
        }
        else{
            cout << "Commande non supportee!" << endl;
        }

        getline(cin, mot);
        entree = decouperString(mot,entree);
        while(!commandeEstSupportee(entree)){
            getline(cin, mot);
            entree = decouperString(mot,entree);
        }
    }
    
    return 0;
}