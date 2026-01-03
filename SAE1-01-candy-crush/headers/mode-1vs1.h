#ifndef MODE_1VS1_H
#define MODE_1VS1_H

#include "grille.h"

namespace mode1vs1{
    bool faireUnMouvement (CMat & grille, const CPosition & pos, const char direction, const unsigned KJoueur);
    void gravite (CMat & grille);
    void suppressionDansLaGrille (CMat & grille, const CMat & matrice);
    unsigned compteScore (CMat & matrice);
    int lancer ();
}

#endif // MODE_1VS1_H
