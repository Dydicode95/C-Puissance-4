#pragma once

#include "joueur.hpp"

template <typename P>
class Partie {
private:
    P pCourante;
    Joueur<P>& j1;
    Joueur<P>& j0;
    bool affichage;
    //Resultat r;

public:
    Partie(Joueur<P>& j1, Joueur<P>& j0, P pInitiale, bool aff = true);
    Resultat r;
    void Commencer();
};
