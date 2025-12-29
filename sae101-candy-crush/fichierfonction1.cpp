#include "fichierfonction1.h"
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

void ansiEscapeAffichage::couleur (const unsigned & coul)
{
    cout << "\033[" << coul <<"m"; //On change de couleur avec coul le code couleur
}
void ansiEscapeAffichage::nettoyerLEcran () {
    cout << "\033[H\033[2J"; //on dit au terminal CTRL+L
}
void ansiEscapeAffichage::couleurBonbon(const unsigned & bonbon)
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

vector <unsigned> & manipulationDeVecteur::suppressionDElement (vector <unsigned> & VTemporaire, const size_t & positionDuDebut)
{
    //l'élément qui se trouve dans cette position est supprimé du vector
    for(size_t i (positionDuDebut);i < VTemporaire.size()-1;++i) VTemporaire[i]=VTemporaire[i+1];
    VTemporaire.resize(VTemporaire.size()-1);
    return VTemporaire;
}
vector <unsigned> & manipulationDeVecteur::insertionDElement (vector <unsigned> & VTemporaire,const size_t pos,const unsigned val)
{
    //On insère un élement à une certaine position
    VTemporaire.resize(VTemporaire.size()+1);
    for (size_t i = VTemporaire.size()-1;  pos < i; --i) VTemporaire[i]=VTemporaire[i-1];
    VTemporaire[pos]=val;
    return VTemporaire;
}

vector <unsigned> & manipulationDeVecteur::deplacerUnElement (vector <unsigned> & VTemporaire, const size_t & positionDuDebut, const size_t & positionDeFin)
{
    //On combine les fonctions suppressionDElement et Insertion pour déplacer un élement
    //on met les valeurs à KImpossible
    unsigned val = VTemporaire[positionDuDebut];
    manipulationDeVecteur::suppressionDElement(VTemporaire,positionDuDebut);
    manipulationDeVecteur::insertionDElement(VTemporaire,positionDeFin,val);
    return VTemporaire;
}

void manipulationDeLaGrille::InitiationGrille (CMatrice & grille, size_t taille)
{
    grille.resize(taille, CVLigne (taille));
    for (CVLigne & col : grille)
    {
        for (unsigned & ligne : col) ligne = rand()%(KNbDeBonbons)+1; // on choisit un nb random entre [1,nbCandies]
    }
}
void manipulationDeLaGrille::afficherLaGrille (const CMatrice & grille)
{
    ansiEscapeAffichage::nettoyerLEcran(); //on nettoie le screen
    for (const CVLigne & uneLigne : grille) // On parcourt le vect CMatrice
    {
        for (const unsigned & cellule : uneLigne) //On parcourt chaque ligne de la matrice
        {
            if (cellule >= 1 && cellule <= KNbDeBonbons) //il faut que la cellule corresponde à un bonbon
            {
                ansiEscapeAffichage::couleurBonbon(cellule); // on affecte chaque case à une couleur selon sa valeur
                cout << setw(3) << cellule;// on espace de 2 et le 3eme charactere est la case
            }
            else
            {
                ansiEscapeAffichage::couleur(KReset);
                cout << setw(3) << ' '; //si ça correspond pas on a une case vide
            }
        }
        cout << endl; // saut de ligne à chaque ligne de la matrice
    }
    ansiEscapeAffichage::couleur(KReset); // on remet la couleur à la normale
}

void manipulationDeLaGrille::faireUnMouvement (CMatrice & grille,const CPosition & pos,char direction)
{
    if ( ((pos.first <= grille.size()-1)) && ((pos.second <= grille.size()-1))) //C'est des unsigned et on a donc pas besoin de la condition >=0
    {
        switch (tolower(direction)) //On interprete les char Maj
        {
        case 'z' :
            if (pos.second > 0 ) //On évite la ligne qui est tt en haut
            {
                swap(grille[pos.second][pos.first],grille[pos.second-1][pos.first]); //On permute la case en haut
                break;
            }
            else break;
        case 's' :
            if (pos.second < grille.size()-1) //On évite la ligne qui est tt en bas
            {
                swap(grille[pos.second][pos.first],grille[pos.second+1][pos.first]); //On permute la case en bas
                break;
            }
            else break;
        case 'a' :
            if (pos.first > 0) //On évite la colonne qui est tt à gauche
            {
                swap(grille[pos.second][pos.first],grille[pos.second][pos.first-1]); //On permute la case à gauche
                break;
            }
            else break;
        case 'e' :
            if (pos.first < grille.size()-1) //On évite la colonne qui est tt à droite
            {
                swap(grille[pos.second][pos.first],grille[pos.second][pos.first+1]); //On permute la case à droite
                break;
            }
            else break;
        default :
            cout << "appuyer sur une touche valide" << endl;
        }
    }
}

void manipulationDeLaGrille::supprimmerUneColonne (CMatrice & grille, const CPosition & pos, unsigned  combien)
{
    /*
    On extrait une colonne en l'extrayant dans un vecteur
    on modifie ce vecteur en supprimmant les valeurs d'affilées
    On met le nombre de motifs d'affilées en valeur KImposssible au début du vector
    On injecte les valeurs du vector dans la colonne de la grille
    */
    vector <unsigned> VTemporaire;
    VTemporaire.resize(grille.size());
    for (size_t i (0); i < grille.size() ;++i) VTemporaire[i] = grille[i][pos.first];
    for (size_t i (pos.second); i < pos.second+combien ;++i) manipulationDeVecteur::insertionDElement(manipulationDeVecteur::suppressionDElement(VTemporaire,i),0,KImpossible);
    for (size_t i (0); i < grille.size() ;++i) grille[i][pos.first] = VTemporaire[i];
}

void manipulationDeLaGrille::supprimmerUneLigne (CMatrice & grille, const CPosition & pos, unsigned  combien)
{
    /*
    On supprimme une ligne en supprimmant en supprimmant une valeur dde chaque colonne le nombre de fois ou le motif se répète
    */
    for (size_t i (pos.first); i < pos.first+combien; ++i) manipulationDeLaGrille::supprimmerUneColonne (grille,CPosition {i,pos.second},1);
}

bool testSurLaGrille::auMoinsTroisDansLaColonne (const manipulationDeLaGrille::CMatrice & grille, manipulationDeLaGrille::CPosition & pos, unsigned & combien)
{
    bool siCEstAlignee (false);
    combien = 1;
    for (size_t j (0);j < size(grille);++j) //On itère les indices des colonnes
    {
        for (size_t i (0);i < size(grille)-1 && !siCEstAlignee;++i)
        {
            /*
            On parcours la colonne en itérant l'indice de la ligne
            et on arrête lorsque le boolen est vrai ou on finit le parcours
            */
            if (grille[i][j] != KImpossible && grille[i][j] == grille[i+1][j])
            {
                /*
                On vérifie que la valeur elle ne soit pas
                vide ensuite on regarde si la valeur suivante est la même
                */
                while ((i < size(grille)-1) &&  grille[i][j]==grille[i+1][j])
                {
                    /*
                    on compte il y  a combien de bonbons d'affilées et on sort lorsqu'on dépasse
                    ou la valeur suivante n'est plus la même
                     */
                    ++combien;
                    ++i;
                }
                if (combien >= 3)
                {
                    /*
                    s'il y a plus de 3 bonbons d'affilées après le parcours d'un colonne on met
                    le booleen à vrai,on enregistre la position de la ligne
                    */
                    siCEstAlignee = true;
                    pos.second = i-combien+1;
                }
                else combien =1;
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

bool testSurLaGrille::auMoinsTroisDansLaLigne (const manipulationDeLaGrille::CMatrice & grille, manipulationDeLaGrille::CPosition & pos, unsigned & combien)
{
    bool siCEstAlignee (false);
    combien = 1;
    for (size_t i (0);i < size(grille);++i) //On itère les indices des lignes
    {
        for (size_t j(0);j < size(grille)-1 && !siCEstAlignee;++j)
        {
            /*
            On parcours la ligne en itérant l'indice de la colonne
            et on arrête lorsque le boolen est vrai ou on finit le parcours
            */
            if (grille[i][j] != KImpossible && grille[i][j] == grille[i][j+1])
            {
                /*
                On vérifie que la valeur elle ne soit pas
                vide ensuite on regarde si la valeur suivante est la même
                */
                while ((j < size(grille)-1) &&  grille[i][j]==grille[i][j+1])
                {
                    /*
                    on compte il y  a combien de bonbons d'affilées et on sort lorsqu'on dépasse
                    ou la valeur suivante n'est plus la même
                     */
                    ++combien;
                    ++j;
                }
                if (combien >= 3)
                {
                    /*
                    s'il y a plus de 3 bonbons d'affilées après le parcours d'une ligne on met
                    le booleen à vrai,on enregistre la position de la colonne
                    */
                    siCEstAlignee = true;
                    pos.first = j-combien+1;
                }
                else combien =1;
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
