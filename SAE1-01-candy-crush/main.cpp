/**
 * @file main.cpp
*/

#include "headers/mode-1vs1.h"
#include "headers/mode-festival.h"
#include "headers/mode-histoire.h"
#include "headers/mode-infini.h"
#include <iostream>
#include <vector>

using namespace std;

/**
 * @mainpage
 * Bienvenue dans la documentation de notre projet pour la SAE de R101
 * réalisée par le groupe de BARTHÉLÉMY Gaël, LI Tommy, SEFFAH Marwane et ZEA BAEZ Brandon.
 * N'hésitez pas à naviguer dans la documentation avec la barre de navigation plus haut !
*/

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

int main () {
    srand(time(nullptr));
    vector <string> logo = {
        {" _____________________________________ "},
        {"|   ___    __    __  _  ____  __  __  |"},
        {"|  / __|  /  \\  |  \\| ||  _ \\ \\ \\/ /  |"},
        {"| | (__  / __ \\ | \\ \\ || |_| | \\  /   |"},
        {"|  \\___|/_/  \\_\\|_|\\__||____/  /_/    |"},
        {"|   ___   ___   _   _   ___   _   _   |"},
        {"|  / __| | _ \\ | | | | / __| | |_| |  |"},
        {"| | (__  |   / | |_| | \\__ \\ |  _  |  |"},
        {"|  \\___| |_|_\\  \\___/  |___/ |_| |_|  |"},
        {"|_____________________________________|"}
    };
    vector <string> modes = {
        {"1: Mode histoire"},
        {"2: Mode infini"},
        {"3: Mode 1 VS 1"},
        {"4: Mode festival"}
    };
    char choix;

    affichage::retouralaligne(3);
    for(string & ligne : logo) {
        cout << affichage::centrer(ligne, 80)<< endl;
    }
    affichage::retouralaligne(3);
    for(string & ligne : modes) {
        cout << affichage::alignement(ligne, 30)<< endl;
    }
    affichage::retouralaligne(3);

    while(true) {
        cout << "> " << flush;
        cin >> choix;

        switch(choix) {
        case '1':
            modeHistoire::lancer();
            break;
        case '2':
            modeInfini::lancer();
            break;
        case '3':
            mode1vs1::lancer();
            break;
        case '4':
            modeFestival::lancer();
            break;
        default:
            cout << "Aucun mode ne correpond à ce numéro" << endl;
            break;
        }
        affichage::retouralaligne(3);
        cout << "Retour au menu" << endl;
        affichage::retouralaligne(3);
    }
    return 0;
}
