#ifndef BOMBE_H
#define BOMBE_H

#include "utilitaires.h"

namespace festival
{
    using CMat = manipulationDeLaGrille::CMatrice; // un type représentant la grille
    using CPosition = manipulationDeLaGrille::CPosition; // une position dans la grille

    void rajouteBombe(CMat & grille);
    unsigned detectionBombe(CMat & grille, const CPosition & pos, unsigned combien, bool uneLigne);
    void supprimeCouleurBombe(CMat & grille, unsigned & couleurCible);
    void gravite (CMat & grille);
}
#endif // BOMBE_H
