#include "../headers/mode-festival.h"
#include "../headers/affichage.h"
#include "../headers/bombe.h"
#include <iostream>
#include <cstdlib>

using namespace std;
using namespace manipulationDeVecteur;
using namespace manipulationDeLaGrille;
using namespace testSurLaGrille;
using namespace festival;


bool mouvementValideFestival(const CMatrice& grille, int x, int y, char direction) {
    bool cond = true;
    if (x < 0 || x >= grille.size() || y < 0 || y >= grille.size()) {
        cond = false;
    }

    switch (tolower(direction)) {
    case 'z':
        if (y <= 0)
            cond = false;
        break;
    case 's':
        if (y >= grille.size() - 1)
            cond = false;
        break;
    case 'a': // Left
        if (x <= 0)
            cond = false;
        break;
    case 'e': // Right
        if (x >= grille.size() - 1)
            cond = false;
        break;
    default:
        cout << "Erreur: touche invalide." << endl;
        cond = false;
    }
    return cond;
}



int modeFestival(){
    CMatrice grille;
    size_t taille = 10;
    unsigned combien;
    CPosition pos;
    char direction;

    InitiationGrille(grille, taille);

    while(true){
        afficherLaGrille(grille);

        while(auMoinsTroisDansLaLigne(grille, pos, combien))
        {
            int couleur = detectionBombe(grille, pos, combien, true);
            supprimmerUneLigne (grille, pos, combien);
            if (couleur != 0){
                supprimeCouleurBombe(grille, couleur);
            }
            gravite(grille);
            afficherLaGrille(grille);
            cout << "------" << endl;
        }

        while(auMoinsTroisDansLaColonne(grille, pos, combien))
        {
            int couleur = detectionBombe(grille, pos, combien, false);
            supprimmerUneColonne (grille, pos, combien);
            if (couleur != 0){
                supprimeCouleurBombe(grille, couleur);
            }
            gravite(grille);
            afficherLaGrille(grille);
            cout << "------" << endl;
        }
    }
    bool valide = false;
    while (!valide) {
        cout << "Donne abscisse (X) : ";
        cin >> pos.first;
        cout << "Donne ordonnee (Y) : ";
        cin >> pos.second;
        cout << "Donne direction (Z, S, A, E) : ";
        cin >> direction;

        if (mouvementValideFestival(grille, pos.first, pos.second, direction)) {
            valide = true;
        } else {
            cout << "Coup impossible" << endl;
        }
    }

    faireUnMouvement(grille, pos, direction);
}
