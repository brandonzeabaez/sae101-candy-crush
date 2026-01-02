#ifndef BOMBE_H
#define BOMBE_H
#include <iostream>
#include "bombe.h"
using namespace std;
using namespace manipulationDeVecteur;
using namespace manipulationDeLaGrille;
using namespace testSurLaGrille;

namespace festival{
    void rajouteBombe(CMatrice & grille);
    int detectionBombe(CMatrice & grille, CPosition & pos, unsigned combien, bool uneLigne);
    void supprimeCouleurBombe(CMatrice & grille, int & couleurCible);
    void gravite (CMatrice & grille);
}
#endif // BOMBE_H
