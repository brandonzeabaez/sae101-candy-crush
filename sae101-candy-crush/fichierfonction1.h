#ifndef FICHIERFONCTION1_H
#define FICHIERFONCTION1_H
#include <vector>
const unsigned KNoir    (30);
const unsigned KRouge   (31);
const unsigned KVert    (32);
const unsigned KJaune   (33);
const unsigned KBleu    (34);
const unsigned KMAgenta (35);
const unsigned KCyan    (36);
const unsigned KReset   (0);
const unsigned KNbDeBonbons (4);
const unsigned KImpossible (999);
namespace ansiEscapeAffichage
{
    void couleurBonbon(const unsigned & bonbon);
    void nettoyerLEcran ();
    void couleur (const unsigned & coul);
}

namespace manipulationDeVecteur
{
    std::vector <unsigned> & suppressionDElement (std::vector <unsigned> & VTemporaire, const size_t & positionDuDebut);
    std::vector <unsigned> & insertionDElement (std::vector <unsigned> & VTemporaire,const size_t pos,const unsigned val);
    std::vector <unsigned> & deplacerUnElement (std::vector <unsigned> & VTemporaire, const size_t & positionDuDebut, const size_t & positionDeFin);
}

namespace manipulationDeLaGrille
{
    typedef std::vector <unsigned> CVLigne; // un type représentant une ligne de la grille
    typedef std::vector <CVLigne> CMatrice; // un type représentant la grille
    typedef std::pair <unsigned, unsigned> CPosition; // une position dans la grille
    void InitiationGrille (CMatrice & grille, size_t taille);
    void afficherLaGrille (const CMatrice & grille);
    void faireUnMouvement (CMatrice & grille,const CPosition & pos,char direction);
    void supprimmerUneColonne (CMatrice & grille, const CPosition & pos, unsigned  combien);
    void supprimmerUneLigne (CMatrice & grille, const CPosition & pos, unsigned  combien);
}
namespace testSurLaGrille
{
    bool auMoinsTroisDansLaColonne (const manipulationDeLaGrille::CMatrice & grille, manipulationDeLaGrille::CPosition & pos, unsigned & combien);
    bool auMoinsTroisDansLaLigne (const manipulationDeLaGrille::CMatrice & grille, manipulationDeLaGrille::CPosition & pos, unsigned & combien);
}
#endif // FICHIERFONCTION1_H
