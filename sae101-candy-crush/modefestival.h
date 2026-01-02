#ifndef MODEFESTIVAL_H
#define MODEFESTIVAL_H
#include <iostream>
#include "fichierfonction1.h"
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

#endif // MODEFESTIVAL_H
