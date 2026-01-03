#include "../headers/grille.h"

// constantes de couleurs d'affichage du terminal
const unsigned KReset   (0);
const unsigned KNoir    (30);
const unsigned KRouge   (31);
const unsigned KVert    (32);
const unsigned KJaune   (33);
const unsigned KBleu    (34);
const unsigned KMAgenta (35);
const unsigned KCyan    (36);

const unsigned KTailleGrille (10); // Longueur & largeur de la grille de jeu
const unsigned KCoupsMax     (20); // Nombre de coups possibles dans la partie
const unsigned KNbSymboles   (5); // Nombre de symboles représentés dans la grille
const unsigned KImpossible   (0); // symbole nul

// change la couleur du terminal
void changerCouleur (const unsigned & couleur) {
    std::cout << "\033[" << couleur <<"m";
}

// efface/réinitialise le terminal
void effacerEcran () {
    std::cout << "\033[H\033[2J";
}

// initialise toutes les cases de la grille avec des nombres tirés au hasard entre 1 et une constante
// l'algorithme empêche les triplets ou plus
void initGrille (CMat & grille) {
    grille.resize(KTailleGrille, CVLine (KTailleGrille));
    for (unsigned i (0); i < KTailleGrille; ++i) {
        for (unsigned j (0); j < KTailleGrille; ++j) {
            do{
                grille[i][j] = rand() % KNbSymboles + 1;
            }while(i >= 2 && j >= 2 && ((grille[i][j] == grille[i-1][j] && grille[i][j] == grille[i-2][j]) || (grille[i][j] == grille[i][j-1] && grille[i][j] == grille[i][j-2])));
        }
    }
}

// (re)initialise toutes les cases de la matrice à 0
void initMat (CMat & matrice) {
    for (CVLine & ligne : matrice)
        for (unsigned & element : ligne)
            element = 0;
}

// colorie les cases du grille
void afficherGrille (const CMat & grille) {
    for (const CVLine & ligne : grille) {
        for (const unsigned & elm : ligne) {
            std::cout << " | ";
            switch (elm) {
            case 1:
                affichage::changerCouleur(KRouge);
                break;
            case 2:
                affichage::changerCouleur(KVert);
                break;
            case 3:
                affichage::changerCouleur(KJaune);
                break;
            case 4:
                affichage::changerCouleur(KBleu);
                break;
            case 5:
                affichage::changerCouleur(KMAgenta);
                break;
            case 6:
                affichage::changerCouleur(KCyan);
                break;
            default:
                affichage::changerCouleur(KReset);
                break;
            }
            std::cout << elm;
            affichage::changerCouleur(KReset);
        }
        std::cout << " |" << std::endl;
    }
}

// Gestion des déplacements en fonction du joueur
bool faireUnMouvement (CMat & grille, const CPosition & pos, const char direction, const unsigned KJoueur) {
    bool changement = true;
    if (KJoueur == 0) {
        switch (direction) {
        case 'Z':
            if (grille[(pos.first > 0 ? pos.first - 1 : KTailleGrille - 1)][pos.second] != 0)
                std::swap(grille[pos.first][pos.second], grille[(pos.first > 0 ? pos.first - 1 : KTailleGrille - 1)][pos.second]);
            else
                changement = false;
            break;
        case 'S':
            if (grille[(pos.first + 1) % KTailleGrille][pos.second] != 0)
                std::swap(grille[pos.first][pos.second], grille[(pos.first + 1) % KTailleGrille][pos.second]);
            else
                changement = false;
            break;
        case 'A':
            if (grille[pos.first][(pos.second > 0 ? pos.second - 1 : KTailleGrille - 1)] != 0)
                std::swap(grille[pos.first][pos.second], grille[pos.first][(pos.second > 0 ? pos.second - 1 : KTailleGrille - 1)]);
            else
                changement = false;
            break;
        case 'E':
            if (grille[pos.first][(pos.second + 1) % KTailleGrille] != 0)
                std::swap(grille[pos.first][pos.second], grille[pos.first][(pos.second + 1) % KTailleGrille]);
            else
                changement = false;
            break;
        default:
            break;
        }
    }else {
        switch (direction) {
        case 'O':
            if (grille[(pos.first > 0 ? pos.first - 1 : KTailleGrille - 1)][pos.second] != 0)
                std::swap(grille[pos.first][pos.second], grille[(pos.first > 0 ? pos.first - 1 : KTailleGrille - 1)][pos.second]);
            else
                changement = false;
            break;
        case 'L':
            if (grille[(pos.first + 1) % KTailleGrille][pos.second] != 0)
                std::swap(grille[pos.first][pos.second], grille[(pos.first + 1) % KTailleGrille][pos.second]);
            else
                changement = false;
            break;
        case 'I':
            if (grille[pos.first][(pos.second > 0 ? pos.second - 1 : KTailleGrille - 1)] != 0)
                std::swap(grille[pos.first][pos.second], grille[pos.first][(pos.second > 0 ? pos.second - 1 : KTailleGrille - 1)]);
            else
                changement = false;
            break;
        case 'P':
            if (grille[pos.first][(pos.second + 1) % KTailleGrille] != 0)
                std::swap(grille[pos.first][pos.second], grille[pos.first][(pos.second + 1) % KTailleGrille]);
            else
                changement = false;
            break;
        default:
            break;
        }
    }
    return changement;
}

// Modifie la matrice en fonction des suites de nombres identiques sur les mêmes lignes
void modifieLigneMatrice (const unsigned i, const unsigned j, const unsigned combienDeSuite, CMat & matrice) {
    unsigned antiDepacement (0);
    if(i < combienDeSuite) {
        antiDepacement = 1;
        matrice[j][0] = 1;
    }
    for(unsigned k (i - combienDeSuite + antiDepacement); k++ < i; )
        matrice[j][k] = 1;
}

// Modifie la matrice en fonction des suites de nombres identiques sur les mêmes colonnes
void modifieColonneMatrice (const unsigned i, const unsigned j, const unsigned combienDeSuite, CMat & matrice) {
    for(unsigned k (j + combienDeSuite); k-- > j; ) {
        std::cout << k << std::endl;
        if(matrice[k][i] != 1)
            matrice[k][i] = 1;
    }}

// Detection d’une suite de nombres identiques sur la même ligne
bool auMoinsTroisParLigne (const CMat & grille, CMat & matrice) {
    bool drapeau (false);
    size_t i (1);
    size_t j (KTailleGrille - 1);
    unsigned combienDeSuite (1);
    while(i <= KTailleGrille - 1) {
        if (grille[j][i] != grille[j][i - 1]) {
            if (combienDeSuite >= 3) {
                grille::modifieLigneMatrice(i - 1, j, combienDeSuite, matrice);
                drapeau = true;
            }
            combienDeSuite = 1;
        }
        else if(grille[j][i] != 0){
            combienDeSuite += 1;
            if (i == KTailleGrille - 1 && combienDeSuite >= 3) {
                grille::modifieLigneMatrice(i, j, combienDeSuite, matrice);
                drapeau = true;
            }
        }
        if((i == KTailleGrille - 1) && (j > 0)) {
            i = 0;
            --j;
            combienDeSuite = 1;
        }
        ++i;
    }
    return drapeau;
}

// Detection d’une suite de nombres identiques sur la même colonne
bool auMoinsTroisParColonne (const CMat & grille, CMat & matrice) {
    bool drapeau (false);
    size_t i (0);
    size_t j (KTailleGrille - 2);
    unsigned combienDeSuite (1);
    while(i <= KTailleGrille - 1) {
        if (grille[j][i] != grille[j + 1][i]) {
            if (combienDeSuite >= 3) {
                grille::modifieColonneMatrice(i, j + 1, combienDeSuite, matrice);
                drapeau = true;
            }
            combienDeSuite = 1;
        }
        else if(grille[j][i] != 0){
            combienDeSuite += 1;
            if (j == 0 && combienDeSuite >= 3) {
                grille::modifieColonneMatrice(i, j, combienDeSuite, matrice);
                drapeau = true;
            }
        }
        if((j == 0) && (i <= KTailleGrille - 1)) {
            j = KTailleGrille - 1;
            ++i;
            combienDeSuite = 1;
        }
        --j;
    }
    return drapeau;
}

// Supprime les nombres identiques successifs de la grille (horizontalement et vertialement)
void suppressionDansLaGrille (CMat & grille, const CMat & matrice) {
    for(unsigned i (0); i <= KTailleGrille - 1; ++i)
        for(unsigned j (0); j <= KTailleGrille - 1; ++j)
            if(matrice[i][j] == 1)
                grille[i][j] = 0;
}
