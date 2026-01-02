/*
 * MODE 1VS1
 * commandes :
 *      Joueur 1 : ‘A’ (gauche), ‘Z’ (haut), ‘E’ (droite), ‘S’ (bas)
 *      Joueur 2 : ‘I’ (gauche), ‘O’ (haut), ‘P’ (droite), ‘L’ (bas)
*/

#include "../headers/mode-1vs1.h"
#include <iostream>
#include <vector>

using namespace std;

typedef vector <unsigned> CVLine; // un type représentant une ligne de la grille
typedef vector <CVLine> CMat; // un type représentant la grille
typedef pair <unsigned, unsigned> CPosition; // une position dans la girlle

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
    cout << "\033[" << couleur <<"m";
}

// efface/réinitialise le terminal
void effacerEcran () {
    cout << "\033[H\033[2J";
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
            cout << " | ";
            switch (elm) {
            case 1:
                changerCouleur(KRouge);
                break;
            case 2:
                changerCouleur(KVert);
                break;
            case 3:
                changerCouleur(KJaune);
                break;
            case 4:
                changerCouleur(KBleu);
                break;
            case 5:
                changerCouleur(KMAgenta);
                break;
            case 6:
                changerCouleur(KCyan);
                break;
            default:
                changerCouleur(KReset);
                break;
            }
            cout << elm;
            changerCouleur(KReset);
        }
        cout << " |" << endl;
    }
}

// Gestion des déplacements en fonction du joueur
bool faireUnMouvement (CMat & grille, const CPosition & pos, const char direction, const unsigned KJoueur) {
    bool changement = true;
    if (KJoueur == 0) {
        switch (direction) {
        case 'Z':
            if (grille[(pos.first > 0 ? pos.first - 1 : KTailleGrille - 1)][pos.second] != 0)
                swap(grille[pos.first][pos.second], grille[(pos.first > 0 ? pos.first - 1 : KTailleGrille - 1)][pos.second]);
            else
                changement = false;
            break;
        case 'S':
            if (grille[(pos.first + 1) % KTailleGrille][pos.second] != 0)
                swap(grille[pos.first][pos.second], grille[(pos.first + 1) % KTailleGrille][pos.second]);
            else
                changement = false;
            break;
        case 'A':
            if (grille[pos.first][(pos.second > 0 ? pos.second - 1 : KTailleGrille - 1)] != 0)
                swap(grille[pos.first][pos.second], grille[pos.first][(pos.second > 0 ? pos.second - 1 : KTailleGrille - 1)]);
            else
                changement = false;
            break;
        case 'E':
            if (grille[pos.first][(pos.second + 1) % KTailleGrille] != 0)
                swap(grille[pos.first][pos.second], grille[pos.first][(pos.second + 1) % KTailleGrille]);
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
                swap(grille[pos.first][pos.second], grille[(pos.first > 0 ? pos.first - 1 : KTailleGrille - 1)][pos.second]);
            else
                changement = false;
            break;
        case 'L':
            if (grille[(pos.first + 1) % KTailleGrille][pos.second] != 0)
                swap(grille[pos.first][pos.second], grille[(pos.first + 1) % KTailleGrille][pos.second]);
            else
                changement = false;
            break;
        case 'I':
            if (grille[pos.first][(pos.second > 0 ? pos.second - 1 : KTailleGrille - 1)] != 0)
                swap(grille[pos.first][pos.second], grille[pos.first][(pos.second > 0 ? pos.second - 1 : KTailleGrille - 1)]);
            else
                changement = false;
            break;
        case 'P':
            if (grille[pos.first][(pos.second + 1) % KTailleGrille] != 0)
                swap(grille[pos.first][pos.second], grille[pos.first][(pos.second + 1) % KTailleGrille]);
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
        cout << k << endl;
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
                modifieLigneMatrice(i - 1, j, combienDeSuite, matrice);
                drapeau = true;
            }
            combienDeSuite = 1;
        }
        else if(grille[j][i] != 0){
            combienDeSuite += 1;
            if (i == KTailleGrille - 1 && combienDeSuite >= 3) {
                modifieLigneMatrice(i, j, combienDeSuite, matrice);
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
                modifieColonneMatrice(i, j + 1, combienDeSuite, matrice);
                drapeau = true;
            }
            combienDeSuite = 1;
        }
        else if(grille[j][i] != 0){
            combienDeSuite += 1;
            if (j == 0 && combienDeSuite >= 3) {
                modifieColonneMatrice(i, j, combienDeSuite, matrice);
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

// Calcule le nombre de points gagnés pendant ce tour de jeu par le joueur en cours
unsigned compteScore (CMat & matrice) {
    unsigned score (0);
    for(CVLine & ligne : matrice)
        for(unsigned & element : ligne)
            if(element == 1)
                ++score;
    return score;
}

// Supprime les nombres identiques successifs de la grille (horizontalement et vertialement)
void suppressionDansLaGrille (CMat & grille, const CMat & matrice) {
    for(unsigned i (0); i <= KTailleGrille - 1; ++i)
        for(unsigned j (0); j <= KTailleGrille - 1; ++j)
            if(matrice[i][j] == 1)
                grille[i][j] = 0;
}

// Fait remonter les cases vides (comme si les symboles étaient soumis à la gravité)
void gravite (CMat & grille) {
    unsigned saut (0);
    for(unsigned i (0); i <= KTailleGrille - 1; ++i) {
        for(unsigned j (KTailleGrille - 1); j > saut; --j) {
            while(grille[j][i] == 0) {
                swap(grille[j][i], grille[j - (1 + saut)][i]);
                if(grille[j][i] == 0)
                    ++saut;
                if(saut + 1 > j)
                    break;
            }
        }
        saut = 0;
    }
}

int mode1vs1 () {
    unsigned joueur (0); // Stocke le joueur en cours
    unsigned coups (0); // Stocke le nombre de coups joués
    pair <unsigned, unsigned> score (pair(0, 0)); // Stock le score de chaque joueur
    CPosition pos; // Tuple des coordonnées du symbole à déplacer
    char coordonnée; // Variable temporaire qui stocke le choix utilisateur des coordonnées
    CMat grille; // Grille qui contiendra les symboles
    CMat matrice; // Matrice qui contiendra les emplacements des symboles à supprimer

    // préparation du terminal & de la grille
    changerCouleur(KReset);
    effacerEcran();
    initGrille(grille);
    matrice.resize(KTailleGrille, CVLine (KTailleGrille));
    initMat(matrice);

    // Affichage des règles
    cout << "Pour jouer vous donnerez :\n"
            "     - L'abscisse de l'élément à déplacer\n"
            "     - L'ordonnée de l'élément à déplacer\n"
            "     - La direction dans laquel vous voulez le déplacer\n" << endl;
    cout << "Les touches valides de déplacement sont :\n"
            "    - Joueur 1 : ‘A’ (gauche), ‘Z’ (haut), ‘E’ (droite), ‘S’ (bas)\n"
            "    - Joueur 2 : ‘I’ (gauche), ‘O’ (haut), ‘P’ (droite), ‘L’ (bas)\n" << endl;

    // début de la partie
    while(KCoupsMax * 2 - coups > 0) {
        afficherGrille(grille); // Affichage de la grille
        cout << "\n" << "Manche : " << coups / 2 + 1 << endl; // Affichage de la manche en cours
        cout << "Joueur : " << joueur + 1 << "\n" << endl; // Affichage du joueur en cours

        // récupération des coordonnées & la direction
        cout << "Abscisse : " << flush;
        cin >> coordonnée;
        pos.second = stoi(&coordonnée);
        cout << "Ordonnée : " << flush;
        cin >> coordonnée;
        pos.first = stoi(&coordonnée);
        cout << "direction : " << flush;
        cin >> coordonnée;

        if (grille[pos.first][pos.second] != 0) {
            if ((joueur == 0 && (coordonnée == 'Z' || coordonnée == 'S' || coordonnée == 'A' || coordonnée == 'E')) || (joueur == 1 && (coordonnée == 'O' || coordonnée == 'L' || coordonnée == 'I' || coordonnée == 'P'))) {
                if (faireUnMouvement(grille, pos, coordonnée, joueur)) {
                    while(auMoinsTroisParLigne(grille, matrice) | auMoinsTroisParColonne(grille, matrice)) {
                        joueur == 0 ? score.first += compteScore(matrice) : score.second += compteScore(matrice); // met à jour le score en fonction du joueur en cours
                        suppressionDansLaGrille(grille, matrice);

                        cout << "\n" << endl;
                        afficherGrille(grille);
                        cout << "\n" << endl;

                        gravite(grille);
                        initMat(matrice);
                    }
                }
                else {
                    cout << "\nVous ne pouvez pas aller dans cette direction !\n" << endl;
                    continue;
                }
            }
            else {
                cout << "\nveuillez entrer une direction valide !\n" << endl;
                continue;
            }
        }
        else {
            cout << "\nVous ne pouvez pas sélectionner une zone vide !\n" << endl;
            continue;
        }

        joueur = (joueur + 1) % 2; // changement du joueur
        ++coups; // incrémentation du nombre de coups joués par les deux joueurs
    }
    // affichage du score final
    cout << "Score final :\n" << "  - 1: " << score.first << "\n" << "  - 2: " << score.second;
    return 0;
}
