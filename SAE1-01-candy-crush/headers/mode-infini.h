#ifndef MODE_INFINI_H
#define MODE_INFINI_H

#include "grille.h"

struct Regle {
    std::string id;
    std::string description;
    unsigned duree;
};

namespace modeInfini{
    void gravite (CMat & grille);
    unsigned compteScore (CMat & matrice);
    std::vector <CPosition> obtenirPositionsSept (CMat & grille);
    void transformer(const unsigned & a, const unsigned & b, CMat & grille);
    bool regleRespectee(Regle & regle, CMat & grille, std::string & sensGravite, std::vector <CPosition> & posSept, unsigned & tribut, CPosition & pos, unsigned & somme, unsigned & combo, bool & tourNonJoue);
    std::string litUneString (std::ifstream & entree);
    int litUnEntier (std::ifstream & entree);
    void triScores (std::vector <std::pair<std::string, unsigned>> & scores);
    int lancer ();
}

#endif // MODE_INFINI_H
