#include <iostream>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include "fichierfonction1.h"
#include <fstream>
#include "modehistoire.h"
using namespace std;
using namespace manipulationDeVecteur;
using namespace manipulationDeLaGrille;
using namespace testSurLaGrille;
using namespace modeHistoire;
int main()
{
    parametresDeLaPartie partie;
    unsigned choix;
    char direction;
    unsigned nbDeTours (0);
    unsigned scoreActuelle (0);
    unsigned combien (1);
    CPosition position {0,0};
    CMatrice matrice;
    cout << "veuillez saisir votre niveau : ";
    cin >> choix;
    choix = choix-1;
    selecteurDeNiveaux(choix,partie);
    InitiationGrille(matrice,partie.taille);
    afficherLaGrille(matrice);
    dynamiqueDuJeu(matrice,position,combien,scoreActuelle);
    ansiEscapeAffichage::nettoyerLEcran();
    scoreActuelle =0;
    do
    {
        string chaine;
        afficherLaGrille(matrice);
        lectureFichier("../../modeHistoire/regles_du_mode_histoire.txt");
        lectureFichier("../../modeHistoire/lore.txt",choix);
        cout << "voici votre score actuel : " << scoreActuelle << endl;
        cout << "voici vos nombres de tours restants : " << partie.nombreDeTours-nbDeTours << endl;
        cout << "veuillez mettre une direction valide : " <<flush;
        cin >> direction;
        if (tolower(direction) == 'x') break;
        cout << "veuillez mettre une position pour la ligne : "<<flush;
        cin >> chaine;
        position.second=stoul(chaine);
        cout << "veuillez mettre une position pour la colonne : "<<flush;
        cin >> chaine;
        position.first=stoul(chaine);
        faireUnMouvement(matrice,position,direction);
        if (! (auMoinsTroisDansLaColonne(matrice,position,combien) || auMoinsTroisDansLaLigne(matrice,position,combien)))
        {
            faireUnMouvement(matrice,position,direction);
        }
        else
        {
            dynamiqueDuJeu(matrice,position,combien,scoreActuelle);
            ++nbDeTours;
        }
    }
    while(nbDeTours != partie.nombreDeTours);
    if ( scoreActuelle< partie.score) cout << "vous avez perdu !" << endl;
    return 0;
}
