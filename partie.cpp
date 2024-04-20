#include "partie.hpp"

template <typename P>
Partie<P>::Partie(Joueur<P>& j1, Joueur<P>& j0, P pInitiale, bool aff) : j1(j1), j0(j0), pCourante(pInitiale), affichage(aff) {}

template <typename P>
void Partie<P>::Commencer() {
    if (affichage)
        std::cout << pCourante.ToString() << std::endl;
    
    while (pCourante.ColonnesNonPleines().size() > 0) {
        if (pCourante.j1aletrait) {
            if (affichage)
                std::cout << j1.nom << "(j1) joue" << std::endl;
            int pos = j1.Jouer(pCourante);
            pCourante.EffectuerCoup(pos);
            if (pCourante.EstGagnant()) { // Appel à la fonction EstGagnant
                r = Resultat::j1gagne;
                break;
            }
            if (affichage)
                std::cout << j1.message << std::endl;
        } else {
            if (affichage)
                std::cout << j0.nom << "(j0) joue" << std::endl;
            pCourante.EffectuerCoup(j0.Jouer(pCourante));
            if (pCourante.EstGagnant()) { // Appel à la fonction EstGagnant
                r = Resultat::j0gagne;
                break;
            }
            if (affichage)
                std::cout << j0.message << std::endl;
        }
        if (affichage)
            std::cout << pCourante.ToString() << std::endl;
    }
    
    // Affichage de l'état final du plateau de jeu et du résultat final
    std::cout << "État final du plateau de jeu :\n" << pCourante.ToString() << std::endl;
    switch (r) {
        case Resultat::j1gagne:
            std::cout << "Le joueur " << j1.nom << " (j1) a gagné !" << std::endl;
            break;
        case Resultat::j0gagne:
            std::cout << "Le joueur " << j0.nom << " (j0) a gagné !" << std::endl;
            break;
        case Resultat::partieNulle:
            std::cout << "Partie nulle !" << std::endl;
            break;
    }
    
    // Appel des méthodes de fin de partie pour chaque joueur
    j1.FinPartie(); 
    j0.FinPartie();
}