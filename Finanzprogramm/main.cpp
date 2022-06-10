// Including Libraries
#include <iostream>
#include <string>
#include "menu.h"
#include "transaction.h"
#include "SQLiteDatabase.h"
#include "date.h"
#include "sqlite3.h"

// The variables for the Databases can be found in "SQLiteDatabase.h"

// Using the namespaces
using namespace std;


// Initializing main function
int main() {
    // Make sure DB with the correct table exists, if not create it
    SQLiteDatabase DBCheckStartUp;  
    DBCheckStartUp.CreateTable();

    // Create Menu class-object and int to quit the programm
    Menu messages;
    int Selection{ 1 };
    Transaction transaktion;

    // Print welcome messages to the user after first starting the programm. 
    messages.Welcome();

    // If the selection is != 0, start the while loop for the main programm. Otherwise the programm terminates and we do not need to start the while loop
    while (Selection != 0)
    {
        // Ask user what he wants to do
        Selection = messages.MainMenu();

        // Based on the user selection, start the appropriate menu

        //Eingabe - Because Selection is set to 1
        if (Selection == 1) {

            // Create variable for the while loop. As long as it is != 0, continue the loop
            int iEingabe{ 1 };
            string ContinueEntry;

            // Beginning of while-loop for continues input of transactions
            while (iEingabe != 0) {

                // Request a new transaction from the user
                cout << "Bitte gebe eine neue Transaktion ein" << endl;
                // Read and format the data with the ReadData() memberfunction of "transaction.h"
                transaktion.ReadData();

                // Ask the user if he wants to continue, accept only 'y' or 'n' as input, else start new while-loop to get correct input
                cout << "Continue? y/n" << endl;
                // cin.ignore() to ignore the automatically inserted whitespace
                cin.ignore();
                getline(cin, ContinueEntry);

                // Check for continueing input
                if (ContinueEntry == "y") {
                    break;
                }
                // Check for stopping input
                else if (ContinueEntry == "n") {
                    iEingabe = 0;
                    break;
                }
                // Every other input, starts new loop to get correct input of 'y' or 'n'
                else {
                    while (ContinueEntry != "y" && ContinueEntry != "n") {
                        cout << "Input is not valid. Please insert 'y' or 'n'" << endl;
                        getline(cin, ContinueEntry);
                        if (ContinueEntry == "n") {
                            iEingabe = 0;
                            break;
                        }
                    }
                }
                
                    

            }
            continue;
        }

        //Anzeige
        else if (Selection == 2) {
            // DO ANEZIGE
            cout << "Here is the data in the DB:" << endl;
            DBCheckStartUp.ShowData();
            continue;
        }

        else if (Selection == 3) {
            // DO ANEZIGE
            std::string DelCategory;
            cout << "Delete category: " << std::endl;
            std::cin.ignore();
            std::getline(cin, DelCategory);
            DBCheckStartUp.DeleteCategoryData(DelCategory);
            continue;
        }
        else if (Selection == 4) {
            // DO ANEZIGE
            std::string DelExpense;
            cout << "Delete Expense: " << std::endl;
            std::cin.ignore();
            std::getline(cin, DelExpense);
            DBCheckStartUp.DeleteExpenseData(DelExpense);
            continue;
        }
        else if (Selection == 5) {
            // DO ANEZIGE
            int DelID_Num;
            cout << "Delete ID_Num: " << std::endl;
            cin >> DelID_Num;
            DBCheckStartUp.DeleteID_NumData(DelID_Num);
            continue;
        }
        else if (Selection == 6) {
            // DO ANEZIGE
            int DelID_Num;
            cout << "Delete All Data: " << std::endl;

            DBCheckStartUp.DeleteAllData();
            continue;
        }

        //Quit
        else if (Selection == 0) {
            // DO QUIT
            cout << "Okay Ciao bro" << endl;

            break;
        }

        // Every other input 
        else {
            cout << "Bro, sowas haben wir nicht im Menue" << endl;
            continue;
        }

    }
    
    return 0;

}