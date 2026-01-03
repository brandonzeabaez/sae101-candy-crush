#ifndef BOMBE_H
#define BOMBE_H
#include "affichage.h"


namespace festival{
    void rajouteBombe(manipulationDeLaGrille::CMatrice & grille);
    int detectionBombe(manipulationDeLaGrille::CMatrice & grille, manipulationDeLaGrille::CPosition & pos, unsigned & combien, bool uneLigne);
    void supprimeCouleurBombe(manipulationDeLaGrille::CMatrice & grille, int & couleurCible);
    void gravite (manipulationDeLaGrille::CMatrice & grille);
}
#endif // BOMBE_H
