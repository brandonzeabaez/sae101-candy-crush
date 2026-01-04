/**
 * @file mode-1vs1.h
*/
#ifndef MODE_1VS1_H
#define MODE_1VS1_H

#include "grille.h"

/**
 * C'est là qu'on trouve toutes les fonctions qu'on utilisera pour notre mode 1vs1
*/
namespace mode1vs1{
    bool faireUnMouvement (CMat & grille, const CPosition & pos, const char direction, const unsigned KJoueur);
    void gravite (CMat & grille);
    void suppressionDansLaGrille (CMat & grille, const CMat & matrice);
    unsigned compteScore (CMat & matrice);
    int lancer ();
}

#endif // MODE_1VS1_H
