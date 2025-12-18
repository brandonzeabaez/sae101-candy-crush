#include <iostream>
#include <cstdlib>
#include <vector>
#include <iomanip>
using namespace std;
// Début des alias
typedef vector <unsigned> CVLine; // un type représentant une ligne de la grille
typedef vector <CVLine> CMat; // un type représentant la grille
typedef pair <unsigned, unsigned> CPosition; // une position dans la girlle

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

//Début des signatures
void clearScreen ();
void couleur (const unsigned & coul);
void couleurBonbon(const unsigned & bonbon);

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
bool atLeastThreeInAColumn (const CMat & grid, CPosition & pos, unsigned & howMany)
{
    bool siCEstAlignee (false);
    howMany = 1;
    for (size_t j (0);j < size(grid);++j) //On itère les indices des colonnes
    {
        for (size_t i (0);i < size(grid)-1 && !siCEstAlignee;++i)
        {
            /*
            On parcours la colonne en itérant l'indice de la ligne
            et on arrête lorsque le boolen est vrai ou on finit le parcours
            */
            if (grid[i][j] != KImpossible && grid[i][j] == grid[i+1][j])
            {
                /*
                On vérifie que la valeur elle ne soit pas
                vide ensuite on regarde si la valeur suivante est la même
                */
                while ((i < size(grid)-1) &&  grid[i][j]==grid[i+1][j])
                {
                    /*
                    on compte il y  a combien de bonbons d'affilées et on sort lorsqu'on dépasse
                    ou la valeur suivante n'est plus la même
                     */
                    ++howMany;
                    ++i;
                }
                if (howMany >= 3)
                {
                    /*
                    s'il y a plus de 3 bonbons d'affilées après le parcours d'un colonne on met
                    le booleen à vrai,on enregistre la position de la ligne
                    */
                    siCEstAlignee = true;
                    pos.second = i-howMany+1;
                }
                else howMany =1;
            }
        }
        if (siCEstAlignee)
        {
            /*
            On vérifie que ça soit alignée si c'est vrai
            on sort et on enregistre la position de la colonne
            */
            pos.first = j;
            break;
        }
    }
    return siCEstAlignee;
}
bool atLeastThreeInARow (const CMat & grid, CPosition & pos, unsigned & howMany)
{
    bool siCEstAlignee (false);
    howMany = 1;
    for (size_t i (0);i < size(grid);++i) //On itère les indices des lignes
    {
        for (size_t j(0);j < size(grid)-1 && !siCEstAlignee;++j)
        {
            /*
            On parcours la ligne en itérant l'indice de la colonne
            et on arrête lorsque le boolen est vrai ou on finit le parcours
            */
            if (grid[i][j] != KImpossible && grid[i][j] == grid[i][j+1])
            {
                /*
                On vérifie que la valeur elle ne soit pas
                vide ensuite on regarde si la valeur suivante est la même
                */
                while ((j < size(grid)-1) &&  grid[i][j]==grid[i][j+1])
                {
                    /*
                    on compte il y  a combien de bonbons d'affilées et on sort lorsqu'on dépasse
                    ou la valeur suivante n'est plus la même
                     */
                    ++howMany;
                    ++j;
                }
                if (howMany >= 3)
                {
                    /*
                    s'il y a plus de 3 bonbons d'affilées après le parcours d'une ligne on met
                    le booleen à vrai,on enregistre la position de la colonne
                    */
                    siCEstAlignee = true;
                    pos.first = j-howMany+1;
                }
                else howMany =1;
            }
        }
        if (siCEstAlignee)
        {
            /*
            On vérifie que ça soit alignée si c'est vrai
            on sort et on enregistre la position de la ligne
            */
            pos.second = i;
            break;
        }
    }
    return siCEstAlignee;
}

vector <unsigned> & Delete (vector <unsigned> & VTemporaire, const size_t & PosBeg)

{
    //l'élément qui se trouve dans cette position est supprimé du vector
    for(size_t i (PosBeg);i < VTemporaire.size()-1;++i) VTemporaire[i]=VTemporaire[i+1];
    VTemporaire.resize(VTemporaire.size()-1);
    return VTemporaire;
}
vector <unsigned> & insertionElement (vector <unsigned> & VTemporaire,const size_t pos,const unsigned val)
{
    //On insère un élement à une certaine position
    VTemporaire.resize(VTemporaire.size()+1);
    for (size_t i = VTemporaire.size()-1;  pos < i; --i) VTemporaire[i]=VTemporaire[i-1];
    VTemporaire[pos]=val;
    return VTemporaire;
}

vector <unsigned> & Move (vector <unsigned> & VTemporaire, const size_t & PosBeg, const size_t & PosEnd)
{
    /*
    On combine les fonctions Delete et Insertion pour déplacer un élement
    on met les valeurs à KImpossible
    */
    unsigned val = VTemporaire[PosBeg];
    Delete(VTemporaire,PosBeg);
    insertionElement(VTemporaire,PosEnd,val);
    return VTemporaire;
}
void removalInColumn (CMat & grid, const CPosition & pos, unsigned  howMany)
{
    /*
    On extrait une colonne en l'extrayant dans un vecteur
    on modifie ce vecteur en supprimmant les valeurs d'affilées
    On met le nombre de motifs d'affilées en valeur KImposssible au début du vector
    On injecte les valeurs du vector dans la colonne de la grille
    */
    vector <unsigned> VTemporaire;
    VTemporaire.resize(grid.size());
    for (size_t i (0); i < grid.size() ;++i) VTemporaire[i] = grid[i][pos.first];
    for (size_t i (pos.second); i < pos.second+howMany ;++i) insertionElement(Delete(VTemporaire,i),0,KImpossible);
    for (size_t i (0); i < grid.size() ;++i) grid[i][pos.first] = VTemporaire[i];
}
void removalInLigne (CMat & grid, const CPosition & pos, unsigned  howMany)
{

    /*
    On supprimme une ligne en supprimmant en supprimmant une valeur dde chaque colonne le nombre de fois ou le motif se répète
    */
    for (size_t i (pos.first); i < pos.first+howMany; ++i) removalInColumn (grid,CPosition {i,pos.second},1);
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
