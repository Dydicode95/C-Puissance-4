#pragma once

#include "class_P4.hpp"

template <typename P>
struct noeud {
    noeud<P>* pere;
    noeud<P>** fils;
    unsigned nbfils;
    P p;
    unsigned cross, win;
    unsigned indiceMeilleurFils;

    static unsigned compt;

    explicit noeud(noeud<P>* pere, P p);
    ~noeud();

    std::string ToString() const;
    void CalculMeilleurFils(double a);
    noeud<P>* MeilleurFils();
};