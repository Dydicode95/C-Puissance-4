#pragma once
#ifndef PUISSANCE4_HPP
#define PUISSANCE4_HPP

#include <string>
#include <random>
#include <iostream>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <random>

enum class Resultat { j1gagne, j0gagne, partieNulle };

template <typename P>
class Joueur {
public:
    std::string nom;
    virtual unsigned Jouer(P p) = 0;
    virtual void FinPartie() { }
    std::string message;
};

class P4 {
private:
    std::vector<std::vector<char>> board;

public:
    bool GrillePleine() const;
    static const int ROWS = 6;
    static const int COLS = 7;
    bool EstGagnant() const;     
    bool j1aletrait;
    P4();
    std::string ToString() const;
    void EffectuerCoup(unsigned col);
    Resultat Eval() const;
    std::vector<unsigned> ColonnesNonPleines();
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
template <typename P>
void Championnat(std::vector<Joueur<P>*>& v, unsigned nbTours);

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


#endif
