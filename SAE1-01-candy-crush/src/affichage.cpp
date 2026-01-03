#include "../headers/affichage.h"
#include <fstream>

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

void ansiEscapeAffichage::couleur (const unsigned & coul)
{
    std::cout << "\033[" << coul <<"m"; //On change de couleur avec coul le code couleur
}

void ansiEscapeAffichage::nettoyerLEcran () {
    std::cout << "\033[H\033[2J"; //on dit au terminal CTRL+L
    //Remplacer 2J par 3J c mieux
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

std::vector <unsigned> & manipulationDeVecteur::suppressionDElement (std::vector <unsigned> & VTemporaire, const std::size_t & positionDuDebut)
{
    //l'élément qui se trouve dans cette position est supprimé du vector
    for(std::size_t i (positionDuDebut);i < VTemporaire.size()-1;++i) VTemporaire[i]=VTemporaire[i+1];
    VTemporaire.resize(VTemporaire.size()-1);
    return VTemporaire;
}
std::vector <unsigned> & manipulationDeVecteur::insertionDElement (std::vector <unsigned> & VTemporaire,const std::size_t pos, const unsigned val)
{
    //On insère un élement à une certaine position
    VTemporaire.resize(VTemporaire.size()+1);
    for (std::size_t i = VTemporaire.size()-1; pos < i; --i) VTemporaire[i]=VTemporaire[i-1];
    VTemporaire[pos]=val;
    return VTemporaire;
}

std::vector <unsigned> & manipulationDeVecteur::deplacerUnElement (std::vector <unsigned> & VTemporaire, const std::size_t & positionDuDebut, const std::size_t & positionDeFin)
{
    //On combine les fonctions suppressionDElement et Insertion pour déplacer un élement
    //on met les valeurs à KImpossible
    unsigned val = VTemporaire[positionDuDebut];
    manipulationDeVecteur::suppressionDElement(VTemporaire,positionDuDebut);
    manipulationDeVecteur::insertionDElement(VTemporaire,positionDeFin,val);
    return VTemporaire;
}

void manipulationDeLaGrille::InitiationGrille (CMatrice & grille, std::size_t taille)
{
    grille.resize(taille, CVLigne (taille));
    for (CVLigne & ligne : grille)
    {
        for (unsigned & cas : ligne) cas = rand()%(KNbDeBonbons)+1; // on choisit un nb random entre [1,nbCandies]
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
                std::cout << std::setw(3) << cellule;// on espace de 2 et le 3eme charactere est la case
            }
            else
            {
                ansiEscapeAffichage::couleur(KReset);
                std::cout << std::setw(3) << ' '; //si ça correspond pas on a une case vide
            }
        }
        std::cout << std::endl; // saut de ligne à chaque ligne de la matrice
    }
    ansiEscapeAffichage::couleur(KReset); // on remet la couleur à la normale
}

void manipulationDeLaGrille::faireUnMouvement (CMatrice & grille,const CPosition & pos,char direction)
{
    if ( ((pos.first < grille.size()-1)) && ((pos.second < grille.size()-1)))
    {
        switch (tolower(direction)) //On interprete les char Maj
        {
        case 'z' :
            if (pos.second > 0 ) //On évite la ligne qui est tt en haut
            {
                std::swap(grille[pos.second][pos.first],grille[pos.second-1][pos.first]); //On permute la case en haut
                break;
            }
            else break;
        case 's' :
            if (pos.second < grille.size()-1) //On évite la ligne qui est tt en bas
            {
                std::swap(grille[pos.second][pos.first],grille[pos.second+1][pos.first]); //On permute la case en bas
                break;
            }
            else break;
        case 'a' :
            if (pos.first > 0) //On évite la colonne qui est tt à gauche
            {
                std::swap(grille[pos.second][pos.first],grille[pos.second][pos.first-1]); //On permute la case à gauche
                break;
            }
            else break;
        case 'e' :
            if (pos.first < grille.size()-1) //On évite la colonne qui est tt à droite
            {
                std::swap(grille[pos.second][pos.first],grille[pos.second][pos.first+1]); //On permute la case à droite
                break;
            }
            else break;
        default :
            std::cout << "appuyer sur une touche valide" << std::endl;
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
    std::vector <unsigned> VTemporaire;
    VTemporaire.resize(grille.size());
    for (std::size_t i (0); i < grille.size() ;++i) VTemporaire[i] = grille[i][pos.first];
    for (std::size_t i (pos.second); i < pos.second+combien ;++i) manipulationDeVecteur::insertionDElement(manipulationDeVecteur::suppressionDElement(VTemporaire,i),0,KImpossible);
    for (std::size_t i (0); i < grille.size() ;++i) grille[i][pos.first] = VTemporaire[i];
}

void manipulationDeLaGrille::supprimmerUneLigne (CMatrice & grille, const CPosition & pos, unsigned  combien)
{
    /*
    On supprimme une ligne en supprimmant en supprimmant une valeur dde chaque colonne le nombre de fois ou le motif se répète
    */
    for (std::size_t i (pos.first); i < pos.first+combien; ++i) manipulationDeLaGrille::supprimmerUneColonne (grille,CPosition {i,pos.second},1);
}

bool testSurLaGrille::auMoinsTroisDansLaColonne (const manipulationDeLaGrille::CMatrice & grille, manipulationDeLaGrille::CPosition & pos, unsigned & combien)
{
    bool siCEstAlignee (false);
    combien = 1;
    for (std::size_t j (0);j < size(grille);++j) //On itère les indices des colonnes
    {
        for (std::size_t i (0);i < size(grille)-1 && !siCEstAlignee;++i)
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
    for (std::size_t i (0);i < size(grille);++i) //On itère les indices des lignes
    {
        for (std::size_t j(0);j < size(grille)-1 && !siCEstAlignee;++j)
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

void gestionHistoire::dynamiqueDuJeu (manipulationDeLaGrille::CMatrice & matrice, manipulationDeLaGrille::CPosition p, unsigned h, unsigned & cpt)
{
    while(testSurLaGrille::auMoinsTroisDansLaLigne(matrice,p,h))
    {
        manipulationDeLaGrille::supprimmerUneLigne (matrice,p,h);
        cpt = cpt +100;
        manipulationDeLaGrille::afficherLaGrille(matrice);
        gestionHistoire::rajoutDesBonbons(matrice);
    }
    while(testSurLaGrille::auMoinsTroisDansLaColonne(matrice,p,h))
    {
        manipulationDeLaGrille::supprimmerUneColonne (matrice,p,h);
        cpt = cpt +100;
        manipulationDeLaGrille::afficherLaGrille(matrice);
        gestionHistoire::rajoutDesBonbons(matrice);
    }
}
void gestionHistoire::rajoutDesBonbons(manipulationDeLaGrille::CMatrice & grille)
{
    for(manipulationDeLaGrille::CVLigne & ligne : grille)
    {
        for(unsigned & cas : ligne)
        {
            if (cas == KImpossible) cas = rand()%(KNbDeBonbons)+1;
        }
    }
}
void gestionHistoire::lectureFichier(const std::string & cheminDuFichier, const size_t i)
{
    std::ifstream ifs;
    ifs.open(cheminDuFichier);
    for (size_t j (0);j!=i && !ifs.eof();++j)
    {
        for(std::string chaine;!ifs.eof();)
        {
            std::getline(ifs,chaine);
            if(chaine=="####") break;
        }
    }
    for(std::string chaine;!ifs.eof();)
    {
        std::getline(ifs,chaine);
        if(chaine=="####") break;
        std::cout << chaine << std::endl;
    }
    ifs.close();
}
void gestionHistoire::selecteurDeNiveaux(const unsigned & niveau,parametresDeLaPartie & partie)
{
    std::ifstream ifs;
    ifs.open("../data/niveaux.txt");
    for (size_t j (0);j!=niveau && !ifs.eof();++j)
    {
        for(std::string chaine;!ifs.eof();)
        {
            std::getline(ifs,chaine);
            if(chaine=="####") break;
        }
    }
    ifs.clear();
    std::string chaine;
    std::getline(ifs,chaine);
    std::getline(ifs,chaine);
    partie.taille= std::stoul(gestionHistoire::lectureDeChiffresDansUneChaine (chaine));
    std::getline(ifs,chaine);
    partie.nombreDeTours= std::stoul(gestionHistoire::lectureDeChiffresDansUneChaine(chaine));
    std::getline(ifs,chaine);
    partie.score= std::stoul(gestionHistoire::lectureDeChiffresDansUneChaine (chaine));
    ifs.close();
}
std::string gestionHistoire::lectureDeChiffresDansUneChaine(const std::string & chaine)
{
    std::string numeros;
    for (const char & c : chaine )
    {
        if (isdigit(c)) numeros = numeros + c;
    }
    return numeros;
}
void gestionHistoire::melangeDesBonbons(manipulationDeLaGrille::CMatrice & grille)
{
    for(size_t ligne (0) ; ligne < grille.size(); ++ligne)
    {
        for(size_t colonne (0) ; colonne < grille.size(); ++colonne) grille[ligne][colonne] = grille[rand()%(grille.size())][rand()%(grille.size())];
    }
}
