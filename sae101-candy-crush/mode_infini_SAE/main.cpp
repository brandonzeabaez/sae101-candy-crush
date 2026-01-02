#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

/*
    Mode Infini
    Commandes : ‘A’ (gauche), ‘Z’ (haut), ‘E’ (droite), ‘S’ (bas)
    Règles: Cette fois, quand des bonbons disparaissent, ils sont
    tout de suite remplacés ! Tenez compte des règles spéciales si
    vous voulez continuer à jouer !
*/


typedef vector <unsigned> CVLine; // un type représentant une ligne de la grille
typedef vector <CVLine> CMat; // un type représentant la grille
typedef pair <unsigned, unsigned> CPosition; // une position dans la girlle

// Les variables qui contiennent les couleurs
const unsigned KReset   (0);
unsigned Noir    (30);
unsigned Rouge   (31);
unsigned RougeAP (41);
unsigned Vert    (32);
unsigned Jaune   (33);
unsigned Bleu    (34);
unsigned Magenta (35);
unsigned Cyan    (36);

const unsigned KTailleGrille (10); // Longueur & largeur de la grille de jeu
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
                changerCouleur(Rouge);
                break;
            case 2:
                changerCouleur(Vert);
                break;
            case 3:
                changerCouleur(Jaune);
                break;
            case 4:
                changerCouleur(Bleu);
                break;
            case 5:
                changerCouleur(Magenta);
                break;
            case 6:
                changerCouleur(Cyan);
                break;
            case 7:
                changerCouleur(RougeAP);
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

// Gestion des déplacements des bonbons de la grille
bool faireUnMouvement (CMat & grille, const CPosition & pos, const char direction) {
    bool changement = true;
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
        cout << "duhh" << k << endl;
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

// Calcule le score (nb de blocs éliminés * combo)
unsigned compteScore (CMat & matrice, unsigned & combo) {
    unsigned score (0);
    for(CVLine & ligne : matrice)
        for(unsigned & element : ligne)
            if(element == 1)
                score = score * combo;
    return score;
}

// Supprime les nombres identiques successifs de la grille (horizontalement et vertialement)
vector <unsigned> suppressionDansLaGrille (CMat & grille, const CMat & matrice) {
    vector <unsigned> historiqueSuppressions;
    for(unsigned i (0); i <= KTailleGrille - 1; ++i) {
        for(unsigned j (0); j <= KTailleGrille - 1; ++j) {
            if(matrice[i][j] == 1) {
                historiqueSuppressions.push_back(grille[i][j]);
                grille[i][j] = 0;
            }
        }
    }
    return historiqueSuppressions;
}

// Remplace les zéros de la grille par des bonbons
void remplacerZero (CMat & grille) {
    for (unsigned i=0 ; i <= KTailleGrille - 1; ++i) {
        for (unsigned j=0 ; j <= KTailleGrille - 1; ++j) {
            if (grille[i][j] == 0) {
                grille[i][j] = rand() % KNbSymboles + 1;
            } // { }
        }
    }
}


// Fait remonter les cases vides (comme si les symboles étaient soumis à la gravité)
void gravite (CMat & grille, string & sens) {
    unsigned saut (0);
    if (sens == "BAS") { // C'est à dire les bonbons descendent
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
        afficherGrille(grille);
        // On en profite pour remplacer ce trou par un bonbon comme on l'a dit
        remplacerZero(grille);
        return;
    }

    if (sens == "HAUT") { // C'est à dire les bonbons montent
        for (unsigned h=0; h<5; ++h) { // On aura 5 bonbons alignés verticalement au maximum alors on s'assure qu'ils bougent avec cette boucle
            for (unsigned i=0; i< KTailleGrille - 1; ++i) {
                for (unsigned j=0; j< KTailleGrille - 1; ++j) {
                    if (grille[i][j] == 0) {
                        swap(grille[i][j], grille[i+1][j]);
                    }
                }
            }
        }
        afficherGrille(grille);
        // On en profite pour remplacer ce trou par un bonbon comme on l'a dit
        remplacerZero(grille);
        return;
    }

    if (sens == "DROITE") { // C'est à dire les bonbons vont vers la droite
        for (unsigned h=0; h<5; ++h) { // On aura 5 bonbons alignés horizontalement au maximum alors on s'assure qu'ils bougent avec cette boucle
            for (unsigned i=0; i< KTailleGrille - 1; ++i) {
                for (unsigned j=1; j<= KTailleGrille - 1; ++j) {
                    if (grille[i][j] == 0) {
                        swap(grille[i][j], grille[i][j-1]);
                    }
                }
            }
        }
        afficherGrille(grille);
        // On en profite pour remplacer ce trou par un bonbon comme on l'a dit
        remplacerZero(grille);
        return;
    }

    if (sens == "GAUCHE") { // C'est à dire les bonbons vont vers la gauche
        for (unsigned h=0; h<5; ++h) { // On aura 5 bonbons alignés horizontalement au maximum alors on s'assure qu'ils bougent avec cette boucle
            for (unsigned i=0; i< KTailleGrille - 1; ++i) {
                for (unsigned j=1; j<= KTailleGrille - 1; ++j) {
                    if (grille[i][j] == 0) {
                        swap(grille[i][j], grille[i][j+1]);
                    }
                }
            }
        }
        afficherGrille(grille);
        // On en profite pour remplacer ce trou par un bonbon comme on l'a dit
        remplacerZero(grille);
        return;
    }
}

struct Regle {
    string id;
    string description;
    unsigned duree;
};

vector <CPosition> obtenirPositionsSept (CMat & grille) {
    vector <CPosition> positionsSept;
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
bool regleRespectee(Regle & regle, CMat & grille, string & sensGravite, vector <CPosition> & posSept, unsigned & tribut, CPosition & pos, unsigned & somme, unsigned & combo, bool & tourNonJoue) {
    if (tourNonJoue) {
        return true;
    }
    if (regle.id == "7ST") {
        if (regle.duree == 7) { // si la règle vient d'être mise en place
                tribut = 1 + (rand() % KNbSymboles);
                transformer(tribut, 7, grille);
                posSept = obtenirPositionsSept(grille);
        }
        cout << string(80, '-') << endl;
        cout << regle.description << endl << "Dure encore " << regle.duree << " tour(s)." << endl;
        cout << string(80, '-') << endl << endl;

        return (posSept == obtenirPositionsSept(grille) && pos.first != 7 && pos.second != 7);
    }
    else if (regle.id == "SING") {
        if (regle.duree == 9) { // si la règle vient d'être mise en place
            vector <string> sensGraviteListe = {"HAUT", "GAUCHE", "DROITE"}; // on exclus le bas pour être sûr de changer la gravité
            sensGravite = sensGraviteListe[rand() % 3]; // sens de la gravité déterminé au hasard
        }

        cout << string(80, '-') << endl;
        cout << regle.description << endl << "Dure encore " << regle.duree << " tour(s)." << endl;
        cout << string(80, '-') << endl << endl;

        cout << "Tiens, on dirait que la singularité est apparue, elle attire les bonbons vers cette partie de l'espace: " << sensGravite << endl;

        return true;
    }
    else if (regle.id == "RNCN") {
        if (regle.duree == 0 && somme < 25) return false;
        cout << string(80, '-') << endl;
        cout << regle.description << endl << "Dure encore " << regle.duree << " tour(s)." << endl;
        cout << string(80, '-') << endl << endl;

        cout << "Votre butin s'élève à " << somme << endl;

    }
    else if (regle.id == "NEB") {
        cout << string(80, '-') << endl;
        cout << regle.description << endl << "Dure encore " << regle.duree << " tour(s)." << endl;
        cout << string(80, '-') << endl << endl;

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

string litUneString (ifstream & entree){
    string uneChaine;
    while (true){
        getline (entree, uneChaine);
        if ((!entree) || (uneChaine.substr(0,2) != "//")) break;
    }
    return uneChaine;
}

int litUnEntier (ifstream & entree){
    string uneChaine;
    while (true){
        getline (entree, uneChaine);
        if ((!entree) || (uneChaine.substr(0,2) != "//")) break;
    }
    return stoi(uneChaine);
}

// trie les scores lus dans le fichier
void triScores (vector <pair<string, unsigned>> & scores) {
    sort(scores.begin(), scores.end(), [](const pair<string, unsigned> &a, const pair<string, unsigned> &b){
        return a.second < b.second; }); // https://www.geeksforgeeks.org/cpp/sort-c-stl/
}

int main () {
    unsigned coups (0); // Stocke le nombre de coups joués
    unsigned score = 0; // Stock le score de chaque joueur
    CPosition pos; // Tuple des coordonnées du symbole à déplacer
    pos.first = 0; pos.second = 0; // valeur arbitraire pour pas casser le code à la premiere iteration
    char coordonnée; // Variable temporaire qui stocke le choix utilisateur des coordonnées
    CMat grille; // Grille qui contiendra les symboles
    CMat matrice; // Matrice qui contiendra les emplacements des symboles à supprimer
    string pseudo; // pseudo pour le record
    vector <Regle> regles;
    string sensGravite = "BAS"; // Vers où les bonbons vont tomber
    bool tourNonJoue = false;
    size_t iRegle = 1;
    unsigned somme = 0;
    unsigned combo = 1;

    ifstream entree ("scores.txt"); // Là où on récupère les scores
    vector <pair<string, unsigned>> scores;
    while (entree.is_open() && !entree.eof()) { // s'il existe
        pair<string, unsigned> temp;
        temp.first = litUneString(entree);
        temp.second = litUnEntier(entree);
        scores.push_back(temp);
    }
    ofstream fichier ("scores.txt"); // Là où on va écrire les scores
    if (!entree.is_open()) { // s'il existe pas
        for (unsigned i=0; i<10; ++i) {
            pair<string, unsigned> temp;
            temp.first = "ANONYME";
            temp.second = 0;
            scores.push_back(temp);
            fichier << "ANONYME" << endl << "0" << endl;
        }
    }



    regles.push_back(Regle {"NEB", "Noir et blanc: l'atmosphère change, les chiffres apparaissent tous en noir sur fond "
                                  "blanc et vous n'avez plus le droit à l'erreur: éliminez au moins trois blocs à chaque tour", 5});
    regles.push_back(Regle {"7ST", "Sept statiques: Interdiction de toucher au nombre 7", 7}); // cela inclue les coordonnées mais on va pas le dire sinon c'est trop facile
    regles.push_back(Regle {"RNCN", "Rançon: éliminer des bonbons pour ajouter leur valeur à votre butin, dépassez 25 pour continuer à jouer.", 4});
    regles.push_back(Regle {"SING", "Singularité: une singularité est apparue quelque part et a changé le sens de la gravité.", 9});

    vector <unsigned> dureesRegles = {5, 7, 4, 9};

    unsigned nbCombo = 0; // Variable qui servira au compte des combos

    // préparation du terminal & de la grille
    changerCouleur(KReset);
    effacerEcran();
    initGrille(grille);
    matrice.resize(KTailleGrille, CVLine (KTailleGrille));
    initMat(matrice);
    unsigned tribut; // Ce sera le nombre qui va se dévouer pour devenir un sept statique




    vector <CPosition> posSept;

    // Affichage des règles
    cout << "Pour jouer vous donnerez :\n"
            "     - L'abscisse de l'élément à déplacer\n"
            "     - L'ordonnée de l'élément à déplacer\n"
            "     /!\\ Les abscisses et ordonnées commencent à 0 !\n"
            "     - La direction dans laquelle vous voulez le déplacer\n" << endl;
    cout << "Les touches valides de déplacement sont :\n"
            "    - ‘A’ (gauche), ‘Z’ (haut), ‘E’ (droite), ‘S’ (bas)\n" << endl;
    cout << "Voici les règles du mode infini :\n"
            "     - Vous aurez plusieurs objectifs à réaliser au cours de la partie pour continuer à jouer.\n"
            "     - Chaque objectif doit être réalisé en un nombre donné de tours.\n"
            "     - Des règles spéciales peuvent également intervenir durant la partie, il faudra en tenir compte pour continuer à jouer.\n"
            "     - Les règles spéciales feront effet pendant un nombre donné de tour.\n"
            "     - Pas de répit ! Vous aurez toujours une règle spéciale ou un objectif à atteindre pour continuer." << endl;

    // Le nom pour le record
    cout << "Entrez un pseudo pour commencer: ";
    cin >> pseudo;

    // début de la partie
    while(regleRespectee(regles[iRegle], grille, sensGravite, posSept, tribut, pos, somme, combo, tourNonJoue)) {
        if (regles[iRegle].duree == 1) {
            cout << string(80, '*') << endl << "Une nouvelle règle va être tirée au sort au prochain tour !"
                    "Vérifiez que vous avez atteint l'objectif (s'il y en a un !)" << endl << string(80, '*') << endl;
        }
        if (regles[iRegle].duree == 0) {
            cout << "Avez-vous atteint l'objectif ? Si la partie continue alors c'est le cas !" << endl;
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
        afficherGrille(grille); // Affichage de la grille
        cout << "\n" << "Manche : " << coups + 1 << endl; // Affichage de la manche en cours

        // récupération des coordonnées & la direction
        cout << "Abscisse : " << flush;
        cin >> coordonnée;
        pos.second = stoi(&coordonnée);
        cout << "Ordonnée : " << flush;
        cin >> coordonnée;
        pos.first = stoi(&coordonnée);
        cout << "direction : " << flush;
        cin >> coordonnée;

        // Traitement du mouvement
        if (coordonnée == 'Z' || coordonnée == 'S' || coordonnée == 'A' || coordonnée == 'E') {
            if (faireUnMouvement(grille, pos, coordonnée)) {
                combo = 0;
                while(auMoinsTroisParLigne(grille, matrice) | auMoinsTroisParColonne(grille, matrice)) {
                    ++combo;
                    score += compteScore(matrice, combo); // met à jour le score
                    vector <unsigned> l = suppressionDansLaGrille(grille, matrice);
                    for (unsigned terme : l) {
                        somme += terme;
                    }

                    if (combo > 1) {
                        cout << "\n Combo X" << combo << " !" << endl;
                        afficherGrille(grille);
                        cout << endl;
                    }

                    gravite(grille, sensGravite);
                    initMat(matrice);
                }
                nbCombo += 1;
                ++coups;
            }
            else {
                cout << "\nVous ne pouvez pas aller dans cette direction !\n" << endl;
                tourNonJoue = true;
                continue;
            }
        }
        else {
            cout << "\nVeuillez entrer une direction valide !\n" << endl;
            tourNonJoue = true;
            continue;
        }
    }
    ++coups; // incrémentation du nombre de coups joués

    // affichage du score final
    cout << endl << string(80, '^') << "Vous n'êtes pas parvenu à atteindre l'objectif, c'est perdu !" << endl;

    if (regles[iRegle].id == "7ST" && (pos.first == 7 || pos.second == 7)) {
        cout << "On vous avait pourtant dit de ne pas toucher aux 7, bien sur que ça inclue l'abscisse et l'ordonnée !" << endl;
    }

    cout << string(80, '^') << "- Score final : " << score << endl << "- Coups joués: " << coups << endl;

    cout << endl << string(30, '*') << " tableau des scores " << string(30, '*') << endl;

    pair<string, unsigned> resultat;
    resultat.first = pseudo;
    resultat.second = score;
    scores.push_back(resultat);
    triScores(scores);
    // on garde que les 10 meilleurs scores
    scores.resize(10);

    for (pair<string, unsigned> & p: scores) {
        cout << "  -  " << p.first << " : " << p.second << endl;
        fichier << p.first << endl << p.second << endl;
    }

    return 0;
}
