#ifndef MODE_FESTIVAL_H
#define MODE_FESTIVAL_H
#include <vector>
typedef vector <unsigned> CVLine; // un type représentant une ligne de la grille
typedef vector <CVLine> CMat; // un type représentant la grille
typedef pair <unsigned, unsigned> CPosition; // une position dans la girlle
namespace modeFestival{
void test1_row_column (CMatrice & matrice,CPosition p,unsigned h);
void test2_column_row (CMatrice & matrice,CPosition p,unsigned h);
void testFestival (CMatrice & matrice,CPosition p,unsigned h);
int modeFestival ();
}
#endif // MODE_FESTIVAL_H
