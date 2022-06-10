#include <iostream>
#include <string>
#include <fstream>
#include "transaction.h"
#include "date.h"
#include "SQLiteDatabase.h"


using namespace std;

// Function for reading and storing input of the user into a file
void Transaction::ReadData() {
    //// Get the input from the User for the item bought and the price
    //// Store information in two variables (Ausgabe, Preis)

    //// Getting the item name
    //cout << "Name of Expense: ";
    //// cin.ignore() to ignore the automatically inserted whitespace
    //cin.ignore();
    //getline(cin, Ausgabe);

    //// Getting the item price
    //cout << "Price: ";
    //cin >> Preis;


    // NEW
    cout << "Name of Expense: ";
    std::cin.ignore();
    std::getline(cin, Expense);

    cout << "Price: ";
    //std::cin.ignore();
    std::cin >> Price;

    cout << "Category of Expense: ";
    std::cin.ignore();
    std::getline(cin, ExpenseCategory);

    EntryMadeTimestamp = date::format("%A, %F %R", std::chrono::system_clock::now());

    SQLiteDatabase DBEntry;
    DBEntry.InsertData(Expense, Price, ExpenseCategory, EntryMadeTimestamp);


    //// Now call the WriteData function to write the data into the database-file (Here a .txt)
    //Transaction::WriteData(Ausgabe, Preis);
}

//// Stores Data (Ausgabe, Preis) into a .txt file, appending the newest entry to the bottom of the file
//// Pass-by-reference Ausgabe and Price
//void Transaction::WriteData(std::string& Ausgabe, double& Preis) {
//
//    // The NewEntryIndexNumber is calculated by counting all the lines in the database, dividing through the BlockSize and adding 1
//    // BlockSize is the amount of lines per entry-block; NumberOfLines is the amount of lines in the document
//    int BlockSize{ 6 };
//    std::size_t NumberOfLines{ 0 };
//    // Create ifstream object, count the NumberOfLines and calculate NewEntryIndexNumber. Also close ifstream object 
//    std::ifstream DBfile;
//    DBfile.open("Datenbank.txt");
//    NumberOfLines = std::count(std::istreambuf_iterator<char>(DBfile), std::istreambuf_iterator<char>(), '\n');
//    int NewEntryIndexNumber = NumberOfLines / BlockSize + 1;
//    DBfile.close();
//
//    // Create ofstream object
//    ofstream db;
//    // Open the object with the mode ios::app ("All output operations are performed at the end of the file, appending the content to the current content of the file.")
//    db.open("Datenbank.txt", ios::app);
//
//    // Hold the current time and date in a string (from date.h library)
//    // The format is: Weekday, YYYY-MM-DD HH:MM
//    std::string CurrTimeDate = date::format("%A, %F %R", std::chrono::system_clock::now());
//
//    // Create frame to distinguish each entry (---) and print the NewEntryIndexNumber, name, price and CurrTimeDate
//    db << "------------------------------------------------------\n";
//    db << "Entry Number: " << NewEntryIndexNumber << endl;
//    db << "Ausgabe: " << Ausgabe << endl;
//    db << "Preis: " << Preis << endl;
//    db << "Entry made: " << CurrTimeDate << endl;
//    db << "------------------------------------------------------\n";
//}
