#include "../headers/grille.h"
#include "../headers/mode-infini.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

/*
    Mode Infini
    Commandes : ‘A’ (gauche), ‘Z’ (haut), ‘E’ (droite), ‘S’ (bas)
    Règles: Cette fois, quand des bonbons disparaissent, ils sont
    tout de suite remplacés ! Tenez compte des règles spéciales si
    vous voulez continuer à jouer !
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

// Calcule le score (nb de blocs éliminés * combo)
unsigned compteScore (CMat & matrice, unsigned & combo) {
    unsigned score (0);
    for(CVLine & ligne : matrice)
        for(unsigned & element : ligne)
            if(element == 1)
                score = score * combo;
    return score;
}

// Fait remonter les cases vides (comme si les symboles étaient soumis à la gravité)
void gravite (CMat & grille, std::string & sens) {
    unsigned saut (0);
    if (sens == "BAS") { // C'est à dire les bonbons descendent
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
        affichage::afficherGrille(grille);
        // On en profite pour remplacer ce trou par un bonbon comme on l'a dit
        remplacerZero(grille);
        return;
    }

    if (sens == "HAUT") { // C'est à dire les bonbons montent
        for (unsigned h=0; h<5; ++h) { // On aura 5 bonbons alignés verticalement au maximum alors on s'assure qu'ils bougent avec cette boucle
            for (unsigned i=0; i< KTailleGrille - 1; ++i) {
                for (unsigned j=0; j< KTailleGrille - 1; ++j) {
                    if (grille[i][j] == 0) {
                        std::swap(grille[i][j], grille[i+1][j]);
                    }
                }
            }
        }
        affichage::afficherGrille(grille);
        // On en profite pour remplacer ce trou par un bonbon comme on l'a dit
        remplacerZero(grille);
        return;
    }

    if (sens == "DROITE") { // C'est à dire les bonbons vont vers la droite
        for (unsigned h=0; h<5; ++h) { // On aura 5 bonbons alignés horizontalement au maximum alors on s'assure qu'ils bougent avec cette boucle
            for (unsigned i=0; i< KTailleGrille - 1; ++i) {
                for (unsigned j=1; j<= KTailleGrille - 1; ++j) {
                    if (grille[i][j] == 0) {
                        std::swap(grille[i][j], grille[i][j-1]);
                    }
                }
            }
        }
        affichage::afficherGrille(grille);
        // On en profite pour remplacer ce trou par un bonbon comme on l'a dit
        remplacerZero(grille);
        return;
    }

    if (sens == "GAUCHE") { // C'est à dire les bonbons vont vers la gauche
        for (unsigned h=0; h<5; ++h) { // On aura 5 bonbons alignés horizontalement au maximum alors on s'assure qu'ils bougent avec cette boucle
            for (unsigned i=0; i< KTailleGrille - 1; ++i) {
                for (unsigned j=1; j<= KTailleGrille - 1; ++j) {
                    if (grille[i][j] == 0) {
                        std::swap(grille[i][j], grille[i][j+1]);
                    }
                }
            }
        }
        affichage::afficherGrille(grille);
        // On en profite pour remplacer ce trou par un bonbon comme on l'a dit
        remplacerZero(grille);
        return;
    }
}

std::vector <CPosition> obtenirPositionsSept (CMat & grille) {
    std::vector <CPosition> positionsSept;
    for (unsigned i=0; i < KTailleGrille; ++i) {
        for (unsigned j=0; j < KTailleGrille; ++j) {
            if (grille[i][j] == 7) {
                CPosition temp;
                temp.first = i;
                temp.second = j;
                positionsSept.push_back(temp);
            }
        }
    }
    return positionsSept;
}

void transformer(const unsigned & a, const unsigned & b, CMat & grille) {
    for (unsigned i = 0; i < KTailleGrille; ++i) {
        for (unsigned j = 0; j < KTailleGrille; ++j) {
            if (grille[i][j] == a) {
                grille[i][j] = b;
            }
        }
    }
}

// Réalisation d'un objectif, dès qu'il est réalisé un nouveau apparait s'il n'est pas réalisé dans le nombre de tours imparti alors finito
bool regleRespectee(Regle & regle, CMat & grille, std::string & sensGravite, std::vector <CPosition> & posSept, unsigned & tribut, CPosition & pos, unsigned & somme, unsigned & combo, bool & tourNonJoue) {
    if (tourNonJoue) {
        return true;
    }
    if (regle.id == "7ST") {
        if (regle.duree == 7) { // si la règle vient d'être mise en place
            tribut = 1 + (rand() % KNbSymboles);
            transformer(tribut, 7, grille);
            posSept = obtenirPositionsSept(grille);
        }
        std::cout << std::string(80, '-') << std::endl;
        std::cout << regle.description << std::endl << "Dure encore " << regle.duree << " tour(s)." << std::endl;
        std::cout << std::string(80, '-') << std::endl << std::endl;

        return (posSept == obtenirPositionsSept(grille) && pos.first != 7 && pos.second != 7);
    }
    else if (regle.id == "SING") {
        if (regle.duree == 9) { // si la règle vient d'être mise en place
            std::vector <std::string> sensGraviteListe = {"HAUT", "GAUCHE", "DROITE"}; // on exclus le bas pour être sûr de changer la gravité
            sensGravite = sensGraviteListe[rand() % 3]; // sens de la gravité déterminé au hasard
        }

        std::cout << std::string(80, '-') << std::endl;
        std::cout << regle.description << std::endl << "Dure encore " << regle.duree << " tour(s)." << std::endl;
        std::cout << std::string(80, '-') << std::endl << std::endl;

        std::cout << "Tiens, on dirait que la singularité est apparue, elle attire les bonbons vers cette partie de l'espace: " << sensGravite << std::endl;

        return true;
    }
    else if (regle.id == "RNCN") {
        if (regle.duree == 0 && somme < 25) return false;
        std::cout << std::string(80, '-') << std::endl;
        std::cout << regle.description << std::endl << "Dure encore " << regle.duree << " tour(s)." << std::endl;
        std::cout << std::string(80, '-') << std::endl << std::endl;

        std::cout << "Votre butin s'élève à " << somme << std::endl;

    }
    else if (regle.id == "NEB") {
        std::cout << std::string(80, '-') << std::endl;
        std::cout << regle.description << std::endl << "Dure encore " << regle.duree << " tour(s)." << std::endl;
        std::cout << std::string(80, '-') << std::endl << std::endl;

        // Noir
        Rouge = 0;
        Vert = 0;
        Jaune = 0;
        Bleu = 0;
        Magenta = 0;
        Cyan = 0;
        return combo != 0;
    }
    return true;
}

std::string litUneString (std::ifstream & entree){
    std::string uneChaine;
    while (true){
        std::getline (entree, uneChaine);
        if ((!entree) || (uneChaine.substr(0,2) != "//")) break;
    }
    return uneChaine;
}

int litUnEntier (std::ifstream & entree){
    std::string uneChaine;
    while (true){
        std::getline (entree, uneChaine);
        if ((!entree) || (uneChaine.substr(0,2) != "//")) break;
    }
    return stoi(uneChaine);
}

// trie les scores lus dans le fichier
void triScores (std::vector <std::pair<std::string, unsigned>> & scores) {
    sort(scores.begin(), scores.end(), [](const std::pair<std::string, unsigned> &a, const std::pair<std::string, unsigned> &b){
        return a.second < b.second; }); // https://www.geeksforgeeks.org/cpp/sort-c-stl/
}

int lancer () {
    unsigned coups (0); // Stocke le nombre de coups joués
    unsigned score = 0; // Stock le score de chaque joueur
    CPosition pos; // Tuple des coordonnées du symbole à déplacer
    pos.first = 0; pos.second = 0; // valeur arbitraire pour pas casser le code à la premiere iteration
    char coordonnée; // Variable temporaire qui stocke le choix utilisateur des coordonnées
    CMat grille; // Grille qui contiendra les symboles
    CMat matrice; // Matrice qui contiendra les emplacements des symboles à supprimer
    std::string pseudo; // pseudo pour le record
    std::vector <Regle> regles;
    std::string sensGravite = "BAS"; // Vers où les bonbons vont tomber
    bool tourNonJoue = false;
    size_t iRegle = 1;
    unsigned somme = 0;
    unsigned combo = 1;

    std::ifstream entree ("scores.txt"); // Là où on récupère les scores
    std::vector <std::pair<std::string, unsigned>> scores;
    while (entree.is_open() && !entree.eof()) { // s'il existe
        std::pair<std::string, unsigned> temp;
        temp.first = litUneString(entree);
        temp.second = litUnEntier(entree);
        scores.push_back(temp);
    }
    std::ofstream fichier ("scores.txt"); // Là où on va écrire les scores
    if (!entree.is_open()) { // s'il existe pas
        for (unsigned i=0; i<10; ++i) {
            std::pair<std::string, unsigned> temp;
            temp.first = "ANONYME";
            temp.second = 0;
            scores.push_back(temp);
            fichier << "ANONYME" << std::endl << "0" << std::endl;
        }
    }



    regles.push_back(Regle {"NEB", "Noir et blanc: l'atmosphère change, les chiffres apparaissent tous en noir sur fond "
                                  "blanc et vous n'avez plus le droit à l'erreur: éliminez au moins trois blocs à chaque tour", 5});
    regles.push_back(Regle {"7ST", "Sept statiques: Interdiction de toucher au nombre 7", 7}); // cela inclue les coordonnées mais on va pas le dire sinon c'est trop facile
    regles.push_back(Regle {"RNCN", "Rançon: éliminer des bonbons pour ajouter leur valeur à votre butin, dépassez 25 pour continuer à jouer.", 4});
    regles.push_back(Regle {"SING", "Singularité: une singularité est apparue quelque part et a changé le sens de la gravité.", 9});

    std::vector <unsigned> dureesRegles = {5, 7, 4, 9};

    unsigned nbCombo = 0; // Variable qui servira au compte des combos

    // préparation du terminal & de la grille
    affichage::changerCouleur(KReset);
    affichage::effacerEcran();
    grille::initGrille(grille);
    matrice.resize(KTailleGrille, CVLine (KTailleGrille));
    grille::initMat(matrice);
    unsigned tribut; // Ce sera le nombre qui va se dévouer pour devenir un sept statique




    std::vector <CPosition> posSept;

    // Affichage des règles
    std::cout << "Pour jouer vous donnerez :\n"
            "     - L'abscisse de l'élément à déplacer\n"
            "     - L'ordonnée de l'élément à déplacer\n"
            "     /!\\ Les abscisses et ordonnées commencent à 0 !\n"
            "     - La direction dans laquelle vous voulez le déplacer\n" << std::endl;
    std::cout << "Les touches valides de déplacement sont :\n"
            "    - ‘A’ (gauche), ‘Z’ (haut), ‘E’ (droite), ‘S’ (bas)\n" << std::endl;
    std::cout << "Voici les règles du mode infini :\n"
            "     - Vous aurez plusieurs objectifs à réaliser au cours de la partie pour continuer à jouer.\n"
            "     - Chaque objectif doit être réalisé en un nombre donné de tours.\n"
            "     - Des règles spéciales peuvent également intervenir durant la partie, il faudra en tenir compte pour continuer à jouer.\n"
            "     - Les règles spéciales feront effet pendant un nombre donné de tour.\n"
            "     - Pas de répit ! Vous aurez toujours une règle spéciale ou un objectif à atteindre pour continuer." << std::endl;

    // Le nom pour le record
    std::cout << "Entrez un pseudo pour commencer: ";
    std::cin >> pseudo;

    // début de la partie
    while(regleRespectee(regles[iRegle], grille, sensGravite, posSept, tribut, pos, somme, combo, tourNonJoue)) {
        if (regles[iRegle].duree == 1) {
            std::cout << std::string(80, '*') << std::endl << "Une nouvelle règle va être tirée au sort au prochain tour !"
                    "Vérifiez que vous avez atteint l'objectif (s'il y en a un !)" << std::endl << std::string(80, '*') << std::endl;
        }
        if (regles[iRegle].duree == 0) {
            std::cout << "Avez-vous atteint l'objectif ? Si la partie continue alors c'est le cas !" << std::endl;
            if (regles[iRegle].id == "7ST") {;
                transformer(7, tribut, grille);
            }
            regles[iRegle].duree = dureesRegles[iRegle];
            iRegle = rand() % 4;
            somme = 0;

            Noir = 30;
            Rouge = 31;
            Vert = 32;
            Jaune = 33;
            Bleu = 34;
            Magenta = 35;
            Cyan = 36;

            sensGravite = "BAS";

            continue;
        }

        --regles[iRegle].duree;

        tourNonJoue = false;
        affichage::afficherGrille(grille); // Affichage de la grille
        std::cout << "\n" << "Manche : " << coups + 1 << std::endl; // Affichage de la manche en cours

        // récupération des coordonnées & la direction
        std::cout << "Abscisse : " << std::flush;
        std::cin >> coordonnée;
        pos.second = std::stoi(&coordonnée);
        std::cout << "Ordonnée : " << std::flush;
        std::cin >> coordonnée;
        pos.first = std::stoi(&coordonnée);
        std::cout << "direction : " << std::flush;
        std::cin >> coordonnée;

        // Traitement du mouvement
        if (coordonnée == 'Z' || coordonnée == 'S' || coordonnée == 'A' || coordonnée == 'E') {
            if (grille::faireUnMouvement(grille, pos, coordonnée)) {
                combo = 0;
                while(grille::auMoinsTroisParLigne(grille, matrice) | grille::auMoinsTroisParColonne(grille, matrice)) {
                    ++combo;
                    score += compteScore(matrice, combo); // met à jour le score
                    std::vector <unsigned> l = grille::suppressionDansLaGrille(grille, matrice);
                    for (unsigned terme : l) {
                        somme += terme;
                    }

                    if (combo > 1) {
                        std::cout << "\n Combo X" << combo << " !" << std::endl;
                        affichage::afficherGrille(grille);
                        std::cout << std::endl;
                    }

                    gravite(grille, sensGravite);
                    grille::initMat(matrice);
                }
                nbCombo += 1;
                ++coups;
            }
            else {
                std::cout << "\nVous ne pouvez pas aller dans cette direction !\n" << std::endl;
                tourNonJoue = true;
                continue;
            }
        }
        else {
            std::cout << "\nVeuillez entrer une direction valide !\n" << std::endl;
            tourNonJoue = true;
            continue;
        }
    }
    ++coups; // incrémentation du nombre de coups joués

    // affichage du score final
    std::cout << std::endl << std::string(80, '^') << "Vous n'êtes pas parvenu à atteindre l'objectif, c'est perdu !" << std::endl;

    if (regles[iRegle].id == "7ST" && (pos.first == 7 || pos.second == 7)) {
        std::cout << "On vous avait pourtant dit de ne pas toucher aux 7, bien sur que ça inclue l'abscisse et l'ordonnée !" << std::endl;
    }

    std::cout << std::string(80, '^') << "- Score final : " << score << std::endl << "- Coups joués: " << coups << std::endl;

    std::cout << std::endl << std::string(30, '*') << " tableau des scores " << std::string(30, '*') << std::endl;

    std::pair<std::string, unsigned> resultat;
    resultat.first = pseudo;
    resultat.second = score;
    scores.push_back(resultat);
    triScores(scores);
    // on garde que les 10 meilleurs scores
    scores.resize(10);

    for (std::pair<std::string, unsigned> & p: scores) {
        std::cout << "  -  " << p.first << " : " << p.second << std::endl;
        fichier << p.first << std::endl << p.second << std::endl;
    }

    return 0;
}
