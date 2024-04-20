#include "joueur.hpp"
#include "partie.hpp"
#include "championnat.hpp"
#include "noeud.hpp"
#include "JMCTS.hpp"

int main() {
    // Création des joueurs JMCTS
    JMCTS<P4> joueur1(1.0, 1);  // Configuration arbitraire pour le premier joueur : c'est le joueur 1 ou j1
    JMCTS<P4> joueur2(2.0, 1);

    // Création de l'état initial du jeu
    P4 etatInitial;

    // Création de la partie entre JMCTS et JHP4
    Partie<P4> partie(joueur1, joueur2, etatInitial);

    // Début de la partie
    partie.Commencer();

    return 0;
}
