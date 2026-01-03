#include "modehistoire.h"
#include "fichierfonction1.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
using namespace std;
void modeHistoire::dynamiqueDuJeu (manipulationDeLaGrille::CMatrice & matrice,manipulationDeLaGrille::CPosition p,unsigned h,unsigned & cpt)
{
    while(testSurLaGrille::auMoinsTroisDansLaLigne(matrice,p,h))
    {
        manipulationDeLaGrille::supprimmerUneLigne (matrice,p,h);
        cpt = cpt +100;
        manipulationDeLaGrille::afficherLaGrille(matrice);
        modeHistoire::rajoutDesBonbons(matrice);
    }
    while(testSurLaGrille::auMoinsTroisDansLaColonne(matrice,p,h))
    {
        manipulationDeLaGrille::supprimmerUneColonne (matrice,p,h);
        cpt = cpt +100;
        manipulationDeLaGrille::afficherLaGrille(matrice);
        modeHistoire::rajoutDesBonbons(matrice);
    }
}
void modeHistoire::rajoutDesBonbons(manipulationDeLaGrille::CMatrice & grille)
{
    for(manipulationDeLaGrille::CVLigne & ligne : grille)
    {
        for(unsigned & cas : ligne)
        {
            if (cas == KImpossible) cas = rand()%(KNbDeBonbons)+1;
        }
    }
}
void modeHistoire::lectureFichier(const string & cheminDuFichier,const size_t i )
{
    ifstream ifs;
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
void modeHistoire::selecteurDeNiveaux(const unsigned & niveau,parametresDeLaPartie & partie)
{
    ifstream ifs;
    ifs.open("../../modeHistoire/niveaux.txt");
    for (size_t j (0);j!=niveau && !ifs.eof();++j)
    {
        for(string chaine;!ifs.eof();)
        {
            getline(ifs,chaine);
            if(chaine=="####") break;
        }
    }
    ifs.clear();
    string chaine;
    getline(ifs,chaine);
    getline(ifs,chaine);
    partie.taille= stoull(modeHistoire::lectureDeChiffresDansUneChaine (chaine));
    getline(ifs,chaine);
    partie.nombreDeTours= stoul(modeHistoire::lectureDeChiffresDansUneChaine(chaine));
    getline(ifs,chaine);
    partie.score= stoul(modeHistoire::lectureDeChiffresDansUneChaine (chaine));
    ifs.close();
}
string modeHistoire::lectureDeChiffresDansUneChaine(const string & chaine)
{
    string numeros;
    for (const char & c : chaine )
    {
        if (isdigit(c)) numeros = numeros + c;
    }
    return numeros;
}
void modeHistoire::melangeDesBonbons(manipulationDeLaGrille::CMatrice & grille)
{
    for(size_t ligne (0) ; ligne < grille.size(); ++ligne)
    {
        for(size_t colonne (0) ; colonne < grille.size(); ++colonne) grille[ligne][colonne] = grille[rand()%(grille.size())][rand()%(grille.size())];
    }
}
