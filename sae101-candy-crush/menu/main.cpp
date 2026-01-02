/*
 * MODE 1VS1
 * commandes :
 *      Joueur 1 : ‘A’ (gauche), ‘Z’ (haut), ‘E’ (droite), ‘S’ (bas)
 *      Joueur 2 : ‘I’ (gauche), ‘O’ (haut), ‘P’ (droite), ‘L’ (bas)
*/

#include <iostream>
#include <vector>

using namespace std;

typedef vector <unsigned> CVLine; // un type représentant une ligne de la grille
typedef vector <CVLine> CMat; // un type représentant la grille
typedef pair <unsigned, unsigned> CPosition; // une position dans la girlle

// constantes de couleurs d'affichage du terminal
const unsigned KReset   (0);
const unsigned KNoir    (30);
const unsigned KRouge   (31);
const unsigned KVert    (32);
const unsigned KJaune   (33);
const unsigned KBleu    (34);
const unsigned KMAgenta (35);
const unsigned KCyan    (36);

// change la couleur du terminal
void changerCouleur (const unsigned & couleur) {
    cout << "\033[" << couleur <<"m";
}

// efface/réinitialise le terminal
void effacerEcran () {
    cout << "\033[H\033[2J";
}

void retouralaligne(unsigned n) {
    for(unsigned i (0); i < n; ++i)
        cout << "\n";
    cout << flush;
}

string & centrer (string & chaine, const unsigned long n){
    unsigned ancienneTaille = size(chaine);
    unsigned posDeb = (n-ancienneTaille)/2;
    chaine.resize(n);
    for(unsigned i (ancienneTaille); i-- > 0;) chaine[posDeb+i-1] = chaine[i];
    for(unsigned i (0); i < posDeb-1; ++i) chaine[i] = ' ';
    for(unsigned i (posDeb+ancienneTaille); i < size(chaine)-1; ++i) chaine[i] = ' ';
    return chaine;
}

string & alignement (string & chaine, const unsigned n){
    while(chaine[0] == ' '){
        for(unsigned i (1); i <= size(chaine)-1; ++i) chaine[i-1] = chaine[i];
        chaine.resize(size(chaine)-1);
    }
    unsigned ancienneTaille = size(chaine);
    chaine.resize(n + ancienneTaille);
    for(unsigned i (ancienneTaille); i-- > 0;) chaine[i+n-1] = chaine[i];
    for(unsigned i (0); i < n-1; ++i) chaine[i] = ' ';
    return chaine;
}

int main () {
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
        {"4: Mode bombe"}
    };
    unsigned choix;

    retouralaligne(3);
    for(string & ligne : logo) {
        cout << centrer(ligne, 80)<< endl;
    }
    retouralaligne(3);
    for(string & ligne : modes) {
        cout << alignement(ligne, 30)<< endl;
    }
    retouralaligne(3);

    cout << "> " << flush;
    cin >> choix;

    switch(choix) {
    case 1:
        // Lancement du mode histoire
        cout << "Lancement du mode histoire" << endl;
        break;
    case 2:
        // Lancement du mode infini
        cout << "Lancement du mode infini" << endl;
        break;
    case 3:
        // Lancement du mode 1 VS 1
        cout << "Lancement du mode 1 VS 1" << endl;
        break;
    case 4:
        // Lancement du mode bombe
        cout << "Lancement du mode bombe" << endl;
        break;
    default:
        cout << "Aucun mode ne correpond à ce numéro" << endl;
        break;
    }

    return 0;
}
