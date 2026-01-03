#include "../headers/mode-histoire.h"
#include "../headers/utilitaires.h"

const unsigned K2Impossible (999);
const unsigned K2NbDeBonbons (4);

int modeHistoire::lancer ()
{
    parametresDeLaPartie partie;
    unsigned choix;
    char direction;
    unsigned nbDeTours (0);
    unsigned scoreActuelle (0);
    unsigned combien (1);
    manipulationDeLaGrille::CPosition position {0,0};
    manipulationDeLaGrille::CMatrice matrice;
    std::cout << "veuillez saisir votre niveau : ";
    std::cin >> choix;
    choix = choix-1;
    gestionHistoire::selecteurDeNiveaux(choix,partie);
    manipulationDeLaGrille::InitiationGrille(matrice,partie.taille);
    manipulationDeLaGrille::afficherLaGrille(matrice);
    gestionHistoire::dynamiqueDuJeu(matrice,position,combien,scoreActuelle);
    ansiEscapeAffichage::nettoyerLEcran();
    scoreActuelle = 0;
    do
    {
        std::string chaine;
        manipulationDeLaGrille::afficherLaGrille(matrice);
        gestionHistoire::lectureFichier("../data/regles_du_mode_histoire.txt");
        gestionHistoire::lectureFichier("../data/lore.txt",choix);
        std::cout << "voici votre score actuel : " << scoreActuelle << std::endl;
        std::cout << "voici vos nombres de tours restants : " << partie.nombreDeTours-nbDeTours << std::endl;
        std::cout << "veuillez mettre une direction valide : " << std::flush;
        std::cin >> direction;
        if (tolower(direction) == 'x') break;
        std::cout << "veuillez mettre une position pour la ligne : "<< std::flush;
        std::cin >> chaine;
        position.second=std::stoul(chaine);
        std::cout << "veuillez mettre une position pour la colonne : "<< std::flush;
        std::cin >> chaine;
        position.first=std::stoul(chaine);
        manipulationDeLaGrille::faireUnMouvement(matrice,position,direction);
        if (! (testSurLaGrille::auMoinsTroisDansLaColonne(matrice,position,combien) || testSurLaGrille::auMoinsTroisDansLaLigne(matrice,position,combien)))
        {
            manipulationDeLaGrille::faireUnMouvement(matrice,position,direction);
        }
        else
        {
            gestionHistoire::dynamiqueDuJeu(matrice,position,combien,scoreActuelle);
            ++nbDeTours;
        }
    }
    while(nbDeTours != partie.nombreDeTours);
    if ( scoreActuelle< partie.score) std::cout << "vous avez perdu !" << std::endl;
    return 0;
}
