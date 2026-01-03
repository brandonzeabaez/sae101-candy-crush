#include "../headers/grille.h"
#include "../headers/mode-1vs1.h"

/*
 * MODE 1VS1
 * commandes :
 *      Joueur 1 : ‘A’ (gauche), ‘Z’ (haut), ‘E’ (droite), ‘S’ (bas)
 *      Joueur 2 : ‘I’ (gauche), ‘O’ (haut), ‘P’ (droite), ‘L’ (bas)
*/

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

// Gestion des déplacements en fonction du joueur
bool mode1vs1::faireUnMouvement (CMat & grille, const CPosition & pos, const char direction, const unsigned KJoueur) {
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

// Fait remonter les cases vides (comme si les symboles étaient soumis à la gravité)
void mode1vs1::gravite (CMat & grille) {
    unsigned saut (0);
    for(unsigned i (0); i <= KTailleGrille - 1; ++i) {
        for(unsigned j (KTailleGrille - 1); j > saut; --j) {
            while(grille[j][i] == 0) {
                std::swap(grille[j][i], grille[j - (1 + saut)][i]);
                if(grille[j][i] == 0)
                    ++saut;
                if(saut + 1 > j)
                    break;
            }
        }
        saut = 0;
    }
}

// Supprime les nombres identiques successifs de la grille (horizontalement et vertialement)
void mode1vs1::suppressionDansLaGrille (CMat & grille, const CMat & matrice) {
    for(unsigned i (0); i <= KTailleGrille - 1; ++i)
        for(unsigned j (0); j <= KTailleGrille - 1; ++j)
            if(matrice[i][j] == 1)
                grille[i][j] = 0;
}

// Calcule le nombre de points gagnés pendant ce tour de jeu par le joueur en cours
unsigned mode1vs1::compteScore (CMat & matrice) {
    unsigned score (0);
    for(CVLine & ligne : matrice)
        for(unsigned & element : ligne)
            if(element == 1)
                ++score;
    return score;
}

int mode1vs1::lancer () {
    unsigned joueur (0); // Stocke le joueur en cours
    unsigned coups (0); // Stocke le nombre de coups joués
    std::pair <unsigned, unsigned> score (std::pair(0, 0)); // Stock le score de chaque joueur
    CPosition pos; // Tuple des coordonnées du symbole à déplacer
    char coordonnée; // Variable temporaire qui stocke le choix utilisateur des coordonnées
    CMat grille; // Grille qui contiendra les symboles
    CMat matrice; // Matrice qui contiendra les emplacements des symboles à supprimer

    // préparation du terminal & de la grille
    affichage::changerCouleur(KReset);
    affichage::effacerEcran();
    grille::initGrille(grille);
    matrice.resize(KTailleGrille, CVLine (KTailleGrille));
    grille::initMat(matrice);

    // Affichage des règles
    std::cout << "Pour jouer vous donnerez :\n"
            "     - L'abscisse de l'élément à déplacer\n"
            "     - L'ordonnée de l'élément à déplacer\n"
            "     - La direction dans laquel vous voulez le déplacer\n" << std::endl;
    std::cout << "Les touches valides de déplacement sont :\n"
            "    - Joueur 1 : ‘A’ (gauche), ‘Z’ (haut), ‘E’ (droite), ‘S’ (bas)\n"
            "    - Joueur 2 : ‘I’ (gauche), ‘O’ (haut), ‘P’ (droite), ‘L’ (bas)\n" << std::endl;

    // début de la partie
    while(KCoupsMax * 2 - coups > 0) {
        affichage::afficherGrille(grille); // Affichage de la grille
        std::cout << "\n" << "Manche : " << coups / 2 + 1 << std::endl; // Affichage de la manche en cours
        std::cout << "Joueur : " << joueur + 1 << "\n" << std::endl; // Affichage du joueur en cours

        // récupération des coordonnées & la direction
        std::cout << "Abscisse : " << std::flush;
        std::cin >> coordonnée;
        pos.second = std::stoi(&coordonnée);
        std::cout << "Ordonnée : " << std::flush;
        std::cin >> coordonnée;
        pos.first = std::stoi(&coordonnée);
        std::cout << "direction : " << std::flush;
        std::cin >> coordonnée;

        if (grille[pos.first][pos.second] != 0) {
            if ((joueur == 0 && (coordonnée == 'Z' || coordonnée == 'S' || coordonnée == 'A' || coordonnée == 'E')) || (joueur == 1 && (coordonnée == 'O' || coordonnée == 'L' || coordonnée == 'I' || coordonnée == 'P'))) {
                if (mode1vs1::faireUnMouvement(grille, pos, coordonnée, joueur)) {
                    while(grille::auMoinsTroisParLigne(grille, matrice) | grille::auMoinsTroisParColonne(grille, matrice)) {
                        joueur == 0 ? score.first += mode1vs1::compteScore(matrice) : score.second += mode1vs1::compteScore(matrice); // met à jour le score en fonction du joueur en cours
                        mode1vs1::suppressionDansLaGrille(grille, matrice);

                        std::cout << "\n" << std::endl;
                        affichage::afficherGrille(grille);
                        std::cout << "\n" << std::endl;

                        mode1vs1::gravite(grille);
                        grille::initMat(matrice);
                    }
                }
                else {
                    std::cout << "\nVous ne pouvez pas aller dans cette direction !\n" << std::endl;
                    continue;
                }
            }
            else {
                std::cout << "\nveuillez entrer une direction valide !\n" << std::endl;
                continue;
            }
        }
        else {
            std::cout << "\nVous ne pouvez pas sélectionner une zone vide !\n" << std::endl;
            continue;
        }

        joueur = (joueur + 1) % 2; // changement du joueur
        ++coups; // incrémentation du nombre de coups joués par les deux joueurs
    }
    // affichage du score final
    std::cout << "Score final :\n" << "  - 1: " << score.first << "\n" << "  - 2: " << score.second << std::endl;
    return 0;
}
