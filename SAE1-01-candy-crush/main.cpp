#include "headers/mode-1vs1.h"
#include "headers/mode-festival.h"
#include "headers/mode-histoire.h"
#include "headers/mode-infini.h"
#include <iostream>
#include <vector>

using namespace std;

typedef vector <unsigned> CVLine; // un type représentant une ligne de la grille
typedef vector <CVLine> CMat; // un type représentant la grille
typedef pair <unsigned, unsigned> CPosition; // une position dans la girlle

// constantes de couleurs d'affichage du terminal
// const unsigned KReset   (0);
// const unsigned KNoir    (30);
// const unsigned KRouge   (31);
// const unsigned KVert    (32);
// const unsigned KJaune   (33);
// const unsigned KBleu    (34);
// const unsigned KMAgenta (35);
// const unsigned KCyan    (36);

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
    unsigned choix;

    affichage::retouralaligne(3);
    for(string & ligne : logo) {
        cout << affichage::centrer(ligne, 80)<< endl;
    }
    affichage::retouralaligne(3);
    for(string & ligne : modes) {
        cout << affichage::alignement(ligne, 30)<< endl;
    }
    affichage::retouralaligne(3);

    cout << "> " << flush;
    cin >> choix;

    switch(choix) {
    case 1:
        modeHistoire::lancer();
        break;
    case 2:
        modeInfini::lancer();
        break;
    case 3:
        mode1vs1::lancer();
        break;
    case 4:
        modeFestival::lancer();
        break;
    default:
        cout << "Aucun mode ne correpond à ce numéro" << endl;
        break;
    }

    return 0;
}
