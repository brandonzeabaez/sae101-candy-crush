#ifndef MODE_FESTIVAL_H
#define MODE_FESTIVAL_H

#include <vector>

typedef std::vector <unsigned> CVLine; // un type représentant une ligne de la grille
typedef std::vector <CVLine> CMat; // un type représentant la grille
typedef std::pair <unsigned, unsigned> CPosition; // une position dans la girlle

namespace modeFestival{
    bool mouvementValideFestival(const CMat & grille, int x, int y, char direction);
    int calculeScore(const CMat & grille);
    int lancer ();
}

#endif // MODE_FESTIVAL_H
