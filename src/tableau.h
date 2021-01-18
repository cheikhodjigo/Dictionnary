/* UQAM / Département d'informatique
   INF3105 - Structures de données et algorithmes
   Squelette pour classe générique Tableau<T> pour le TP1 et Lab3.

   AUTEUR(S):
    1) Nom + Code permanent du l'étudiant.e 1
    2) Nom + Code permanent du l'étudiant.e 2
*/

#if !defined(_TABLEAU___H_)
#define _TABLEAU___H_

#include <assert.h>
#include <iostream>
template <class T>
class Tableau{

  public:
    Tableau(int capacite_initiale=4);
    Tableau(const Tableau&);
    ~Tableau();

    // Ajouter un element à la fin
    void           ajouter(const T& element);
    // Vider le tableau
    void           vider();
    // Retourne le nombre d'éléments dans le tableau
    int            taille() const;

    // Insère element à position index. Les éléments à partir de index sont décalés d'une position.
    void           inserer(const T& element, int index=0);

    void           afficher();
    // Enlève l'element à position index. Les éléments après index sont décalés d'une position après.
    void           enlever(int index=0);

    // Cherche et retourne la position de l'élément. Si non trouvé, retourne -1.
    int            chercher(const T& element) const;

    const T*       giveT() const;
    
    const T        operator[] (int index) const;
    T&             operator[] (int index);

    bool           operator == (const Tableau<T>& autre) const;
    Tableau<T>&    operator = (const Tableau<T>& autre);

  private:
    T*             elements;
    int            nbElements;
    int            capacite;
};


// ---------- Définitions -------------


template <class T>
Tableau<T>::Tableau(int capacite_)
{
    capacite = capacite_;
    nbElements = 0;
    elements = new T[capacite];
}

template <class T>
Tableau<T>::Tableau(const Tableau& autre)
{
    nbElements = autre.nbElements;
    capacite = autre.nbElements;
    elements = new T[capacite];
    for(int i = 0;i<autre.nbElements;i++){
        elements[i] = autre.elements[i];
    }    
}

template <class T>
Tableau<T>::~Tableau()
{
    delete[]elements; 
}


template <class T>
int Tableau<T>::taille() const
{   
    return nbElements;
}

template <class T>
void Tableau<T>::ajouter(const T& item)
{
    if (nbElements<capacite){
        elements[nbElements++] = item;
    }else{
        capacite*=2;
        T* copie =  new T[capacite];
        for(int i =0;i<nbElements;i++){
            copie[i]= elements[i];
        }
        delete[]elements;
        elements = copie;
        elements[nbElements++] = item;
    }
}

template <class T>
void Tableau<T>::inserer(const T& element, int index)
{    
    int get_nbEl = nbElements;
    if(index < get_nbEl){
        ajouter(elements[get_nbEl-1]);
        for(int i =get_nbEl-1;i!=index;i--){
            elements[i] = elements[i-1];
        }
        elements[index]=element;
    }
}

template <class T>
void Tableau<T>::enlever(int index)
{
    int get_nbEl = nbElements;
    if(index < get_nbEl){
        for(int i =index;i<nbElements;i++){
            elements[i] = elements[i+1];
        }
        nbElements--;
    }
}

template <class T>
int Tableau<T>::chercher(const T& element) const
{
    for(int i=0;i<nbElements;i++){
        if(elements[i] == element)
            return i;
    }
    return -1;
}

template <class T>
void Tableau<T>::vider()
{   
    delete [] elements;
    elements = NULL;
    capacite=4;
    elements= new T[capacite];
    nbElements=0;
}

template <class T>
const T Tableau<T>::operator[] (int index) const
{
    assert(index <= capacite);
    return elements[index];
}

template <class T>
T& Tableau<T>::operator[] (int index)
{
    assert(index <= capacite);
    return elements[index];
}

template <class T>
Tableau<T>& Tableau<T>::operator = (const Tableau<T>& autre)
{
    if(!(this == &autre)){
        capacite = autre.capacite;
        nbElements = autre.nbElements;
        delete[]elements;
        elements = new T[capacite];
        for (int i= 0;i<capacite;i++){
            elements[i] = autre[i];
        }
    }
    return *this;
}

template <class T>
bool Tableau<T>::operator == (const Tableau<T>& autre) const
{
    if((capacite == autre.capacite) && (nbElements == autre.nbElements)){
        for(int i = 0;i<nbElements;i++){
            if(elements[i]!=autre.elements[i])
                return false;
        }  
        return true; 
    }
    return false;
}

template<class T>
const T* Tableau<T>::giveT() const{
    return elements;
}

template<class T>
void Tableau<T>::afficher(){
    for(int i = 0;i<nbElements;i++){
        std::cout << elements[i] << std::endl;
    }
}
#endif //define _TABLEAU___H_


