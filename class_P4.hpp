#pragma once

#include <vector>
#include <string>
#include <iostream>

enum class Resultat { j1gagne, j0gagne, partieNulle };

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
