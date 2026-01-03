#include "../headers/mode-histoire.h"
#include "../headers/affichage.h"

const unsigned K2Impossible (999);
const unsigned K2NbDeBonbons (4);

void modeHistoire::rajoutDesBonbons(CMat & grille)
{
    for(CVLigne & ligne : grille)
    {
        for(unsigned & cas : ligne)
        {
            if (cas == K2Impossible) cas = rand()%(K2NbDeBonbons)+1;
        }
    }
}
void modeHistoire::test1_row_column (CMat & matrice,CPosition p,unsigned h)
{
    while(testSurLaGrille::auMoinsTroisDansLaLigne(matrice,p,h))
    {
        manipulationDeLaGrille::supprimmerUneLigne (matrice,p,h);
        manipulationDeLaGrille::afficherLaGrille(matrice);
        rajoutDesBonbons(matrice);

    }
    while(testSurLaGrille::auMoinsTroisDansLaColonne(matrice,p,h))
    {
        manipulationDeLaGrille::supprimmerUneColonne (matrice,p,h);
        manipulationDeLaGrille::afficherLaGrille(matrice);
        rajoutDesBonbons(matrice);

    }

}
void modeHistoire::melangeDesBonbons(CMat & grille)
{
    for(size_t ligne (0) ; ligne < grille.size(); ++ligne)
    {
        for(size_t colonne (0) ; colonne < grille.size(); ++colonne) grille[ligne][colonne] = grille[rand()%(grille.size())][rand()%(grille.size())];
    }
}
void modeHistoire::test2_column_row (CMat & matrice,CPosition p,unsigned h)
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
}
int modeHistoire::lancer ()
{
    //cout << "\033[" << 41 <<"m";
    unsigned h (1);
    CPosition p {0,0};
    CMat matrice;
    manipulationDeLaGrille::InitiationGrille(matrice,6);
    manipulationDeLaGrille::afficherLaGrille(matrice);
    test1_row_column(matrice,p,h);
    //afficherLaGrille(matrice);
    //melangeDesBonbons(matrice);
    char direction;
    do
    {
        std::string chaine;
        manipulationDeLaGrille::afficherLaGrille(matrice);
        std::cout << "veuillez mettre une position pour la ligne : ";
        std::cin >> chaine;
        p.second=std::stoul(chaine);
        std::cout << p.second << std::endl;
        std::cout << "veuillez mettre une position pour la colonne : ";
        std::cin >> chaine;
        p.first=std::stoul(chaine);
        std::cout << p.first << std::endl;
        std::cout << "veuillez mettre une direction valide : ";
        std::cin >> direction;
        manipulationDeLaGrille::faireUnMouvement(matrice,p,direction);
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
