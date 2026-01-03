#include "../headers/bombe.h"
#include "../headers/affichage.h"
#include <iostream>
using namespace std;
using namespace manipulationDeVecteur;
using namespace manipulationDeLaGrille;
using namespace testSurLaGrille;

// rajoute bombe (nombre 5) dans un endroit rnadom dans la grille
void festival::rajouteBombe(CMatrice & grille){
    int numPremier = rand()%(grille.size());
    int numDeuxieme = rand()%(grille.size());
    grille[numPremier][numDeuxieme] = 5;
}

int festival::detectionBombe(CMatrice & grille, CPosition & pos, unsigned & combien, bool uneLigne){
    // si couleurCible == 0, il n'y a pas de bombe
    // si couleurCible != 0, on veut eliminer toutes cases avec couleurCible
    int couleurCible = 0;
    int x;
    int y;

    // parcourt toutes cases qui vont être supprimées
    for (unsigned i = 0; i < combien; ++i){
        if (uneLigne){
            y = pos.second;
            x = pos.first + i;
        }
        else{
            y = pos.second + i;
            x = pos.first;
        }

        vector<int> coordVertical = {-1, 1, 0, 0};
        vector<int> coordHorizontal = {0, 0, -1, 1};

        // on verifie chaque coord adjacent (haut, bas, gauche, droite)
        for (int coord = 0; coord < 4; ++coord){
            int yAdjacent = y + coordVertical[coord];
            int xAdjacent = x + coordHorizontal[coord];
            // on verifie si la case adjacent n'est pas au bord
            if (yAdjacent >= 0 && yAdjacent < grille.size() && xAdjacent >= 0 && xAdjacent < grille.size()){
                // verification si case adjacent est une bombe (numero 5)
                if (grille[yAdjacent][xAdjacent] == 5){
                    // couleurCible devient couleur de la ligne qui allait être supprimé
                    couleurCible = grille[y][x];
                    // supprime la bombe
                    grille[yAdjacent][xAdjacent] = KImpossible;
                }
            }
        }
    }
    return couleurCible;
}


// enleve toute couleurCible dans la grille avec KImpossible
void festival::supprimeCouleurBombe(CMatrice & grille, int & couleurCible){
    for (size_t i = 0; i < grille.size(); ++i){
        for (size_t j = 0; j < grille.size(); ++j) {
            if (grille[i][j] == couleurCible){
                grille[i][j] = KImpossible;
            }
        }
    }
}

// Fait remonter les cases vides (comme si les symboles étaient soumis à la gravité)
void festival::gravite (CMatrice & grille) {
    unsigned saut (0);
    for(unsigned i (0); i <= grille.size() - 1; ++i) {
        for(unsigned j (grille.size() - 1); j > saut; --j) {
            while(grille[j][i] == KImpossible) {
                swap(grille[j][i], grille[j - (1 + saut)][i]);
                if(grille[j][i] == KImpossible)
                    ++saut;
                if(saut + 1 > j)
                    break;
            }
        }
        saut = 0;
    }
}
