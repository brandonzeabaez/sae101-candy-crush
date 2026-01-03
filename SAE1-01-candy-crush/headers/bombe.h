#ifndef BOMBE_H
#define BOMBE_H
#include <iostream>
#include "bombe.h"
// Pas de namespaces dans les fichiers.h askip
// using namespace std;
using namespace manipulationDeVecteur;
using namespace manipulationDeLaGrille;
using namespace testSurLaGrille;

typedef std::vector <CVLine> CMat; // un type représentant la grille
typedef std::pair <unsigned, unsigned> CPosition; // une position dans la girlle

namespace festival{
    void rajouteBombe(CMat & grille);
    int detectionBombe(CMat & grille, CPosition & pos, unsigned combien, bool uneLigne); // je sais pas si c'est voulu de pas avoir mis de & mais ok ?
    void supprimeCouleurBombe(CMat & grille, int & couleurCible);
    void gravite (CMat & grille);
}
#endif // BOMBE_H
