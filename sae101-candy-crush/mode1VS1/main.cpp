#include <iostream>
#include <vector>

using namespace std;

typedef vector <unsigned> CVLine; // un type représentant une ligne de la grille
typedef vector <CVLine> CMat; // un type représentant la grille
typedef pair <unsigned, unsigned> CPosition; // une position dans la girlle

const unsigned KReset   (0);
const unsigned KNoir    (30);
const unsigned KRouge   (31);
const unsigned KVert    (32);
const unsigned KJaune   (33);
const unsigned KBleu    (34);
const unsigned KMAgenta (35);
const unsigned KCyan    (36);

const unsigned KCoupsMax = 20;
const unsigned KNbSymboles = 5;
const unsigned KImpossible = 0;

// une fontion qui change la coleur du terminal
void changerCouleur (const unsigned & couleur) {
    cout << "\033[" << couleur <<"m";
}

// une fontion qui efface le terminal
void effacerEcran () {
    cout << "\033[H\033[2J";
}

// initialise toutes les cases de la grille avec des nombres tirés au hasard entre 1 et une constante
void initGrille (CMat & grille, unsigned taille) {
    grille.resize(taille, CVLine (taille));
    for (unsigned i (0); i < taille; ++i){
        for (unsigned j (0); j < taille; ++j){
            do{
                grille[i][j] = rand() % (KNbSymboles + 1) + 1;
            }while(i >= 2 && j >= 2 && ((grille[i][j] == grille[i-1][j] && grille[i][j] == grille[i-2][j]) || (grille[i][j] == grille[i][j-1] && grille[i][j] == grille[i][j-2])));
        }
    }
}

/*
void initGrille (CMat & grille, unsigned taille) {
    grille.resize(taille, CVLine (taille));
    for (CVLine & ligne : grille)
        for (unsigned & elm : ligne)
            elm = rand() % (KNbSymboles + 1) + 1;
}
*/

// colorie les cases du tableau
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

// Gestion des déplacements
void faireUnMouvement (CMat & grille, const CPosition & pos, char direction, const unsigned KJoueur) {
    if (KJoueur == 0) {
        switch (direction) {
        case 'Z':
            swap(grille[pos.first][pos.second], grille[pos.first - 1][pos.second]);
            break;
        case 'S':
            swap(grille[pos.first][pos.second], grille[pos.first + 1][pos.second]);
            break;
        case 'A':
            swap(grille[pos.first][pos.second], grille[pos.first][pos.second - 1]);
            break;
        case 'E':
            swap(grille[pos.first][pos.second], grille[pos.first][pos.second + 1]);
            break;
        default:
            break;
        }
    }else {
        switch (direction) {
        case 'O':
            swap(grille[pos.first][pos.second], grille[pos.first - 1][pos.second]);
            break;
        case 'L':
            swap(grille[pos.first][pos.second], grille[pos.first + 1][pos.second]);
            break;
        case 'I':
            swap(grille[pos.first][pos.second], grille[pos.first][pos.second - 1]);
            break;
        case 'P':
            swap(grille[pos.first][pos.second], grille[pos.first][pos.second + 1]);
            break;
        default:
            break;
        }
    }
}

// Detection d’une suite de nombres identiques sur la même colonne
bool auMoinsTroisParColonne (const CMat & grille, CPosition & pos, unsigned & howMany) {
    // size_t i = pos.second;
    size_t i = 1;
    howMany = 1;
    bool result = false;
    while(i < size(grille)) {
        if (grille[i][pos.second] != grille[i - 1][pos.second]) {
            if (howMany >= 3) {
                result = true;
                break;
            }
            howMany = 1;
        }
        else {
            if (i == size(grille) - 1 && howMany >= 3) result = true;
            howMany += 1;
        }
        ++i;
    }
    return result;
}

// Detection d’une suite de nombres identiques sur la même ligne
bool auMoinsTroisParLigne (const CMat & grille, CPosition & pos, unsigned & howMany) {
    // size_t i = pos.first;
    size_t i = 1;
    howMany = 1;
    bool result = false;
    while(i < size(grille)) {
        if (grille[pos.first][i] != grille[pos.first][i - 1]) {
            if (howMany >= 3) {
                result = true;
                break;
            }
            howMany = 1;
        }
        else {
            if (i == size(grille) - 1 && howMany >= 3) result = true;
            howMany += 1;
        }
        ++i;
    }
    return result;
}

// Cette fonction supprime les nombres identiques successifs de la colonne
void suppressionDansLaColonne (CMat & grille, const CPosition & pos, unsigned howMany) {
    unsigned i = 0;
    while(i < howMany || pos.first + i + howMany < size(grille)) {
        grille[pos.first + i][pos.second] = grille[pos.first + i + howMany][pos.second];
        i += 1;
    }
    while(pos.first + i < size(grille)) {
        grille[pos.first + i][pos.second] = KImpossible;
        i += 1;
    }
}

// Cette fonction supprime les nombres identiques successifs de la ligne
void suppressionDansLaLigne (CMat & grille, const CPosition & pos, unsigned howMany) {
    CPosition newPos = pos;
    for (unsigned i = 0; i < howMany; ++i) {
        newPos.second += 1;
        suppressionDansLaColonne (grille, newPos, 1);
    }
}

int main () {
    unsigned joueur = 0;
    unsigned coups = 0;
    unsigned score = 0;
    CPosition pos;
    char coordonnée;
    unsigned nombrePoints;
    CPosition flag;
    changerCouleur(KReset);
    effacerEcran();
    CMat tableau;
    initGrille(tableau, 10);
    while(KCoupsMax - coups > 0) {
        afficherGrille(tableau);
        cout << "Pour jouer vous donnerez :" << endl;
        cout << "     - L'abscisse de l'élément à déplacer" << endl;
        cout << "     - L'ordonnée de l'élément à déplacer" << endl;
        cout << "     - La direction dans laquel vous voulez le déplacer" << endl;
        cout << "Les touches valides de déplacement sont : ‘A’ (gauche),‘Z’ (haut), ‘E’ (droit), ‘S’ (bas)" << endl << endl;
        cout << "Abscisse :" << endl;
        cin >> coordonnée;
        pos.first = stoi(&coordonnée);
        cout << "Ordonnée :" << endl;
        cin >> coordonnée;
        pos.second = stoi(&coordonnée);
        cout << "direction :" << endl;
        cin >> coordonnée;
        faireUnMouvement(tableau, pos, coordonnée, joueur);
        flag = pair(1, 1);
        if ((joueur == 1 && (coordonnée == 'A' || coordonnée == 'E')) || (joueur == 2 && (coordonnée == 'I' || coordonnée == 'P'))) {
            while (flag.first != 0 && flag.second != 0) {
                if(auMoinsTroisParColonne(tableau, pos, nombrePoints)) {
                    score += nombrePoints;
                    suppressionDansLaColonne(tableau, pos, nombrePoints);
                    flag.first = 1;
                }
                else
                    flag.first = 0;
                if(auMoinsTroisParLigne(tableau, pos, nombrePoints)) {
                    score += nombrePoints;
                    suppressionDansLaLigne(tableau, pos, nombrePoints);
                    flag.second = 1;
                }
                else
                    flag.second = 0;
            }
        }
        else if ((joueur == 1 && (coordonnée == 'Z' || coordonnée == 'S')) || (joueur == 2 && (coordonnée == 'O' || coordonnée == 'L'))) {
            while (flag.first != 0 && flag.second != 0) {
                afficherGrille(tableau);
                cout << "  " << endl;
                if(auMoinsTroisParLigne(tableau, pos, nombrePoints)) {
                    cout << "1" << endl;
                    cout << nombrePoints << endl;
                    score += nombrePoints;
                    suppressionDansLaLigne(tableau, pos, nombrePoints);
                    flag.first = 1;
                }
                else
                    flag.first = 0;
                if(auMoinsTroisParColonne(tableau, pos, nombrePoints)) {
                    cout << "2" << endl;
                    cout << nombrePoints << endl;
                    score += nombrePoints;
                    suppressionDansLaColonne(tableau, pos, nombrePoints);
                    flag.second = 1;
                }
                else
                    flag.second = 0;
            }
        }
        else {
            cout << "veuillez rentrer une direction valide !" << endl;
            continue;
        }
        joueur = (joueur + 1) % 2;
        ++coups;
    }
    cout << "Score final : " << score;
    return 0;
}
