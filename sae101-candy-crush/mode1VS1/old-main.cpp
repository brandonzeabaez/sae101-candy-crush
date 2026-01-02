/*
 * MODE 1VS1
 * commandes :
 *      Joueur 1 : ‘A’ (gauche), ‘Z’ (haut), ‘E’ (droite), ‘S’ (bas)
 *      Joueur 2 : ‘I’ (gauche), ‘O’ (haut), ‘P’ (droite), ‘L’ (bas)
*/

/*


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

const unsigned KTailleGrille = 10; // Longueur & largeur de la grille de jeu
const unsigned KCoupsMax = 20; // Nombre de coups possibles dans la partie
const unsigned KNbSymboles = 5; // Nombre de symboles représentés dans la grille
const unsigned KImpossible = 0; // symbole nul

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
void initGrille (CMat & grille, unsigned taille) {
    grille.resize(taille, CVLine (taille));
    for (unsigned i (0); i < taille; ++i){
        for (unsigned j (0); j < taille; ++j){
            do{
                grille[i][j] = rand() % KNbSymboles + 1;
            }while(i >= 2 && j >= 2 && ((grille[i][j] == grille[i-1][j] && grille[i][j] == grille[i-2][j]) || (grille[i][j] == grille[i][j-1] && grille[i][j] == grille[i][j-2])));
        }
    }
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
void faireUnMouvement (CMat & grille, const CPosition & pos, char direction, const unsigned KJoueur) {
    if (KJoueur == 0) {
        switch (direction) {
        case 'Z':
            swap(grille[pos.first][pos.second], grille[(pos.first > 0 ? pos.first - 1 : KTailleGrille - 1)][pos.second]);
            break;
        case 'S':
            swap(grille[pos.first][pos.second], grille[(pos.first + 1) % KTailleGrille][pos.second]);
            break;
        case 'A':
            swap(grille[pos.first][pos.second], grille[pos.first][(pos.second > 0 ? pos.second - 1 : KTailleGrille - 1)]);
            break;
        case 'E':
            swap(grille[pos.first][pos.second], grille[pos.first][(pos.second + 1) % KTailleGrille]);
            break;
        default:
            break;
        }
    }else {
        switch (direction) {
        case 'O':
            swap(grille[pos.first][pos.second], grille[(pos.first > 0 ? pos.first - 1 : KTailleGrille - 1)][pos.second]);
            break;
        case 'L':
            swap(grille[pos.first][pos.second], grille[(pos.first + 1) % KTailleGrille][pos.second]);
            break;
        case 'I':
            swap(grille[pos.first][pos.second], grille[pos.first][(pos.second > 0 ? pos.second - 1 : KTailleGrille - 1)]);
            break;
        case 'P':
            swap(grille[pos.first][pos.second], grille[pos.first][(pos.second + 1) % KTailleGrille]);
            break;
        default:
            break;
        }
    }
}

// Detection d’une suite de nombres identiques sur la même colonne
bool auMoinsTroisParColonne (const CMat & grille, CPosition & pos, unsigned & combienDeSuite) {
    size_t i = 1;
    combienDeSuite = 1;
    bool result = false;
    while(i < size(grille)) {
        if (grille[i][pos.second] != grille[i - 1][pos.second]) {
            if (combienDeSuite >= 3) {
                result = true;
                break;
            }
            combienDeSuite = 1;
        }
        else {
            if (i == size(grille) - 1 && combienDeSuite >= 3) result = true;
            combienDeSuite += 1;
        }
        ++i;
    }
    return result;
}

// Detection d’une suite de nombres identiques sur la même ligne
bool auMoinsTroisParLigne (const CMat & grille, CPosition & pos, unsigned & combienDeSuite) {
    // size_t i = pos.first;
    size_t i = 1;
    combienDeSuite = 1;
    bool result = false;
    while(i < size(grille)) {
        if (grille[pos.first][i] != grille[pos.first][i - 1]) {
            if (combienDeSuite >= 3) {
                result = true;
                break;
            }
            combienDeSuite = 1;
        }
        else {
            if (i == size(grille) - 1 && combienDeSuite >= 3) result = true;
            combienDeSuite += 1;
        }
        ++i;
    }
    return result;
}

// Cette fonction supprime les nombres identiques successifs de la colonne
void suppressionDansLaColonne (CMat & grille, const CPosition & pos, unsigned combienDeSuite) {
    unsigned i = 0;
    while(i < combienDeSuite || pos.first + i + combienDeSuite < size(grille)) {
        grille[pos.first + i][pos.second] = grille[pos.first + i + combienDeSuite][pos.second];
        i += 1;
    }
    while(pos.first + i < size(grille)) {
        grille[pos.first + i][pos.second] = KImpossible;
        i += 1;
    }
}

// Cette fonction supprime les nombres identiques successifs de la ligne
void suppressionDansLaLigne (CMat & grille, const CPosition & pos, unsigned combienDeSuite) {
    CPosition newPos = pos;
    for (unsigned i = 0; i < combienDeSuite; ++i) {
        newPos.second += 1;
        suppressionDansLaColonne (grille, newPos, 1);
    }
}

int main () {
    unsigned joueur = 0; // Stocke le joueur en cours
    unsigned coups = 0; // Stocke le nombre de coups joués
    pair <unsigned, unsigned> score = pair(0, 0); // Stock le score de chaque joueur
    CPosition pos; // Tuple des coordonnées du symbole à déplacer
    char coordonnée; // Variable temporaire qui stocke le choix utilisateur des coordonnées
    unsigned nombrePoints; // Stocke le nombre de points réalisé à cette manche
    pair <unsigned, unsigned> flag; // Drapeau qui permet de vérifier que la grille est bien valide (pas de triplet ou plus) après modification ou non
    CMat grille; // Grille qui contiendra les symboles

    // préparation du terminal & de la grille
    changerCouleur(KReset);
    effacerEcran();
    initGrille(grille, KTailleGrille);

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

        faireUnMouvement(grille, pos, coordonnée, joueur);
        flag = pair(1, 1);
        if ((joueur == 0 && (coordonnée == 'A' || coordonnée == 'E')) || (joueur == 1 && (coordonnée == 'I' || coordonnée == 'P'))) {
            while (flag.first != 0 && flag.second != 0) {
                if(auMoinsTroisParColonne(grille, pos, nombrePoints)) {
                    joueur == 0 ? score.first += nombrePoints : score.second += nombrePoints;
                    suppressionDansLaColonne(grille, pos, nombrePoints);
                    flag.first = 1;
                }
                else
                    flag.first = 0;
                if(auMoinsTroisParLigne(grille, pos, nombrePoints)) {
                    joueur == 0 ? score.first += nombrePoints : score.second += nombrePoints;
                    suppressionDansLaLigne(grille, pos, nombrePoints);
                    flag.second = 1;
                }
                else
                    flag.second = 0;
            }
        }
        else if ((joueur == 0 && (coordonnée == 'Z' || coordonnée == 'S')) || (joueur == 1 && (coordonnée == 'O' || coordonnée == 'L'))) {
            while (flag.first != 0 && flag.second != 0) {
                if(auMoinsTroisParLigne(grille, pos, nombrePoints)) {
                    joueur == 0 ? score.first += nombrePoints : score.second += nombrePoints;
                    suppressionDansLaLigne(grille, pos, nombrePoints);
                    flag.first = 1;
                }
                else
                    flag.first = 0;
                if(auMoinsTroisParColonne(grille, pos, nombrePoints)) {
                    joueur == 0 ? score.first += nombrePoints : score.second += nombrePoints;
                    suppressionDansLaColonne(grille, pos, nombrePoints);
                    flag.second = 1;
                }
                else
                    flag.second = 0;
            }
        }
        else {
            cout << "\nveuillez rentrer une direction valide !\n" << endl;
            continue;
        }
        joueur = (joueur + 1) % 2;
        ++coups;
    }
    // affichage du score final
    cout << "Score final :\n" << "  - 1: " << score.first << "\n" << "  - 2: " << score.second;
    return 0;
}

*/
