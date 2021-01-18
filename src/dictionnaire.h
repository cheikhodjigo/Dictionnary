/**
 * INF3105 Structure de donnees
 * Cette classe permet de créer un dictionnaire et de
 * faire les manipulations nécessaires.
 * Auteur: CHEIKH OMAR DJIGO-DJIC22119708
*/
#if !defined(_DICTIONNAIRE___H_)
#define _DICTIONNAIRE___H_

#include <iostream>
#include <fstream>
#include "arbremap.h"
#include "tableau.h" 
#include "utility.cpp"

using namespace std;
using namespace utility;

class Dictionnaire{
  public:
    bool AjouterMot(const string&,const string&);
    bool estTrouveDansSupOuInf(const string&, const string&);
    void AjouterSynonyme(const string&, const string&, const string&);
    void AjouterTraduct(const string&, const string&, const string&, 
                        const string&);
    void importer(const string&, const string&);
    bool voirDansSupOuInf(const string&, const string&);
    void chercherMot(const string&);
    void chercherLangue(const string&);
    void chercher(const string&, const string&);
    void chercherSynonyme(const string&,const string&);
    void chercherTraduction(const string&,const string&);
    void supprimerSynonyme(const string&,const string&);
    void supprimerTraduction(const string&, const string&);
    void supprimerMot(const string&);
    void supprimerLangue(const string&);
    void supprimer(const string&, const string&);
    void importerSynonyme(const string&,const string&, const string&);
    void importerTraduction(const string&,const string&, const string&);
    void AjoutRecursifSyn(const string&, const string&, const string&);
    void AjoutRecursifARef(const string&, const string&, const string&);
    Tableau<string>& reecrireTexte(const string&, Tableau<string>&);

    class MotA;

  private:
    ArbreMap<string, ArbreMap<string, MotA> > mots; // langue --> mot --> objet Mot
    
  public:
    class MotA
    {
        ArbreAVL<string> synonymes; // Synonymes
        ArbreMap<string, ArbreAVL<string> > traductions; // langue --> Traductions
        friend class Dictionnaire;
    };
};

/**
* Cette méthode ajoute un mot au dictionnaire dans la langue spécifiée.
*
* @params nouveautMot   C'est le mot à ajouter
* @params langue        C'est la langue du mot à ajouter 
* @return Vrai ou Faux si le mot est ajouté où pas
*/
bool Dictionnaire::AjouterMot(const string& nouveauMot, const string& langue)
{
    if(mots.contient(langue)){
        if(mots[langue].contient(nouveauMot)){
            //cout << "Mot existant !"<< endl;
            return false;
        }else{
            ArbreMap<string, MotA>::Iterateur iter = mots[langue].rechercherEgalOuPrecedent(nouveauMot);
            if(iter){
                if(!estTrouveDansSupOuInf(iter.cle(),nouveauMot)){
                    iter = mots[langue].rechercherEgalOuSuivant(nouveauMot);
                    if(iter){
                        if(!estTrouveDansSupOuInf(iter.cle(),nouveauMot)){
                            mots[langue].inserer(nouveauMot);
                            return true;
                        }
                    }
                }
            }else{
                mots[langue].inserer(nouveauMot);
                return true;
            }
            //mots[langue].inserer(nouveauMot);
            //return true;
        }
    }else{
        mots.inserer(langue);
        mots[langue].inserer(nouveauMot);
        return true;
    }
    return false;
}

bool Dictionnaire::estTrouveDansSupOuInf(const string& mot,const string& nouveauMot){
    if(mot.size() != nouveauMot.size())
        return false;
    for(int i = 0;i<mot.size();i++){
        char lettreMot = mot[i];
        char lettreNewMot = nouveauMot[i];
        if(toupper(lettreMot) != toupper(lettreNewMot))
            return false;
    }
    return true;
}

bool Dictionnaire::voirDansSupOuInf(const string& langue,const string& nouveauMot){
    if(!mots[langue].contient(nouveauMot)){
        ArbreMap<string, MotA>::Iterateur iter = mots[langue].rechercherEgalOuPrecedent(nouveauMot);
        if(iter){
            if(!estTrouveDansSupOuInf(iter.cle(),nouveauMot)){
                iter = mots[langue].rechercherEgalOuSuivant(nouveauMot);
                if(iter){
                    if(estTrouveDansSupOuInf(iter.cle(),nouveauMot)){
                        //mots[langue].inserer(nouveauMot);
                        return true;
                    }
                }
            }else{
                return true;
            }
        }
    }else{
        return true;
    }
    return false;
}

/**
 * Cette methode ajoute un nouveau synonymes au mot de référence dans la langue
 * spécifiée.
 * 
 * @params ref          Le mot auquel on doit ajouter une référence
 * @params nouveauSyn   Le synonyme à ajouter
 * @params langue       La langue dans laquelle on doit ajouter le synonyme   
 */
void Dictionnaire::AjouterSynonyme(const string& ref, const string& nouveauSyn,
    const string& langue)
{
    if(ref.compare(nouveauSyn)){
        if(mots[langue].contient(ref)){
            if(mots[langue].contient(nouveauSyn)){
                AjoutRecursifSyn(ref,nouveauSyn,langue);
            }else{
                mots[langue].inserer(nouveauSyn);
                ArbreAVL<string>::Iterateur iter = mots[langue][ref].synonymes.debut();
                while(iter){
                    if(nouveauSyn.compare(*iter)){
                        mots[langue][*iter].synonymes.inserer(nouveauSyn);
                        mots[langue][nouveauSyn].synonymes.inserer(*iter);
                    }
                    ++iter;
                }
                mots[langue][ref].synonymes.inserer(nouveauSyn);
                mots[langue][nouveauSyn].synonymes.inserer(ref);
                //AjoutRecursifSyn(ref,nouveauSyn,langue);
            }
        }else{
            mots[langue].inserer(ref);
            if(mots[langue].contient(nouveauSyn)){
                AjoutRecursifARef(ref,nouveauSyn,langue);
            }else{
                mots[langue].inserer(nouveauSyn);
                mots[langue][nouveauSyn].synonymes.inserer(ref);
                mots[langue][ref].synonymes.inserer(nouveauSyn);
            }
        }
    }
}

/**
 * Cette methode ajoute récursivement à chaque synonyme de ref les synonymes
 * de nouveau mot et vice verca. Ensuite il ajoute ref aux synonymes de nouveauMot
 * et vice verca.
 * 
 * @params ref          Le mot auquel on doit ajouter une référence
 * @params nouveauSyn   Le synonyme à ajouter
 * @params langue       La langue dans laquelle on doit ajouter le synonyme   
 */
void Dictionnaire::AjoutRecursifSyn(const string& ref, const string& nouveauSyn,
    const string& langue)
{
    ArbreAVL<string>::Iterateur iter1 = mots[langue][nouveauSyn].synonymes.debut();
    if(iter1){
        while(iter1){
            ArbreAVL<string>::Iterateur iter2 = mots[langue][ref].synonymes.debut();
            while(iter2){
                if(*iter1 != *iter2){
                    mots[langue][*iter1].synonymes.inserer(*iter2);
                    mots[langue][*iter2].synonymes.inserer(*iter1);
                }   
                ++iter2;
            }   
            ++iter1;
        }
    }else{
        ArbreAVL<string>::Iterateur iter2 = mots[langue][ref].synonymes.debut();
        while(iter2){
            mots[langue][nouveauSyn].synonymes.inserer(*iter2);
            mots[langue][*iter2].synonymes.inserer(nouveauSyn);
            ++iter2;
        }   
    }    
    mots[langue][ref].synonymes.inserer(nouveauSyn);
    mots[langue][nouveauSyn].synonymes.inserer(ref);
}

/**
 * Cette methode ajoute aussi tous les synonymes de nouveauMot aux synonymes de ref.
 * 
 * @params ref          Le mot auquel on doit ajouter une référence
 * @params nouveauSyn   Le synonyme à ajouter
 * @params langue       La langue dans laquelle on doit ajouter le synonyme   
 */
void Dictionnaire::AjoutRecursifARef(const string& ref, const string& nouveauSyn,
    const string& langue)
{

    ArbreAVL<string>::Iterateur iter = mots[langue][nouveauSyn].synonymes.debut();
    while(iter){
        if(ref.compare(*iter)){
            mots[langue][*iter].synonymes.inserer(ref);
            mots[langue][ref].synonymes.inserer(*iter);
        }
        ++iter;
    }
    mots[langue][ref].synonymes.inserer(nouveauSyn);
    mots[langue][nouveauSyn].synonymes.inserer(ref);
}

/**
 * Cette methode permet d'ajouter des traductions à un mot 
 * dans le dictionnaire.
 * @params langue       La langue appartenant au mot 
 * @params langue_trad  La langue de traduction
 * @params mot_ref      Le mot auquel on ajoute une traduction
 * @params mot          La traduction à ajouter 
*/
void Dictionnaire::AjouterTraduct(const string& langue, const string& langue_trad, 
                                const string& mot_ref, const string& nouveauMot)
{
    if(!mots[langue].contient(mot_ref))
        mots[langue].inserer(mot_ref);
    if(!mots[langue_trad].contient(nouveauMot))
        mots[langue_trad].inserer(nouveauMot);
    ArbreAVL<string>::Iterateur iter_ref = mots[langue][mot_ref].traductions[langue_trad].debut(); 
    ArbreAVL<string>::Iterateur iter_trad = mots[langue_trad][nouveauMot].traductions[langue].debut();
    if(iter_ref){
        if(iter_trad){
            while(iter_ref){
                while(iter_trad){
                    mots[langue_trad][*iter_ref].traductions[langue].inserer(*iter_trad);
                    mots[langue][*iter_trad].traductions[langue_trad].inserer(*iter_ref);
                    ++iter_trad;
                }
                ++iter_ref;
            }
        }else{
            while(iter_ref){
                mots[langue_trad][nouveauMot].synonymes.inserer(*iter_ref);
                mots[langue_trad][*iter_ref].synonymes.inserer(nouveauMot);
                ++iter_ref;
            }
        }
    }else{
        while(iter_trad){
            mots[langue][*iter_trad].traductions[langue_trad].inserer(mot_ref);
            ++iter_trad;
        }
    }
    mots[langue][mot_ref].traductions[langue_trad].inserer(nouveauMot);
    mots[langue_trad][nouveauMot].traductions[langue].inserer(mot_ref);
      
}  

void Dictionnaire::importer(const string& langue, const string& dossier)
{
    string mot;
    bool estValide=true;
    ifstream myfile(dossier.c_str());
	if(!myfile){
		cout << "Fichier introuvable!"<<endl;	
	}else{
        while(getline(myfile,mot)){
            while(isspace(mot[mot.size()-1]))
                mot = mot.substr(0,mot.size()-1);
            if(motEstValide(mot)){
                if(AjouterMot(mot,langue))
                    cout <<"Ajouter "<< langue << " " <<mot <<endl;
            }else{
                cout << "Parametre Invalide!"<< endl;
            }
        }
    }
	myfile.close();
}

void Dictionnaire::importerSynonyme(const string& langue, const string& mot_ref,const string& dossier)
{
    string mot;
    Tableau<string>desMots;
    bool estImporter = false;
    ifstream myfile(dossier.c_str());
	if(!myfile){
		cout << "Fichier introuvable!"<<endl;	
	}else{
        estImporter =true;
        while(getline(myfile,mot)){
            while(isspace(mot[mot.size()-1]))
                mot = mot.substr(0,mot.size()-1);
            if(motEstValide(mot)){
                AjouterSynonyme(mot_ref,mot,langue);
                desMots.ajouter(mot);
            }else{
                cout << "Parametre Invalide!"<< endl;
            }
        }
    }
    if(estImporter){
        cout << "AjouterSynonyme " << langue << " "<< mot_ref << " ";
        for(int i =0;i <desMots.taille();i++)
            cout << desMots[i]<< " ";
        cout << endl;
    }
	myfile.close();
}

void Dictionnaire::importerTraduction(const string& langue, const string& mot_ref,const string& dossier)
{
    string mot;
    string mot_actuel;
    bool estImporter = false;
    Tableau<string>entree;
    Tableau<string>lesLangues;
    Tableau<string>lesMots;
    ifstream myfile(dossier.c_str());
	if(!myfile){
		cout << "Fichier introuvable!" <<  endl;	
	}else{
        estImporter = true;
        while(getline(myfile,mot)){
            entree = decouperString(mot,entree);
            if(entree.taille() == 2 && motEstValide(entree[0]) 
                && langueEstValide(entree[1])){
                AjouterTraduct(langue,entree[1],mot_ref,entree[0]);
                if(lesLangues.chercher(entree[1]) == -1)
                    lesLangues.ajouter(entree[1]);
                mot_actuel = entree[1] + entree[0];
                lesMots.ajouter(mot_actuel);
            }else{
                cout << "Parametre Invalide!"<< endl;
            }
        }    
    }
    if(estImporter){
        cout << "AjouterTraduction " << langue << " " << mot_ref << " ";
        for(int i = 0;i< lesLangues.taille();i++){
            cout << lesLangues[i]<< " ";
            for(int j = 0;j< lesMots.taille();j++){
                string cherche = lesMots[j].substr(0,4);
                if(cherche == lesLangues[i]){
                    cout << lesMots[j].substr(4,lesMots[j].size()-4)<< " ";
                }
            }
        }
        cout <<endl;
    }
	myfile.close();
}

void Dictionnaire::chercherMot(const string& mot){
    if(!mot.compare("*")){
        ArbreMap<string, ArbreMap <string,MotA> >::Iterateur iter = mots.debut();
        while(iter){
            cout << iter.cle() << endl;
            ArbreMap<string,MotA>::Iterateur iter1 = mots[iter.cle()].debut();
            while(iter1){
                cout << iter1.cle() << endl;
                ++iter1;
            }
            ++iter;
        }
    }else{
        ArbreMap<string, ArbreMap <string,MotA> >::Iterateur iter = mots.debut();
        bool estContenu =false;
        while(iter){
            if(mots[iter.cle()].contient(mot)){
                cout << iter.cle() << endl;
                cout << mots[iter.cle()].rechercher(mot).cle() << endl;
                estContenu = true;
            }
            ++iter;
        }
        if(!estContenu)
            cout << "Mot inexistant!"<<endl;
    }
}

void Dictionnaire::chercherLangue(const string& langue){
    if(mots.contient(langue)){
        ArbreMap<string,MotA>::Iterateur iter = mots[langue].debut();
        while(iter){
            cout << iter.cle() << endl;
            ++iter;
        }
    }else{
        cout << "Mot inexistant!"<<endl;
    }
}

void Dictionnaire::chercher(const string& langue, const string& mot){
    if(mots.contient(langue)){
        if(mots[langue].contient(mot)){
            cout << mots[langue].rechercher(mot).cle() << endl;
        }else{
            cout << "Mot inexistant!"<<endl;
        }
    }else{
        cout << "Mot inexistant!"<<endl;
    }
}

void Dictionnaire::supprimerMot(const string& mot){
    if(!mot.compare("*")){
        ArbreMap<string, ArbreMap <string,MotA> >::Iterateur iter = mots.debut();
        while(iter){
            cout << iter.cle() << endl;
            ArbreMap<string,MotA>::Iterateur iter1 = mots[iter.cle()].debut();
            while(iter1){
                cout << iter1.cle() << endl;
                mots[iter.cle()].enlever(iter1.cle());
                ++iter1;
            }
            mots[iter.cle()].enlever(iter.cle());
            ++iter;
        }
        mots.vider();
    }else{
        ArbreMap<string, ArbreMap <string,MotA> >::Iterateur iter = mots.debut();
        while(iter){
            if(mots[iter.cle()].contient(mot)){
                cout << iter.cle() << endl;
                cout << mots[iter.cle()].rechercher(mot).cle() << endl;
                mots[iter.cle()].enlever(mot);
            }
            ++iter;
        }
    }
}

void Dictionnaire::supprimerLangue(const string& langue){
    if(mots.contient(langue)){
        ArbreMap<string,MotA>::Iterateur iter = mots[langue].debut();
        while(iter){
            cout << iter.cle() << endl;
            ++iter;
        }
        mots.enlever(langue);
    }
}

void Dictionnaire::supprimer(const string& langue, const string& mot){
    if(mots.contient(langue)){
        if(mots[langue].contient(mot)){
            cout << mots[langue].rechercher(mot).cle() << endl;
            mots[langue].enlever(mot);
        }
    }
    
}

void Dictionnaire::chercherSynonyme(const string& langue,const string& mot){
    if(mots[langue].contient(mot)){
        if(!mots[langue][mot].synonymes.vide()){
            ArbreAVL<string>::Iterateur iter = mots[langue][mot].synonymes.debut();
            while(iter){
                cout << *iter << endl;
                ++iter;
            }
        }else{
            cout << "Mot inexistant!"<<endl;
        }
    }else{
        cout << "Mot inexistant!"<<endl;
    }
}

void Dictionnaire::chercherTraduction(const string& langue,const string& mot){
    if(mots[langue].contient(mot)){
        if(!mots[langue][mot].traductions.vide()){
            ArbreMap<string,ArbreAVL<string> >::Iterateur iter = mots[langue][mot].traductions.debut();
            while(iter){
                cout << iter.cle() << endl;
                ArbreAVL<string>::Iterateur iter1 = mots[langue][mot].traductions[iter.cle()].debut();
                while(iter1){
                    cout << *iter1 << endl;
                    ++iter1;        
                }
                ++iter;
            }
        }else{
            cout << "Mot inexistant!"<<endl;
        }
    }else{
        cout << "Mot inexistant!"<<endl;
    }
}

void Dictionnaire::supprimerSynonyme(const string& langue, const string& mot){
    if(!mots[langue][mot].synonymes.vide()){
        ArbreAVL<string>::Iterateur iter = mots[langue][mot].synonymes.debut();
        while(iter){
            cout << *iter << endl;
            mots[langue][*iter].synonymes.enlever(mot);
            ++iter;
        }
        mots[langue][mot].synonymes.vider();
    }
}

void Dictionnaire::supprimerTraduction(const string& langue, const string& mot){
    if(!mots[langue][mot].traductions.vide()){
        ArbreMap<string,ArbreAVL<string> >::Iterateur iter = mots[langue][mot].traductions.debut();
        while(iter){
            cout << iter.cle() << endl;
            ArbreAVL<string>::Iterateur iter1 = mots[langue][mot].traductions[iter.cle()].debut();
            while(iter1){
                cout << *iter1 << endl;
                mots[iter.cle()][*iter1].traductions[langue].enlever(mot);
                //if(mots[iter.cle()][*iter1].traductions[langue].vide()){
                //    mots[iter.cle()][*iter1].traductions.enlever(langue);
                //}
                ++iter1;        
            }
            ++iter;
        }
    }
    mots[langue][mot].traductions.vider();
}

Tableau<string>& Dictionnaire::reecrireTexte(const string& langue,Tableau<string>& texte){
    /*Tableau<ArbreAVL<string>::Iterateur> tabIter;
    for(int i = 0;i<texte.taille();i++){
        if(voirDansSupOuInf(langue,texte[i])){
            if(!mots[langue][texte[i]].synonymes.vide()){
                for(int j = 0;j<tabIter.taille();j++){
                    if(!mots[langue][*tabIter[j]].synonymes.contient(texte[i])){
                        ArbreAVL<string>::Iterateur iter1= mots[langue][texte[i]].synonymes.debut();
                        texte[i] = *iter1;
                        ++iter1;
                        tabIter.ajouter(iter1);
                    }else{
                        texte[i] = tabIter[j];
                        ++tabIter[j];
                        
                    }
                }
            }
        }
    }*/
    return texte;
}

#endif //define _DICTIONNAIRE___H_

