#include <iostream>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include "fichierfonction1.h"
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
        afficherLaGrille(matrice);
    }
    while(auMoinsTroisDansLaColonne(matrice,p,h))
    {
        supprimmerUneColonne (matrice,p,h);
        afficherLaGrille(matrice);
        rajoutDesBonbons(matrice);
        afficherLaGrille(matrice);
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
int main()
{
    //cout << "\033[" << 41 <<"m";
    unsigned h (1);
    CPosition p {0,0};
    CMatrice matrice;
    InitiationGrille(matrice,13);
    afficherLaGrille(matrice);
    test1_row_column(matrice,p,h);
    p = {2,2};
    faireUnMouvement(matrice,p,'z');
    afficherLaGrille(matrice);
    melangeDesBonbons(matrice);
    afficherLaGrille(matrice);
    // for (unsigned i (0);i<5;++i)
    // {
    //     string chaine;
    //     cout << "veuillez mettre une position pour la ligne : " ;
    //     getline(cin,chaine);
    //     p.second = stoul(chaine);
    //     cout << '\n' <<"veuillez mettre une position pour la colonne : " ;
    //     getline(cin,chaine);
    //     p.first = stoul(chaine);
    //     cout << '\n' << "veuillez appuyer sur la touche directionnelle : ";
    //     direction = char(getchar());
    //     cout << endl;
    //     faireUnMouvement(matrice,p,'z');
    //     afficherLaGrille(matrice);
    //     test1_row_column(matrice,p,h);
    // }
    //afficherLaGrille(matrice);
    //test2_column_row(matrice,p,h);
    return 0;
}
