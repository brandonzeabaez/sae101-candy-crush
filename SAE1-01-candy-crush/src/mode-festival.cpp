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

// verification de mouvement valide pour mode festival
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
    case 'a':
        if (x <= 0)
            cond = false;
        break;
    case 'e':
        if (x >= grille.size() - 1)
            cond = false;
        break;
    default:
        cout << "Erreur: touche invalide." << endl;
        cond = false;
    }
    return cond;
}

// calcule de score pour mode festival
int calculeScore(const CMatrice & grille){
    int score = 0;
    for (size_t i = 0; i < grille.size(); ++i){
        for (size_t j = 0; j < grille.size(); ++i){
            if (grille[i][j] != KImpossible){
                score = score + 5;
            }
        }
    }
    return score;
}


// jeu principale
int modeFestival(){
    // initialisation des variables
    CMatrice grille;
    size_t taille = 10;
    unsigned combien;
    CPosition pos;
    char direction;
    int coups = 11;
    int score = 0;

    InitiationGrille(grille, taille);

    // boucle principale du jeu
    while(coups != 0){
        afficherLaGrille(grille);
        cout << "Il reste " << coups << "coups" << endl;

        // verifier si mouvement est valide
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
            }
            else {
                cout << "Coup impossible" << endl;
            }
        }
        faireUnMouvement(grille, pos, direction);

        // enleve les lignes et colonnes avec detection de bombe
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


    score = calculeScore(grille);
    cout << "Score: " << score << endl;
    return 0;
}
