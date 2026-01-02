#include "../headers/mode-histoire.h"
#include "../headers/affichage.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <iomanip>
using namespace std;
using namespace manipulationDeVecteur;
using namespace manipulationDeLaGrille;
using namespace testSurLaGrille;
const unsigned K2Impossible (999);
const unsigned K2NbDeBonbons (4);
void rajoutDesBonbons(CMatrice & grille);
void test1_row_column (CMatrice & matrice,CPosition p,unsigned h)
{
    while(auMoinsTroisDansLaLigne(matrice,p,h))
    {
        supprimmerUneLigne (matrice,p,h);
        afficherLaGrille(matrice);
        rajoutDesBonbons(matrice);

    }
    while(auMoinsTroisDansLaColonne(matrice,p,h))
    {
        supprimmerUneColonne (matrice,p,h);
        afficherLaGrille(matrice);
        rajoutDesBonbons(matrice);

    }

}
void rajoutDesBonbons(CMatrice & grille)
{
    for(CVLigne & ligne : grille)
    {
        for(unsigned & cas : ligne)
        {
            if (cas == K2Impossible) cas = rand()%(K2NbDeBonbons)+1;
        }
    }
}
void melangeDesBonbons(CMatrice & grille)
{
    for(size_t ligne (0) ; ligne < grille.size(); ++ligne)
    {
        for(size_t colonne (0) ; colonne < grille.size(); ++colonne) grille[ligne][colonne] = grille[rand()%(grille.size())][rand()%(grille.size())];
    }
}
void test2_column_row (CMatrice & matrice,CPosition p,unsigned h)
{
    while(auMoinsTroisDansLaColonne(matrice,p,h))
    {
        supprimmerUneColonne (matrice,p,h);
        afficherLaGrille(matrice);
    }
    while(auMoinsTroisDansLaLigne(matrice,p,h))
    {
        supprimmerUneLigne (matrice,p,h);
        afficherLaGrille(matrice);
    }
}
int modeHistoire ()
{
    //cout << "\033[" << 41 <<"m";
    unsigned h (1);
    CPosition p {0,0};
    CMatrice matrice;
    InitiationGrille(matrice,6);
    afficherLaGrille(matrice);
    test1_row_column(matrice,p,h);
    //afficherLaGrille(matrice);
    //melangeDesBonbons(matrice);
    char direction;
    do
    {
        string chaine;
        afficherLaGrille(matrice);
        cout << "veuillez mettre une position pour la ligne : ";
        cin >> chaine;
        p.second=stoul(chaine);
        cout << p.second << endl;
        cout << "veuillez mettre une position pour la colonne : ";
        cin >> chaine;
        p.first=stoul(chaine);
        cout << p.first << endl;
        cout << "veuillez mettre une direction valide : ";
        cin >> direction;
        faireUnMouvement(matrice,p,direction);
        test1_row_column(matrice,p,h);
        ansiEscapeAffichage::nettoyerLEcran();
        // afficherLaGrille(matrice);
        //test1_row_column(matrice,p,h);
    }
    while(tolower(direction)!='x');
    //afficherLaGrille(matrice);
    //test2_column_row(matrice,p,h);
    return 0;
}
