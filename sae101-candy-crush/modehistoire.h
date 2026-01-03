#ifndef MODEHISTOIRE_H
#define MODEHISTOIRE_H
#include "fichierfonction1.h"
#include <iostream>
struct parametresDeLaPartie
{
    size_t taille;
    unsigned nombreDeTours;
    unsigned score;
};
namespace modeHistoire
{
    void dynamiqueDuJeu (manipulationDeLaGrille::CMatrice & matrice,manipulationDeLaGrille::CPosition p,unsigned h,unsigned & cpt);
    void rajoutDesBonbons(manipulationDeLaGrille::CMatrice & grille);
    void lectureFichier(const std::string & cheminDuFichier,const size_t i = 0);
    void selecteurDeNiveaux(const unsigned & niveau,parametresDeLaPartie & partie);
    std::string lectureDeChiffresDansUneChaine(const std::string & chaine);
    void melangeDesBonbons(manipulationDeLaGrille::CMatrice & grille);
}

#endif // MODEHISTOIRE_H
