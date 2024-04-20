#include "class_P4.hpp"

#include <ctime>
#include <cstdlib>
#include <random>

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
}T

