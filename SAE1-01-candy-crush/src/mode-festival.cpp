#include "../headers/mode-festival.h"
#include "../headers/affichage.h"
#include "../headers/bombe.h"

void modeFestival::test1_row_column (CMat & matrice, CPosition p, unsigned h)
{
    while(testSurLaGrille::auMoinsTroisDansLaLigne(matrice,p,h))
    {
        manipulationDeLaGrille::supprimmerUneLigne (matrice,p,h);
        manipulationDeLaGrille::afficherLaGrille(matrice);
        std::cout << "------" << std::endl;
    }
    while(testSurLaGrille::auMoinsTroisDansLaColonne(matrice,p,h))
    {
        manipulationDeLaGrille::supprimmerUneColonne (matrice,p,h);
        manipulationDeLaGrille::afficherLaGrille(matrice);
        std::cout << "------" << std::endl;
    }
}
void modeFestival::test2_column_row (CMat & matrice, CPosition p, unsigned h)
{
    while(testSurLaGrille::auMoinsTroisDansLaColonne(matrice,p,h))
    {
        manipulationDeLaGrille::supprimmerUneColonne (matrice,p,h);
        manipulationDeLaGrille::afficherLaGrille(matrice);
    }
    while(testSurLaGrille::auMoinsTroisDansLaLigne(matrice,p,h))
    {
        manipulationDeLaGrille::supprimmerUneLigne (matrice,p,h);
        manipulationDeLaGrille::afficherLaGrille(matrice);
    }
    manipulationDeLaGrille::afficherLaGrille(matrice);
}

void modeFestival::testFestival (CMat & matrice, CPosition p, unsigned h)
{
    festival::rajouteBombe(matrice);
    manipulationDeLaGrille::afficherLaGrille(matrice);

    while(testSurLaGrille::auMoinsTroisDansLaLigne(matrice,p,h))
    {
        unsigned couleur = festival::detectionBombe(matrice, p, h, true);
        manipulationDeLaGrille::supprimmerUneLigne (matrice,p,h);
        if (couleur != 0){
            std::cout << "On enleve couleur: "<< couleur << std::endl;
            festival::supprimeCouleurBombe(matrice, couleur);
            festival::gravite(matrice);
        }
        manipulationDeLaGrille::afficherLaGrille(matrice);
        std::cout << "------" << std::endl;
    }

    while(testSurLaGrille::auMoinsTroisDansLaColonne(matrice,p,h))
    {
        unsigned couleur = festival::detectionBombe(matrice, p, h, false);
        manipulationDeLaGrille::supprimmerUneColonne (matrice,p,h);
        if (couleur != 0){
            std::cout << "On enleve couleur: "<< couleur << std::endl;
            festival::supprimeCouleurBombe(matrice, couleur);
            festival::gravite(matrice);
        }
        manipulationDeLaGrille::afficherLaGrille(matrice);
        std::cout << "------" << std::endl;
    }
}


int modeFestival::lancer ()
{
    //cout << "\033[" << 41 <<"m";
    unsigned h (1);
    CPosition p {0,0};
    CMat matrice;
    manipulationDeLaGrille::InitiationGrille(matrice,8);
    //matrice[1][5] = 5;
    manipulationDeLaGrille::afficherLaGrille(matrice);
    std::cout << "------" << std::endl;
    //test1_row_column(matrice,p,h);
    //test2_column_row(matrice,p,h);
    testFestival(matrice,p,h);
    return 0;
}
