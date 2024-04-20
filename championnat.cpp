#include "championnat.hpp"

void Championnat(std::vector<Joueur<P4>*>& v, unsigned nbTours) {
    unsigned nbJoueurs = v.size();

    // Initialisation du bilan des duels
    std::vector<std::pair<unsigned, unsigned>> bilan(nbJoueurs, {0, 0}); // {nbVictoires, nbDefaites}

    // Boucle pour chaque tour
    for (unsigned tour = 0; tour < nbTours; ++tour) {
        std::cout << "Tour " << tour + 1 << " du championnat :" << std::endl;

        // Boucle pour chaque joueur
        for (unsigned i = 0; i < nbJoueurs; ++i) {
            for (unsigned j = 0; j < nbJoueurs; ++j) {
                if (i != j) { // Ne pas jouer contre soi-même
                    Joueur<P4>* joueur1 = v[i];
                    Joueur<P4>* joueur2 = v[j];

                    P4 etatInitial; // Création de l'état initial du jeu
                    Partie<P4> partie1(*joueur1, *joueur2, etatInitial); // Premier match : joueur1 commence
                    Partie<P4> partie2(*joueur2, *joueur1, etatInitial); // Deuxième match : joueur2 commence

                    // Déroulement du premier match
                    partie1.Commencer();
                    // Enregistrement du résultat
                    if (partie1.r == Resultat::j1gagne)
                        bilan[i].first++, bilan[j].second++; // joueur1 a gagné
                    else if (partie1.r == Resultat::j0gagne)
                        bilan[j].first++, bilan[i].second++; // joueur2 a gagné, joueur1 a perdu

                    // Déroulement du deuxième match
                    partie2.Commencer();
                    // Enregistrement du résultat
                    if (partie2.r == Resultat::j1gagne)
                        bilan[j].first++, bilan[i].second++; // joueur2 a gagné
                    else if (partie2.r == Resultat::j0gagne)
                        bilan[i].first++, bilan[j].second++; // joueur1 a gagné, joueur2 a perdu
                }
            }
        }

        std::cout << "Fin du tour " << tour + 1 << " du championnat." << std::endl;
    }

    // Affichage du bilan des duels
    std::cout << "\nBilan des duels :\n";
    for (unsigned i = 0; i < nbJoueurs; ++i) {
        std::cout << "Joueur " << v[i]->nom << " - Victoires: " << bilan[i].first << " - Défaites: " << bilan[i].second << std::endl;
    }
}
