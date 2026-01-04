/**
 * @file mode-histoire.h
*/
#ifndef MODE_HISTOIRE_H
#define MODE_HISTOIRE_H

#include <vector>

/**
 * un type représentant une ligne de la grille
*/
typedef std::vector <unsigned> CVLigne;
/**
 * un type représentant la grille
*/
typedef std::vector <CVLigne> CMat;
/**
 * un type représentant une position dans la grille
*/
typedef std::pair <unsigned, unsigned> CPosition;

/**
 * C'est là qu'on trouve toutes les fonctions qu'on utilisera pour notre mode histoire
*/
namespace modeHistoire{
    void rajoutDesBonbons(CMat & grille);
    void test1_row_column (CMat & matrice,CPosition p,unsigned h);
    void rajoutDesBonbons(CMat & grille);
    void melangeDesBonbons(CMat & grille);
    void test2_column_row (CMat & matrice,CPosition p,unsigned h);
    int lancer ();
}

#endif // MODE_HISTOIRE_H
