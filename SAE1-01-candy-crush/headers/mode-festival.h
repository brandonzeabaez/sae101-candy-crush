#ifndef MODE_FESTIVAL_H
#define MODE_FESTIVAL_H
#include "affichage.h"

namespace festival{
    bool mouvementValide(const manipulationDeLaGrille::CMatrice& grille, int x, int y, char direction);
    int modeFestival ();
}
#endif // MODE_FESTIVAL_H
