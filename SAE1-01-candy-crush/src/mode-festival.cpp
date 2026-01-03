#include "../headers/mode-festival.h"
#include "../headers/utilitaires.h"
#include "../headers/bombe.h"

const unsigned KImpossible (999);

// verification de mouvement valide pour mode festival
bool modeFestival::mouvementValideFestival(const CMat& grille, int x, int y, char direction) {
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
        std::cout << "Erreur: touche invalide." << std::endl;
        cond = false;
    }
    return cond;
}

// calcule de score pour mode festival
int modeFestival::calculeScore(const CMat & grille){
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
int modeFestival::lancer(){
    // initialisation des variables
    CMat grille;
    size_t taille = 10;
    unsigned combien;
    CPosition pos;
    char direction;
    int coups = 11;
    int score = 0;

    manipulationDeLaGrille::InitiationGrille(grille, taille);

    // boucle principale du jeu
    while(coups != 0){
        manipulationDeLaGrille::afficherLaGrille(grille);
        std::cout << "Il reste " << coups << "coups" << std::endl;

        // verifier si mouvement est valide
        bool valide = false;
        while (!valide) {
            std::cout << "Donne abscisse (X) : ";
            std::cin >> pos.first;
            std::cout << "Donne ordonnee (Y) : ";
            std::cin >> pos.second;
            std::cout << "Donne direction (Z, S, A, E) : ";
            std::cin >> direction;

            if (mouvementValideFestival(grille, pos.first, pos.second, direction)) {
                valide = true;
            }
            else {
                std::cout << "Coup impossible" << std::endl;
            }
        }
        manipulationDeLaGrille::faireUnMouvement(grille, pos, direction);

        // enleve les lignes et colonnes avec detection de bombe
        while(testSurLaGrille::auMoinsTroisDansLaLigne(grille, pos, combien))
        {
            unsigned couleur = festival::detectionBombe(grille, pos, combien, true);
            manipulationDeLaGrille::supprimmerUneLigne (grille, pos, combien);
            if (couleur != 0){
                festival::supprimeCouleurBombe(grille, couleur);
            }
            festival::gravite(grille);
            manipulationDeLaGrille::afficherLaGrille(grille);
            std::cout << "------" << std::endl;
        }

        while(testSurLaGrille::auMoinsTroisDansLaColonne(grille, pos, combien))
        {
            unsigned couleur = festival::detectionBombe(grille, pos, combien, false);
            manipulationDeLaGrille::supprimmerUneColonne (grille, pos, combien);
            if (couleur != 0){
                festival::supprimeCouleurBombe(grille, couleur);
            }
            festival::gravite(grille);
            manipulationDeLaGrille::afficherLaGrille(grille);
            std::cout << "------" << std::endl;
        }
    }


    score = calculeScore(grille);
    std::cout << "Score: " << score << std::endl;
    return 0;
}
