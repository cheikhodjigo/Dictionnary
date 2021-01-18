/*  INF3105 - Structures de données et algorithmes
    UQAM | Faculté des sciences | Département d'informatique
    Automne 2017 | Lab8 + TP2
    http://ericbeaudry.uqam.ca/INF3105/lab8/
    http://ericbeaudry.uqam.ca/INF3105/tp2/

    AUTEUR(S):
     (1) Cheikh Omar DJIGO + DJIC22119708
*/
#if !defined(_ARBREMAP___H_)
#define _ARBREMAP___H_

#include "arbreavl.h"

template <class K, class V>
class ArbreMap
{
  private:
    // À compléter : voir la Section 8.11 (Arbres associatifs (Mapping Trees)) des notes de cours.
    class Entree{
        public:
          Entree(const K& c):cle(c),valeur(){}
          K cle;
          V valeur;
          bool operator < (const Entree& e) const { return cle < e.cle; } 
          bool operator > (const Entree& e) const { return cle > e.cle; }             
    };
    ArbreAVL<Entree> entrees;

  public:
    ArbreMap();
    ~ArbreMap();
    void inserer(const K&);
    bool contient(const K&) const;
    void enlever(const K&);
    void vider();
    bool vide() const;
    
    class Iterateur;
    
    // Fonctions pour obtenir un itérateur (position dans l'arbre)    
    Iterateur debut() const;
    Iterateur fin() const;
    Iterateur rechercher(const K&) const;
    Iterateur rechercherEgalOuSuivant(const K&) const;
    Iterateur rechercherEgalOuPrecedent(const K&) const;

    const V& operator[] (const K&) const;
    V& operator[] (const K&);

  public:
      class Iterateur{
        public:
            Iterateur(const ArbreMap& a);
            const V& valeur() const;
            const K& cle() const;
            operator bool() const;
            bool operator!() const;
            bool operator==(const Iterateur&) const;
            bool operator!=(const Iterateur&) const;
        
            const K& operator*() const;

            Iterateur& operator++();
            Iterateur operator++(int);
            Iterateur& operator = (const Iterateur&);
        private:
            const ArbreMap& arbre_associe;
            typename ArbreAVL<Entree>::Iterateur element;

        friend class ArbreMap;
    };
};

template <class K, class V>
ArbreMap<K,V>::ArbreMap(){
}

template <class K, class V>
ArbreMap<K,V>::~ArbreMap(){
    entrees.vider();
}

template <class K, class V>
void ArbreMap<K,V>::inserer(const K& elt){
     entrees.inserer(elt);
}

template <class K, class V>
void ArbreMap<K,V>::vider(){
     entrees.vider();
}

template <class K, class V>
bool ArbreMap<K,V>::vide() const{
    return entrees.vide();
}

template <class K, class V>
void ArbreMap<K,V>::enlever(const K& c)
{
    entrees.enlever(c);
}

template <class K, class V>
bool ArbreMap<K,V>::contient(const K& c) const
{
    return entrees.contient(c);
}

template <class K, class V>
const V& ArbreMap<K,V>::operator[] (const K& c)  const
{
    typename ArbreAVL<Entree>::Iterateur iter = entrees.rechercher(c);
    return entrees[iter].valeur;
}

template <class K, class V>
V& ArbreMap<K,V>::operator[] (const K& c) 
{
    typename ArbreAVL<Entree>::Iterateur iter = entrees.rechercher(c);
    if(!iter){
        entrees.inserer(c);
        iter = entrees.rechercher(c);
    }
    return entrees[iter].valeur;
}
template <class K, class V>
typename ArbreMap<K,V>::Iterateur ArbreMap<K,V>::debut() const
{
    Iterateur iter(*this);
    iter.element = entrees.debut();
    return iter;
}

template <class K, class V>
typename ArbreMap<K,V>::Iterateur ArbreMap<K,V>::fin() const
{
    Iterateur iter(*this);
    iter.element = entrees.fin();
    return iter;
}
template <class K,class V>
typename ArbreMap<K,V>::Iterateur ArbreMap<K,V>::rechercher(const K& c) const
{
    Iterateur iter(*this);
    iter.element = entrees.rechercher(c);
    return iter; 
}

template <class K, class V>
typename ArbreMap<K,V>::Iterateur ArbreMap<K,V>::rechercherEgalOuSuivant(const K& c) const
{
    Iterateur iter(*this);
    iter.element = entrees.rechercherEgalOuSuivant(c);
    return iter;
}

template <class K, class V>
typename ArbreMap<K,V>::Iterateur ArbreMap<K,V>::rechercherEgalOuPrecedent(const K& c) const
{
    Iterateur iter(*this);
    iter.element = entrees.rechercherEgalOuPrecedent(c);
    return iter;
}

template <class K, class V>
ArbreMap<K,V>::Iterateur::Iterateur(const ArbreMap& a)
 : arbre_associe(a), element(a.entrees)
{
}

template <class K, class V>
typename ArbreMap<K,V>::Iterateur& ArbreMap<K,V>::Iterateur::operator++()
{
    ++element;
    return *this;
}

// Post-incrément
template <class K, class V>
typename ArbreMap<K,V>::Iterateur ArbreMap<K,V>::Iterateur::operator++(int)
{
    element++;
    return *this;
}

template <class K, class V>
ArbreMap<K,V>::Iterateur::operator bool() const
{
    if(element)    
        return true;
    else 
        return false;
}

template <class K, class V>
bool ArbreMap<K,V>::Iterateur::operator!() const{
    return !element;
}

template <class K, class V>
bool ArbreMap<K,V>::Iterateur::operator==(const Iterateur& o) const{
    return element == o.element;
}

template <class K, class V>
bool ArbreMap<K,V>::Iterateur::operator!=(const Iterateur& o) const{
    return element != o.element;
}

template <class K, class V>
const K& ArbreMap<K,V>::Iterateur::operator *() const
{
    return *element;
}

template <class K, class V>
typename ArbreMap<K,V>::Iterateur& ArbreMap<K,V>::Iterateur::operator = (const Iterateur& autre){
    element = autre.element;
    return *this;
}

template <class K, class V>
const K& ArbreMap<K,V>::Iterateur::cle() const{
    return arbre_associe.entrees[element].cle;
}

template <class K, class V>
const V& ArbreMap<K,V>::Iterateur::valeur() const{
    return arbre_associe.entrees[element].valeur;
}
#endif

