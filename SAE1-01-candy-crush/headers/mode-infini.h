#ifndef MODE_INFINI_H
#define MODE_INFINI_H
#include <vector>
#include <string>
typedef vector <unsigned> CVLine; // un type représentant une ligne de la grille
typedef vector <CVLine> CMat; // un type représentant la grille
typedef pair <unsigned, unsigned> CPosition; // une position dans la girlle
struct Regle {
    string id;
    string description;
    unsigned duree;
};
const unsigned KNoir    (30);
const unsigned KRouge   (31);
const unsigned KVert    (32);
const unsigned KJaune   (33);
const unsigned KBleu    (34);
const unsigned KMAgenta (35);
const unsigned KCyan    (36);
const unsigned KTailleGrille (10); // Longueur & largeur de la grille de jeu
const unsigned KNbSymboles   (5); // Nombre de symboles représentés dans la grille
const unsigned KImpossible   (0); // symbole nul
namespace modeInfini{
void changerCouleur (const unsigned & couleur);
void effacerEcran ();
void initGrille (CMat & grille);
void initMat (CMat & matrice);
void afficherGrille (const CMat & grille);
bool faireUnMouvement (CMat & grille, const CPosition & pos, const char direction, const unsigned KJoueur);
void modifieLigneMatrice (const unsigned i, const unsigned j, const unsigned combienDeSuite, CMat & matrice);
void modifieColonneMatrice (const unsigned i, const unsigned j, const unsigned combienDeSuite, CMat & matrice);
bool auMoinsTroisParLigne (const CMat & grille, CMat & matrice);
bool auMoinsTroisParColonne (const CMat & grille, CMat & matrice);
unsigned compteScore (CMat & matrice);
void suppressionDansLaGrille (CMat & grille, const CMat & matrice);
void gravite (CMat & grille);
vector <CPosition> obtenirPositionsSept (CMat & grille);
void transformer(const unsigned & a, const unsigned & b, CMat & grille);
bool regleRespectee(Regle & regle, CMat & grille, string & sensGravite, vector <CPosition> & posSept, unsigned & tribut, CPosition & pos, unsigned & somme, unsigned & combo, bool & tourNonJoue);
string litUneString (ifstream & entree);
int litUnEntier (ifstream & entree);
void triScores (vector <pair<string, unsigned>> & scores);
int modeInfini ();
}
#endif // MODE_INFINI_H
