#include <iostream>
#include <cstdlib>
#include <vector>
#include <iomanip>
using namespace std;
// Début des alias
typedef vector <unsigned> CVLine; // un type représentant une ligne de la grille
typedef vector <CVLine> CMat; // un type représentant la grille
typedef pair <unsigned, unsigned> CPosition; // une position dans la girlle
// Fin de l'alias
//Début de la déclaration des constantes
const unsigned KReset   (0);
const unsigned KNoir    (30);
const unsigned KRouge   (31);
const unsigned KVert    (32);
const unsigned KJaune   (33);
const unsigned KBleu    (34);
const unsigned KMAgenta (35);
const unsigned KCyan    (36);
const unsigned KnbCandies (4);
const unsigned KImpossible (999);
//Fin de la déclaration des constantes
//Début des signatures
void clearScreen ();
void couleur (const unsigned & coul);
void couleurBonbon(const unsigned & bonbon);
//Fin des signatures
void InitGrid (CMat & Grid, size_t Size)
{
    Grid.resize(Size, CVLine (Size));
    for (CVLine & col : Grid)
    {
        for (unsigned & lign : col) lign = rand()%(KnbCandies)+1; // on choisit un nb random entre [1,nbCandies]
    }
}
void displayGrid (const CMat & grid)
{
    clearScreen(); //on nettoie le screen
    for (const CVLine & uneLigne : grid) // On parcourt le vect CMat
    {
        for (const unsigned & cellule : uneLigne) //On parcourt chaque ligne de la matrice
        {
            if (cellule >= 1 && cellule <= KnbCandies) //il faut que la cellule corresponde à un bonbon
            {
                couleurBonbon(cellule); // on affecte chaque case à une couleur selon sa valeur
                cout << setw(3) << cellule;// on espace de 2 et le 3eme charactere est la case
            }
            else
            {
                couleur(KReset);
                cout << setw(3) << ' '; //si ça correspond pas on a une case vide
            }
        }
        cout << endl; // saut de ligne à chaque ligne de la matrice
    }
    couleur(KReset); // on remet la couleur à la normale
}
void couleurBonbon(const unsigned & bonbon)
{
    switch (bonbon)
    {
    case 1 : //bonbon rouge
        couleur(KRouge+10);
        break;
    case 2 :
        couleur(KVert+10); //bonbon vert
        break;
    case 3 :
        couleur(KBleu+10); //bonbon bleu
        break;
    case 4 :
        couleur(KJaune+10); //bonbon jaune
    }
}

void clearScreen () {
    cout << "\033[H\033[2J"; //on dit au terminal CTRL+L
}
void couleur (const unsigned & coul) {
    cout << "\033[" << coul <<"m"; //On change de couleur avec coul le code couleur
}

void MakeAMove (CMat & Grid,const CPosition & pos,char Direction)
{
    if ( ((pos.first <= Grid.size()-1)) && ((pos.second <= Grid.size()-1))) //C'est des unsigned et on a donc pas besoin de la condition >=0
    {
        switch (tolower(Direction)) //On interprete les char Maj
        {
        case 'z' :
            if (pos.second > 0 ) //On évite la ligne qui est tt en haut
            {
                swap(Grid[pos.second][pos.first],Grid[pos.second-1][pos.first]); //On permute la case en haut
                break;
            }
            else break;
        case 's' :
            if (pos.second < Grid.size()-1) //On évite la ligne qui est tt en bas
            {
                swap(Grid[pos.second][pos.first],Grid[pos.second+1][pos.first]); //On permute la case en bas
                break;
            }
            else break;
        case 'a' :
            if (pos.first > 0) //On évite la colonne qui est tt à gauche
            {
                swap(Grid[pos.second][pos.first],Grid[pos.second][pos.first-1]); //On permute la case à gauche
                break;
            }
            else break;
        case 'e' :
            if (pos.first < Grid.size()-1) //On évite la colonne qui est tt à droite
            {
                swap(Grid[pos.second][pos.first],Grid[pos.second][pos.first+1]); //On permute la case à droite
                break;
            }
            else break;
        default :
            cout << "appuyer sur une touche valide" << endl;
        }
    }
}
/*
bool atLeastThreeInAColumn (const CMat & grid, CPosition & pos, unsigned & howMany)
{
    bool siCEstAlignee (false);
    for (size_t colonne (0); colonne < grid.size();++colonne)
    {
        howMany=1;
        for (size_t ligne (0);ligne < grid.size()-1;++ligne)
        {
            if (grid[ligne][colonne] == grid[ligne+1][colonne] && grid[ligne][colonne]!=KImpossible)
            {
                ++howMany;
                continue;
            }
            else if (howMany >= 3)
            {
                siCEstAlignee = true;
                pos = {colonne,ligne-howMany+1};
                break;
            }
            else howMany=1;
        }
        if (siCEstAlignee == true) break;
    }
    return siCEstAlignee;
}
*/
bool atLeastThreeInAColumn (const CMat & grid, CPosition & pos, unsigned & howMany)
{
    bool siCEstAlignee (false);
    size_t i (0);
    size_t j (0);
    howMany = 1;
    while (j < size(grid))
    {
        while (i < size(grid)-1 && !siCEstAlignee)
        {
            if (grid[i][j] != KImpossible && grid[i][j] == grid[i+1][j])
            {
                while ((i < size(grid)-1) &&  grid[i][j]==grid[i+1][j])
                {
                    ++howMany;
                    /*
                    if (howMany >= 3)
                    {
                        siCEstAlignee = true;
                        pos.second = i-howMany+1;
                    }
                    */
                    ++i;

                }
                if (howMany >= 3)
                {
                    siCEstAlignee = true;
                    pos.second = i-howMany+1;
                }
                else howMany =1;
            }
            else ++i;
        }
        i = 0;
        if (siCEstAlignee)
        {
            pos.first = j;
            break;
        }
        ++j;
    }
    return siCEstAlignee;
}
bool atLeastThreeInARow (const CMat & grid, CPosition & pos, unsigned & howMany)
{
    bool siCEstAlignee (false);
    for (size_t ligne (0); ligne < grid.size();++ligne)
    {
        howMany=1;
        for (size_t colonne (0);colonne < grid.size()-1;++colonne)
        {
            if (grid[ligne][colonne] == grid[ligne][colonne+1] && grid[ligne][colonne]!=KImpossible)
            {
                ++howMany;
                continue;
            }
            else if (howMany >= 3)
            {
                siCEstAlignee = true;
                pos = {colonne-howMany+1,ligne};
                break;
            }
            else howMany=1;
        }
        if (siCEstAlignee == true) break;
    }
    return siCEstAlignee;
}

vector <unsigned> & Delete (vector <unsigned> & VTemporaire, const size_t & PosBeg)

{
    for(size_t i (PosBeg);i < VTemporaire.size()-1;++i) VTemporaire[i]=VTemporaire[i+1];
    VTemporaire.resize(VTemporaire.size()-1);
    return VTemporaire;
}
vector <unsigned> & insertionElement (vector <unsigned> & VTemporaire,const size_t pos,const unsigned val)
{
    VTemporaire.resize(VTemporaire.size()+1);
    for (size_t i = VTemporaire.size()-1;  pos < i; --i)
    {
        VTemporaire[i]=VTemporaire[i-1];
    }
    VTemporaire[pos]=val;
    return VTemporaire;
}

vector <unsigned> & Move (vector <unsigned> & VTemporaire, const size_t & PosBeg, const size_t & PosEnd)
{
    Delete(VTemporaire,PosBeg);
    insertionElement(VTemporaire,PosEnd,KImpossible);
    return VTemporaire;
}
void removalInColumn (CMat & grid, const CPosition & pos, unsigned  howMany)
{
    vector <unsigned> VTemporaire;
    VTemporaire.resize(grid.size());
    for (size_t i (0); i < grid.size() ;++i) VTemporaire[i] = grid[i][pos.first];
    for (size_t i (pos.second); i < pos.second+howMany ;++i) Move(VTemporaire,i,0);
    for (size_t i (0); i < grid.size() ;++i) grid[i][pos.first] = VTemporaire[i];
}
void removalInLigne (CMat & grid, const CPosition & pos, unsigned  howMany)
{
    for (size_t i (pos.first); i < pos.first+howMany; ++i)
    {
        removalInColumn (grid,CPosition {i,pos.second},1);
    }
}

void test1_row_column (CMat & matrice,CPosition p,unsigned h)
{
    while(atLeastThreeInARow(matrice,p,h))
    {
        removalInLigne (matrice,p,h);
        displayGrid(matrice);
    }
    while(atLeastThreeInAColumn(matrice,p,h))
    {
        removalInColumn (matrice,p,h);
        displayGrid(matrice);
    }
}
void test2_column_row (CMat & matrice,CPosition p,unsigned h)
{
    while(atLeastThreeInAColumn(matrice,p,h))
    {
        removalInColumn (matrice,p,h);
        displayGrid(matrice);
    }
    while(atLeastThreeInARow(matrice,p,h))
    {
        removalInLigne (matrice,p,h);
        displayGrid(matrice);
    }
    displayGrid(matrice);
}
int main()
{
    //cout << "\033[" << 41 <<"m";
    unsigned h (1);
    CPosition p {0,0};
    CMat matrice;
    InitGrid(matrice,8);
    displayGrid(matrice);
    /*
    if (atLeastThreeInAColumn(matrice,p,h))
    {
        cout << "la position en ligne : " << p.second <<endl;
        cout << "la position en colonne : " << p.first <<endl;
        cout << "il y a  : " << h <<" d'alignées"<<endl;
        removalInColumn(matrice,p,h);
        displayGrid(matrice);
    }
    */
    /*
    while(atLeastThreeInAColumn(matrice,p,h))
    {
        cout << "la position en ligne : " << p.second <<endl;
        cout << "la position en colonne : " << p.first <<endl;
        cout << "il y a  : " << h <<" d'alignées"<<endl;
        removalInColumn(matrice,p,h);
        displayGrid(matrice);
    }
    */
    test1_row_column(matrice,p,h);
    //test2_column_row(matrice,p,h);
    return 0;
}
