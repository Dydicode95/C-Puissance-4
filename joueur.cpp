#include "joueur.hpp"

#include <iostream>

// Définition des méthodes de la classe JHP4
JHP4::JHP4() {
    nom = "Joueur Humain (Puissance 4)";
}

unsigned JHP4::Jouer(P4 p) {
    unsigned col;
    std::cout << "Entrez le numéro de la colonne où vous voulez jouer (de 1 à 7) : ";
    std::cin >> col;
    // Convertir de 1-indexed à 0-indexed
    return col - 1;
}

IARandom::IARandom() {
    nom = "IA Aléatoire";
    // Initialisation du générateur de nombres aléatoires
    std::srand(std::time(nullptr));
}

unsigned IARandom::Jouer(P4 p) {
    // Obtenir le nombre de colonnes possibles
    unsigned nbCols = p.ColonnesNonPleines().size();
    // Choisir aléatoirement une colonne entre 0 et nbCols - 1
    unsigned col = std::rand() % nbCols;
    return col;
}
