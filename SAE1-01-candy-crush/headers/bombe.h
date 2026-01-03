#ifndef BOMBE_H
#define BOMBE_H

#include "affichage.h"

namespace festival
{
    using CMat = manipulationDeLaGrille::CMatrice; // un type représentant la grille
    using CPosition = manipulationDeLaGrille::CPosition; // une position dans la girlle

    void rajouteBombe(CMat & grille);
    unsigned detectionBombe(CMat & grille, const CPosition & pos, unsigned combien, bool uneLigne); // je sais pas si c'est voulu de pas avoir mis de & mais ok ?
    void supprimeCouleurBombe(CMat & grille, unsigned & couleurCible);
    void gravite (CMat & grille);
}
#endif // BOMBE_H
