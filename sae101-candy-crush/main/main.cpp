#include <iostream>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include "fichierfonction1.h"
#include "modefestival.h"
using namespace std;
using namespace manipulationDeVecteur;
using namespace manipulationDeLaGrille;
using namespace testSurLaGrille;
using namespace festival;
void test1_row_column (CMatrice & matrice,CPosition p,unsigned h)
{
    while(auMoinsTroisDansLaLigne(matrice,p,h))
    {
        supprimmerUneLigne (matrice,p,h);
        afficherLaGrille(matrice);
        cout << "------" << endl;
    }
    while(auMoinsTroisDansLaColonne(matrice,p,h))
    {
        supprimmerUneColonne (matrice,p,h);
        afficherLaGrille(matrice);
        cout << "------" << endl;
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

void testFestival (CMatrice & matrice,CPosition p,unsigned h)
{
    rajouteBombe(matrice);
    afficherLaGrille(matrice);

    while(auMoinsTroisDansLaLigne(matrice,p,h))
    {
        int couleur = detectionBombe(matrice, p, h, true);
        supprimmerUneLigne (matrice,p,h);
        if (couleur != 0){
            cout << "On enleve couleur: "<< couleur << endl;
            supprimeCouleurBombe(matrice, couleur);
            gravite(matrice);
        }
        afficherLaGrille(matrice);
        cout << "------" << endl;
    }

    while(auMoinsTroisDansLaColonne(matrice,p,h))
    {
        int couleur = detectionBombe(matrice, p, h, false);
        supprimmerUneColonne (matrice,p,h);
        if (couleur != 0){
            cout << "On enleve couleur: "<< couleur << endl;
            supprimeCouleurBombe(matrice, couleur);
            gravite(matrice);
        }
        afficherLaGrille(matrice);
        cout << "------" << endl;
    }
}


int main()
{
    //cout << "\033[" << 41 <<"m";
    unsigned h (1);
    CPosition p {0,0};
    CMatrice matrice;
    InitiationGrille(matrice,8);
    //matrice[1][5] = 5;
    afficherLaGrille(matrice);
    cout << "------" << endl;
    //test1_row_column(matrice,p,h);
    //test2_column_row(matrice,p,h);
    testFestival(matrice,p,h);
    return 0;
}
