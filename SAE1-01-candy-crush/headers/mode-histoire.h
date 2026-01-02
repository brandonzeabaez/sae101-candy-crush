#ifndef MODE_HISTOIRE_H
#define MODE_HISTOIRE_H
#include <vector>
typedef vector <unsigned> CVLine; // un type représentant une ligne de la grille
typedef vector <CVLine> CMat; // un type représentant la grille
typedef pair <unsigned, unsigned> CPosition; // une position dans la girlle
const unsigned K2Impossible (999);
const unsigned K2NbDeBonbons (4);
namespace modeHistoire{
void rajoutDesBonbons(CMatrice & grille);
void test1_row_column (CMatrice & matrice,CPosition p,unsigned h);
void rajoutDesBonbons(CMatrice & grille);
void melangeDesBonbons(CMatrice & grille);
void test2_column_row (CMatrice & matrice,CPosition p,unsigned h);
int modeHistoire ();
}
#endif // MODE_HISTOIRE_H
