#include <iostream>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include "fichierfonction1.h"
#include <fstream>

using namespace std;
using namespace manipulationDeVecteur;
using namespace manipulationDeLaGrille;
using namespace testSurLaGrille;
const unsigned K2Impossible (999);
const unsigned K2NbDeBonbons (4);
void rajoutDesBonbons(CMatrice & grille);
ifstream ifs;
void test1_row_column (CMatrice & matrice,CPosition p,unsigned h,unsigned & cpt)
{
    while(auMoinsTroisDansLaLigne(matrice,p,h))
    {
        supprimmerUneLigne (matrice,p,h);
        cpt = cpt +100;
        afficherLaGrille(matrice);
        rajoutDesBonbons(matrice);
    }
    while(auMoinsTroisDansLaColonne(matrice,p,h))
    {
        supprimmerUneColonne (matrice,p,h);
        cpt = cpt +100;
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
void lectureFichier(const string & cheminDuFichier,const size_t i = 0)
{
    ifs.open(cheminDuFichier);
    for (size_t j (0);j!=i && !ifs.eof();++j)
    {
        for(string chaine;!ifs.eof();)
        {
            getline(ifs,chaine);
            if(chaine=="####") break;
        }
    }
    for(string chaine;!ifs.eof();)
    {
        getline(ifs,chaine);
        if(chaine=="####") break;
        cout << chaine << endl;
    }
    ifs.close();
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
    unsigned cpt (0);
    unsigned h (1);
    CPosition p {0,0};
    CMatrice matrice;
    InitiationGrille(matrice,6);
    afficherLaGrille(matrice);
    test1_row_column(matrice,p,h,cpt);
    //afficherLaGrille(matrice);
    //melangeDesBonbons(matrice);
    cpt =0;
    char direction;
    do
    {
        string chaine;
        afficherLaGrille(matrice);
        cout << "voici votre score actuel : " << cpt <<endl;
        //lectureFichier();
        cout << "veuillez mettre une position pour la ligne : ";
        cin >> chaine;
        p.second=stoul(chaine);
        cout << "veuillez mettre une position pour la colonne : ";
        cin >> chaine;
        p.first=stoul(chaine);
        cout << "veuillez mettre une direction valide : ";
        cin >> direction;
        faireUnMouvement(matrice,p,direction);
        if (! (auMoinsTroisDansLaColonne(matrice,p,h) || auMoinsTroisDansLaLigne(matrice,p,h))) faireUnMouvement(matrice,p,direction);
        else test1_row_column(matrice,p,h,cpt);

        //test1_row_column(matrice,p,h);
    }
    while(tolower(direction)!='x');

    //afficherLaGrille(matrice);
    //test2_column_row(matrice,p,h);
    return 0;
}
