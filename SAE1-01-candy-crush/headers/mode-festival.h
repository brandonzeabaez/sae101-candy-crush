#ifndef MODE_FESTIVAL_H
#define MODE_FESTIVAL_H

#include <vector>

typedef std::vector <unsigned> CVLine; // un type représentant une ligne de la grille
typedef std::vector <CVLine> CMat; // un type représentant la grille
typedef std::pair <unsigned, unsigned> CPosition; // une position dans la girlle

namespace modeFestival{
    void test1_row_column (CMat & matrice,CPosition p,unsigned h);
    void test2_column_row (CMat & matrice,CPosition p,unsigned h);
    void testFestival (CMat & matrice,CPosition p,unsigned h);
    int lancer ();
}

#endif // MODE_FESTIVAL_H
