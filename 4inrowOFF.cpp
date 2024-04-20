#include "4inrow.hpp"

std::random_device rd;
std::default_random_engine e(rd());

// Définition des méthodes de la classe P4
bool P4::GrillePleine() const {  // le const dans la déclaration de GrillePleine() garantit que cette fonction ne modifie pas l'état de l'objet P4 sur lequel elle est appelée, et qu'elle peut être appelée sur des objets const P4.
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

std::vector<unsigned> P4::ColonnesNonPleines() {
    std::vector<unsigned> colonnesNonPleines;
    for (unsigned col = 0; col < COLS; ++col) {
        if (board[0][col] == ' ') {
            colonnesNonPleines.push_back(col);
        }
    }
    return colonnesNonPleines;
}

bool P4::EstGagnant() const {
    // Vérification horizontale
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS - 3; ++col) {
            if (board[row][col] != ' ' &&
                board[row][col] == board[row][col + 1] &&
                board[row][col] == board[row][col + 2] &&
                board[row][col] == board[row][col + 3]) {
                return true;
            }
        }
    }

    // Vérification verticale
    for (int col = 0; col < COLS; ++col) {
        for (int row = 0; row < ROWS - 3; ++row) {
            if (board[row][col] != ' ' &&
                board[row][col] == board[row + 1][col] &&
                board[row][col] == board[row + 2][col] &&
                board[row][col] == board[row + 3][col]) {
                return true;
            }
        }
    }

    // Vérification diagonale (descendante)
    for (int row = 0; row < ROWS - 3; ++row) {
        for (int col = 0; col < COLS - 3; ++col) {
            if (board[row][col] != ' ' &&
                board[row][col] == board[row + 1][col + 1] &&
                board[row][col] == board[row + 2][col + 2] &&
                board[row][col] == board[row + 3][col + 3]) {
                return true;
            }
        }
    }

    // Vérification diagonale (montante)
    for (int row = 3; row < ROWS; ++row) {
        for (int col = 0; col < COLS - 3; ++col) {
            if (board[row][col] != ' ' &&
                board[row][col] == board[row - 1][col + 1] &&
                board[row][col] == board[row - 2][col + 2] &&
                board[row][col] == board[row - 3][col + 3]) {
                return true;
            }
        }
    }

    return false; // Aucun gagnant détecté
}


P4::P4() {
    board.assign(ROWS, std::vector<char>(COLS, ' '));
} // Ce code définit le constructeur par défaut de la classe `P4`, qui initialise la grille de jeu représentée par la variable `board`. Il utilise la fonction `assign()` pour créer une grille vide de taille `ROWS` lignes par `COLS` colonnes, où chaque case est initialisée avec un espace `' '`. Ainsi, lorsque vous créez une nouvelle instance de la classe `P4`, sa grille de jeu est automatiquement configurée pour commencer une nouvelle partie.

std::string P4::ToString() const {
    std::string result;
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            result += board[i][j];
            result += ' ';
        }
        result += '\n';
    }
    return result;
}

void P4::EffectuerCoup(unsigned col) {
    // Parcours des lignes du bas vers le haut
    for (int i = ROWS - 1; i >= 0; --i) {
        // Vérifie si la case est vide
        if (board[i][col] == ' ') {
            // Détermine le jeton du joueur en fonction de j1aletrait
            char joueur = (j1aletrait) ? 'X' : 'O';
            // Place le jeton sur le plateau
            board[i][col] = joueur;
            // Change le joueur actif
            j1aletrait = !j1aletrait;
            // Sort de la fonction après avoir placé le jeton
            return;
        }
    }
}


Resultat P4::Eval() const {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (board[i][j] != ' ') {
                char joueur = board[i][j];
                // Vérification horizontale
                if (j + 3 < COLS && board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2] && board[i][j] == board[i][j + 3]) {
                    return (joueur == 'X') ? Resultat::j1gagne : Resultat::j0gagne;
                }
                // Vérification verticale
                if (i + 3 < ROWS && board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j] && board[i][j] == board[i + 3][j]) {
                    return (joueur == 'X') ? Resultat::j1gagne : Resultat::j0gagne;
                }
                // Vérification diagonale (descendante)
                if (i + 3 < ROWS && j + 3 < COLS && board[i][j] == board[i + 1][j + 1] && board[i][j] == board[i + 2][j + 2] && board[i][j] == board[i + 3][j + 3]) {
                    return (joueur == 'X') ? Resultat::j1gagne : Resultat::j0gagne;
                }
                // Vérification diagonale (montante)
                if (i - 3 >= 0 && j + 3 < COLS && board[i][j] == board[i - 1][j + 1] && board[i][j] == board[i - 2][j + 2] && board[i][j] == board[i - 3][j + 3]) {
                    return (joueur == 'X') ? Resultat::j1gagne : Resultat::j0gagne;
                }
            }
        }
    }
    return Resultat::partieNulle;
}

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

template <typename P>
JMCTS<P>::JMCTS(double a, unsigned temps) : a(a), temps(temps) {
    this->nom = "JMCTS(a=" + std::to_string(a) + ",temps=" + std::to_string(temps) + ")";
}

template <typename P>
unsigned JMCTS<P>::JeuHasard(P p) const {
    unsigned re = 1;
    while (p.ColonnesNonPleines().size() > 0) {
        std::vector<unsigned> colonnesNonPleines = p.ColonnesNonPleines();
        unsigned a = colonnesNonPleines[e() % colonnesNonPleines.size()];
        p.EffectuerCoup(a);   
    } // Le pb de mon code c'est que il se termine à cette ligne !
    if (p.Eval() == Resultat::j1gagne) { re = 2; }
    if (p.Eval() == Resultat::j0gagne) { re = 0; }
    return re;
}

template <typename P>
unsigned JMCTS<P>::Jouer(P p) {
    std::clock_t t0 = std::clock();
    std::clock_t t1 = t0 + temps * (CLOCKS_PER_SEC / 1000); // En résumé, ce code utilise std::clock() pour enregistrer le temps actuel dans t0, puis calcule le moment où un temps spécifié en millisecondes sera écoulé depuis t0, et stocke ce moment dans t1.
    racine = new noeud<P>(nullptr, p); // racine = new noeud<P4>(nullptr, pCourante); : Cette ligne crée un nouvel objet de type noeud<P4> (nœud), alloue de la mémoire pour cet objet en utilisant l'opérateur new, et l'initialise en appelant le constructeur noeud<P4>(nullptr, pCourante).
    unsigned iter = 0;
    while (std::clock() < t1) {
        noeud<P>* no = racine; // no est un pointeur sur une instance de la classe noeud

        do // Sélection
        {
            no->CalculMeilleurFils(a); // appel de la méthode CalculMeilleurFils() qui ne renvoie rien mais 
            no = no->MeilleurFils(); // 

        } while (no->cross > 0 && no->nbfils > 0);

        unsigned re = JeuHasard(no->p); // Simulation
        while (no != nullptr) // Rétropropagation
        {
            no->cross += 2;
            no->win += re;
            no = no->pere;
        }
        ++iter;
    }
    // il faut qu'avant de calculer le meilleur fils, lui obliger de choisir parmi les colonnes non pleines ! donc il faut afficher le plateau de jeu de racine
    P4 plateauCopie = racine->p;
    std::cout << plateauCopie.ToString() << std::endl;
    std::cout<<"Voici l'état actuel du plateau"<<std::endl;
    racine->CalculMeilleurFils(a);
    this->message = std::to_string(iter) + " itérations\n";
    this->message += racine->ToString();
    //unsigned res = racine->indiceMeilleurFils;
    unsigned res = p.ColonnesNonPleines()[racine->indiceMeilleurFils];
    delete racine;
    return res;
}

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
