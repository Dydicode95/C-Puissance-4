#include "JMCTS.hpp"

#include <ctime>
std::random_device rd;
std::default_random_engine e(rd());
template <typename P>
JMCTS<P>::JMCTS(double a, unsigned temps) : a(a), temps(temps) {
    this->nom = "JMCTS(a=" + std::to_string(a) + ",temps=" + std::to_string(temps) + ")";
}

template <typename P>
unsigned JMCTS<P>::JeuHasard(P p) const {
    unsigned re = 1;
    while (p.ColonnesNonPleines().size() > 0) {
        std::vector<unsigned> colonnesNonPleines = p.ColonnesNonPleines();
        unsigned a = colonnesNonPleines[e() % colonnesNonPleines.size()];
        p.EffectuerCoup(a);   
    } // Le pb de mon code c'est que il se termine à cette ligne !
    if (p.Eval() == Resultat::j1gagne) { re = 2; }
    if (p.Eval() == Resultat::j0gagne) { re = 0; }
    return re;
}

template <typename P>
unsigned JMCTS<P>::Jouer(P p) {
    std::clock_t t0 = std::clock();
    std::clock_t t1 = t0 + temps * (CLOCKS_PER_SEC / 1000); // En résumé, ce code utilise std::clock() pour enregistrer le temps actuel dans t0, puis calcule le moment où un temps spécifié en millisecondes sera écoulé depuis t0, et stocke ce moment dans t1.
    racine = new noeud<P>(nullptr, p); // racine = new noeud<P4>(nullptr, pCourante); : Cette ligne crée un nouvel objet de type noeud<P4> (nœud), alloue de la mémoire pour cet objet en utilisant l'opérateur new, et l'initialise en appelant le constructeur noeud<P4>(nullptr, pCourante).
    unsigned iter = 0;
    while (std::clock() < t1) {
        noeud<P>* no = racine; // no est un pointeur sur une instance de la classe noeud

        do // Sélection
        {
            no->CalculMeilleurFils(a); // appel de la méthode CalculMeilleurFils() qui ne renvoie rien mais 
            no = no->MeilleurFils(); // 

        } while (no->cross > 0 && no->nbfils > 0);

        unsigned re = JeuHasard(no->p); // Simulation
        while (no != nullptr) // Rétropropagation
        {
            no->cross += 2;
            no->win += re;
            no = no->pere;
        }
        ++iter;
    }
    // il faut qu'avant de calculer le meilleur fils, lui obliger de choisir parmi les colonnes non pleines ! donc il faut afficher le plateau de jeu de racine
    P4 plateauCopie = racine->p;
    std::cout << plateauCopie.ToString() << std::endl;
    std::cout<<"Voici l'état actuel du plateau"<<std::endl;
    racine->CalculMeilleurFils(a);
    this->message = std::to_string(iter) + " itérations\n";
    this->message += racine->ToString();
    //unsigned res = racine->indiceMeilleurFils;
    unsigned res = p.ColonnesNonPleines()[racine->indiceMeilleurFils];
    delete racine;
    return res;
}