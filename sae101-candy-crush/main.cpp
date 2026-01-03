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
vector <string> & lectureFichier(vector <string> & vect,const size_t i = 0)
{
    ifs.open("../../modeHistoire/ascii_art.txt");
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
        vect.push_back(chaine);
    }
    ifs.close();
    return vect;
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
    /*
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
        lecteurFichier();
        cout << "veuillez mettre une position pour la ligne : ";
        cin >> chaine;
        p.second=stoul(chaine);
        cout << "veuillez mettre une position pour la colonne : ";
        cin >> chaine;
        p.first=stoul(chaine);
        cout << "veuillez mettre une direction valide : ";
        cin >> direction;
        faireUnMouvement(matrice,p,direction);
        test1_row_column(matrice,p,h);
        ansiEscapeAffichage::nettoyerLEcran();
        // afficherLaGrille(matrice);
        //test1_row_column(matrice,p,h);
    }
    while(tolower(direction)!='x');
    */
    vector <string> vec1,vec2,vec3,vec4,vec5;
    lectureFichier(vec1,1);
    lectureFichier(vec2,0);
    lectureFichier(vec4,9);
    for(unsigned i (0);i<vec1.size();++i)
    {
        vec3.push_back(vec1[i]+vec2[i]);
    }
    for(unsigned i (0);i<vec3.size();++i)
    {
        vec5.push_back(vec4[i]+vec3[i]);
    }
    for (string & chaine : vec5) cout << chaine << endl;
    //afficherLaGrille(matrice);
    //test2_column_row(matrice,p,h);
    return 0;
}
