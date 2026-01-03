#ifndef GRILLE_H
#define GRILLE_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>

typedef std::vector <unsigned> CVLine; // un type représentant une ligne de la grille
typedef std::vector <CVLine> CMat; // un type représentant la grille
typedef std::pair <unsigned, unsigned> CPosition; // une position dans la girlle

namespace affichage{
void changerCouleur (const unsigned & couleur);
void effacerEcran ();
void afficherGrille (const CMat & grille);
}

namespace grille{
void initGrille (CMat & grille);
void initMat (CMat & matrice);
bool faireUnMouvement (CMat & grille, const CPosition & pos, const char direction, const unsigned KJoueur);
void modifieLigneMatrice (const unsigned i, const unsigned j, const unsigned combienDeSuite, CMat & matrice);
void modifieColonneMatrice (const unsigned i, const unsigned j, const unsigned combienDeSuite, CMat & matrice);
bool auMoinsTroisParLigne (const CMat & grille, CMat & matrice);
bool auMoinsTroisParColonne (const CMat & grille, CMat & matrice);
void suppressionDansLaGrille (CMat & grille, const CMat & matrice);
}

#endif // GRILLE_H
