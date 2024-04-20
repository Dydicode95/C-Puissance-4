#pragma once

#include <string>
#include "class_P4.hpp"

template <typename P>
class Joueur {
public:
    std::string nom;
    virtual unsigned Jouer(P p) = 0;
    virtual void FinPartie() { }
    std::string message;
};

class JHP4 : public Joueur<P4> {
public:
    JHP4();
    unsigned Jouer(P4 p) override;
};

class IARandom : public Joueur<P4> {
public:
    IARandom();
    unsigned Jouer(P4 p) override;
};