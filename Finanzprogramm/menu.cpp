#include <iostream>
#include "menu.h"

using namespace std;

// Welcome message. Printed at programm start up
void Menu::Welcome() {
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "+                                                +" << endl;
    cout << "+          Willkommen im Finanzboi 3k :)         +" << endl;
    cout << "+                                                +" << endl;
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
}

int Menu::MainMenu() {
    // Ask user what he wants to do
    cout << "Main Menu - Choose your option" << endl;
    cout << "1. Enter new transaction" << endl;
    cout << "2. Show entries in database" << endl;
    cout << "0. Quit" << endl;
    cout << "Selection: ";
    int ChosenOption{ 1 };
    cin >> ChosenOption;
    return ChosenOption;

}


