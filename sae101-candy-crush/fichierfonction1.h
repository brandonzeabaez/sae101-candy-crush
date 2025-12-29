#ifndef FICHIERFONCTION1_H
#define FICHIERFONCTION1_H
#include <vector>
namespace ansiEscapeAffichage
{
    const unsigned KNoir    (30);
    const unsigned KRouge   (31);
    const unsigned KVert    (32);
    const unsigned KJaune   (33);
    const unsigned KBleu    (34);
    const unsigned KMAgenta (35);
    const unsigned KCyan    (36);
    void couleurBonbon(const unsigned & bonbon);
    void nettoyerLEcran ();
    void couleur (const unsigned & coul);
}
/*
namespace manipulationDeVecteur
{
    std::vector <unsigned> & suppressionDElement (std::vector <unsigned> & VTemporaire, const size_t & positionDuDebut);
}
*/
#endif // FICHIERFONCTION1_H
