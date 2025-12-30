#include <iostream>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include "fichierfonction1.h"
using namespace std;
using namespace manipulationDeVecteur;
using namespace manipulationDeLaGrille;
using namespace testSurLaGrille;
void test1_row_column (CMatrice & matrice,CPosition p,unsigned h)
{
    while(auMoinsTroisDansLaLigne(matrice,p,h))
    {
        supprimmerUneLigne (matrice,p,h);
        afficherLaGrille(matrice);
    }
    while(auMoinsTroisDansLaColonne(matrice,p,h))
    {
        supprimmerUneColonne (matrice,p,h);
        afficherLaGrille(matrice);
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
    afficherLaGrille(matrice);
}
int main()
{
    //cout << "\033[" << 41 <<"m";
    unsigned h (1);
    CPosition p {0,0};
    CMatrice matrice;
    InitiationGrille(matrice,8);
    afficherLaGrille(matrice);
    test1_row_column(matrice,p,h);
    //test2_column_row(matrice,p,h);
    return 0;
}
