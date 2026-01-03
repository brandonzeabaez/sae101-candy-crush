#ifndef MODE_HISTOIRE_H
#define MODE_HISTOIRE_H
#include <vector>
typedef std::vector <unsigned> CVLine; // un type représentant une ligne de la grille
typedef std::vector <CVLine> CMat; // un type représentant la grille
typedef std::pair <unsigned, unsigned> CPosition; // une position dans la girlle
const unsigned K2Impossible (999);
const unsigned K2NbDeBonbons (4);
namespace modeHistoire{
void rajoutDesBonbons(CMat & grille);
void test1_row_column (CMat & matrice,CPosition p,unsigned h);
void rajoutDesBonbons(CMat & grille);
void melangeDesBonbons(CMat & grille);
void test2_column_row (CMat & matrice,CPosition p,unsigned h);
int modeHistoire ();
}
#endif // MODE_HISTOIRE_H
