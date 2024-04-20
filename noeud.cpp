#include "noeud.hpp"

template<typename P>
unsigned noeud<P>::compt = 0;

template <typename P>
noeud<P>::noeud(noeud<P>* pere, P p) : pere(pere), p(p), cross{0}, win{0} {
    ++compt;
    nbfils = p.ColonnesNonPleines().size();
    fils = new noeud<P>*[nbfils];
    for (unsigned i = 0; i < nbfils; ++i) fils[i] = nullptr;
}

template <typename P>
noeud<P>::~noeud() {
    for (unsigned i = 0; i < nbfils; ++i) { delete fils[i]; }
    delete[] fils;
    --compt;
}

template <typename P>
noeud<P>* noeud<P>::MeilleurFils() {
    if (fils[indiceMeilleurFils] != nullptr) {
        return fils[indiceMeilleurFils];
    }
    P q = p;
    q.EffectuerCoup(indiceMeilleurFils);
    fils[indiceMeilleurFils] = new noeud<P>(this, q); // apparemment this correspondrait à racine !
    return fils[indiceMeilleurFils]; // ainsi no devient noeud<P4> (racine, q_1) sachant que q_1 est pCourante après q'un coup ai été effectué !
}

template <typename P>
void noeud<P>::CalculMeilleurFils(double a) {
    double s;
    double sM = 0;
    if (p.j1aletrait) {
        for ( unsigned i=0;i<nbfils; i++){
            if (fils[i] == nullptr) {
                s = 1;
            }
            else {
                s = (fils[i]->win + a) / (fils[i]->cross + a); // l'erreur de segmentation vient ici !
            }
            if (s > sM ) {
                sM = s; 
                indiceMeilleurFils = i;

            }

        }
    }
    else {
        for (unsigned i=0;i<nbfils;i++) {
            if (fils[i]== nullptr) { s = 1; }
            else { s = (fils[i]->cross - fils[i]->win + a) / (fils[i]->cross + a); }
            if (s > sM) { sM = s; indiceMeilleurFils = i; }
        }
    }
}


template <typename P>
std::string noeud<P>::ToString() const {
    std::string s = "";
    s = s + "indice MF = " + std::to_string(indiceMeilleurFils);
    double note;
    s += "\n note=";
    if (fils[indiceMeilleurFils]) {
        note = (1.0 * fils[indiceMeilleurFils]->win) / fils[indiceMeilleurFils]->cross;
        s += std::to_string(note);
    }
    else s += "?";
    s += "\n nbC=" + std::to_string(cross / 2);
    s += "\n" + std::to_string(compt);
    return s;
}