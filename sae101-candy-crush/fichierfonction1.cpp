#include "fichierfonction1.h"
#include <iostream>
#include <vector>
using namespace std;
//using namespace manipulationDeVecteur;
void ansiEscapeAffichage::couleur (const unsigned & coul) {
    cout << "\033[" << coul <<"m"; //On change de couleur avec coul le code couleur
}
void ansiEscapeAffichage::nettoyerLEcran () {
    cout << "\033[H\033[2J"; //on dit au terminal CTRL+L
}
void ansiEscapeAffichage::couleurBonbon(const unsigned & bonbon)
{
    switch (bonbon)
    {
    case 1 : //bonbon rouge
        couleur(KRouge+10);
        break;
    case 2 :
        couleur(KVert+10); //bonbon vert
        break;
    case 3 :
        couleur(KBleu+10); //bonbon bleu
        break;
    case 4 :
        couleur(KJaune+10); //bonbon jaune
    }
}
/*
vector <unsigned> & suppressionDElement (vector <unsigned> & VTemporaire, const size_t & positionDuDebut)
{
    //l'élément qui se trouve dans cette position est supprimé du vector
    for(size_t i (positionDuDebut);i < VTemporaire.size()-1;++i) VTemporaire[i]=VTemporaire[i+1];
    VTemporaire.resize(VTemporaire.size()-1);
    return VTemporaire;
}
*/
