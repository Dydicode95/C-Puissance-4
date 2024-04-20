#pragma once

#include "joueur.hpp"

template <typename P>
class JMCTS : public Joueur<P> {
private:
    double a;
    unsigned temps;
    noeud<P>* racine;

public:
    JMCTS(double a, unsigned temps);
    unsigned JeuHasard(P p) const;
    unsigned Jouer(P p) override;
};
