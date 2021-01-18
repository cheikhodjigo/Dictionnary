#include <iostream>
#include "utility.hpp"

namespace utility
{
    /**
     * Cette methode permet de separer le mot passer en paramétre en plusieurs mots
     * qui à l'aide des espaces.
     * @params a_decouper   le mot qu'on doit découper
     * @params a_retourner  le tableau dans lequelle on va placer les mots
     * @return              le nouveau tableau contenant les mots
     */
    Tableau<string>& decouperString(string& a_decouper, Tableau<string>& a_retourner)
    {
        //Tableau<string> *a_retourner = new Tableau<string>();
        a_retourner.vider();
        string mot;
        for(int i = 0; i < a_decouper.size();i++){
            if(isspace(a_decouper[i])){
                if(mot.size()!= 0)
                    a_retourner.ajouter(mot);
                    mot = "";
            }else{
                mot += a_decouper[i];
            }
        }
        if(mot.size() != 0)
            a_retourner.ajouter(mot);
        return a_retourner;
    }


    /**
     *  Cette methode verifie si le format de la langue est respecté.
     * @params langue   le mot qu'il faut analyser
     * @return          Vrai si le format est bon, faux sinon.
     */
    bool langueEstValide(string& langue){
        if(langue.size() != 4)
            return false;
        if(langue[0] != '[')
            return false;
        if((langue[1] < 'A' || langue[1] > 'Z') || (langue[2] < 'A' || langue[2] > 'Z'))
            return false;
        if(langue[3] != ']')
            return false;
        return true;
    }

    /**
     * Cette méthode permet de vérifier si le mot contient des caractéres numériques uniquement.
     * @params mot  le mot à vérifier
     * @return      vrai si le mot est valide ou faux sinon
    */
    bool motEstValide(string& mot){
        for(int i = 0;i < mot.size();i++){
            if((mot[i] < 'a' || mot[i] > 'z') && (mot[i] < 'A' || mot[i] > 'Z'))
                return false;
        }
        return true;
    }

    /**
     * Cette méthode permet de vérifier si le tableau d'entrées est valide 
     * pour la commande Ajouter.
     * @params entree   le tableau à vérifier
     * @return          vrai si le tableau est valide ou faux sinon
    */
    bool ajouterEstValide(Tableau<string>& entree){
        if(entree.taille() != 3)
            return false;
        if(!langueEstValide(entree[1]))
            return false;
        if(!motEstValide(entree[2]))
            return false;
        return true;
    }

    /**
     * Cette méthode permet de vérifier si le tableau d'entrées est valide 
     * pour la commande Ajouter Synonyme.
     * @params entree   le tableau à vérifier
     * @return          vrai si le tableau est valide ou faux sinon
    */
    bool ajouterSynEstValide(Tableau<string>& entree){
        if(entree.taille() < 3)
            return false;
        if(!langueEstValide(entree[1]))
            return false;
        for(int i = 2; i < entree.taille();i++){
            if(!motEstValide(entree[i]))
                return false;
        }
        return true;
    }

    /**
     * Cette méthode permet de vérifier si le tableau d'entrées est valide 
     * pour la commande Ajouter Traduction.
     * @params entree   le tableau à vérifier
     * @return          vrai si le tableau est valide ou faux sinon
    */
    bool ajouterTradEstValide(Tableau<string>& entree){
        if(entree.taille() < 5)
            return false;
        if(!langueEstValide(entree[1]))
            return false;
        if(!langueEstValide(entree[3]))
            return false;
        for(int i = 4; i < entree.taille();i++){
            if(!motEstValide(entree[i]))
                return false;
        }
        return true;
    }

    /**
     * Cette méthode permet de vérifier si le tableau d'entrées est valide 
     * pour la commande importer.
     * @params entree   le tableau à vérifier
     * @return          vrai si le tableau est valide ou faux sinon
    */
    bool importerEstValide(Tableau<string>& entree){
        if(entree.taille() != 3)
            return false;
        if(!langueEstValide(entree[1]))
            return false;
        string extension = entree[2].substr(entree[2].size()-4,4);
        if(extension.compare(".txt"))
            return false;
        return true;
    }

    /**
     * Cette méthode permet de vérifier si le tableau d'entrées est valide 
     * pour la commande importer synonyme.
     * @params entree   le tableau à vérifier
     * @return          vrai si le tableau est valide ou faux sinon
    */
    bool importerSynEtTradEstValide(Tableau<string>& entree){
        if(entree.taille() != 4)
            return false;
        if(!langueEstValide(entree[1]))
            return false;
        if(!motEstValide(entree[2]))
            return false;
        return true;
    }

    /**
     * Cette méthode permet de vérifier si le tableau d'entrées est valide 
     * pour la commande importer synonyme.
     * @params entree   le tableau à vérifier
     * @return          vrai si le tableau est valide ou faux sinon
    */
    bool chercherEstValide(Tableau<string>& entree){
        if(entree.taille() != 2 && entree.taille() !=3)
            return false;
        if(entree.taille() == 2){
            if(motEstValide(entree[1]))
                return true;
            else if(langueEstValide(entree[1]))
                return true;
            else if(!entree[1].compare("*"))
                return true;
        }else{
            if(!langueEstValide(entree[1]))
                return false;
            else
                return motEstValide(entree[2]);    
        }
        return false;
    }

    bool chercherSynEstValide(Tableau<string>& entree){
        if(entree.taille() != 3)
            return false;
        if(!langueEstValide(entree[1]))
            return false;
        if(!motEstValide(entree[2]))
            return false;
        return true;
    }

    /**
     * Cette méthode permet de vérifier si le tableau de commande est valide 
     * @params commande le tableau à vérifier
     * @return          vrai si le tableau est valide ou faux sinon
    */
    bool commandeEstSupportee(Tableau<string>& commande){
        if(commande.taille() == 0){
            cout << "Commande non supportee !"<<endl;
            return false;
        }else if (commande.taille() == 1 &&  (!commande[0].compare("Ajouter") || 
            !commande[0].compare("AjouterSynonyme") || !commande[0].compare("AjouterTraduction")
            || !commande[0].compare("Importer") || !commande[0].compare("ImporterSynonyme") || 
            !commande[0].compare("ImporterTraduction") || !commande[0].compare("Chercher") ||
            !commande[0].compare("Supprimer") || !commande[0].compare("ChercherSynonyme") ||
            !commande[0].compare("SupprimerSynonyme") || !commande[0].compare("SupprimerTraduction") 
            || !commande[0].compare("ChercherTraduction") || !commande[0].compare("RecrireTexte") ||
            !commande[0].compare("TraduireTexte"))){
            cout << "Aucune entree!" << endl;
            return false;
        }
        return true;
    }

    bool reecrireTexteValide(Tableau<string>& entree){
        if(!langueEstValide(entree[1]))
            return false;
        return true;
    }

    bool checkEnd(const string& mot){
        char a = mot[mot.size()-1];
        if((a < 'A' || a > 'Z') || (a < 'A' || a > 'Z'))
            return false;
        return true;
    }

}