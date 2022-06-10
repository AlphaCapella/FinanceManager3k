#include <iostream>
#include <string>
#include <fstream>
#include "sqlite3.h"
#include "SQLiteDatabase.h"




// All functions assume that OpenDB(std::string&) has been called before using any of the member functions of SQLiteDatabase. Use it in the 
// programm begin or before attempting to use any function
// If SQLite is not further needed, close the connection to the Db by calling CloseDB()

// Function to open the DB-connection, if DB does not exist, it will be created with the DB-Name passed as string from main()
// If opening/creating fails, print error message. Otherwise print success of opening/creating the connection
// Using the private member-pointer "DB" to access the DB-connection
void SQLiteDatabase::OpenDB(const std::string& DBName) {
	if (sqlite3_open(DBName.c_str(), &DB) != 0) {
		std::cerr << "Database connection could not be opened. Error: " << sqlite3_errmsg(DB) << std::endl;
	}
	else {
		std::cout << "Database opened" << std::endl;
	}
}

// Function to close the DB-connection
// If closing fails, print error message. Otherwise print success of closing the connection
// Using the private member-pointer "DB" to access the DB-connection
void SQLiteDatabase::CloseDB() {
	if (sqlite3_close(DB) != 0) {
		std::cerr << "Database connection could not be close. Error: " << sqlite3_errmsg(DB) << std::endl;
	}
	else {
		std::cout << "Database connection closed" << std::endl;
	}
}

// Create table for data entry and check if tables already exists
void SQLiteDatabase::CreateTable() {
	//// Open DB Connection
	SQLiteDatabase::OpenDB(DBName);

	SQLCreateTableTRANSACTION = "CREATE TABLE IF NOT EXISTS MONEYSPEND("
								"ID_Num INTEGER PRIMARY KEY, "
								"Expense VARCHAR(255) NOT NULL, "
								"Price DOUBLE NOT NULL, "
								"Category VARCHAR(255), "
								"EntryMade DATETIME);";


	if (sqlite3_exec(DB, SQLCreateTableTRANSACTION.c_str(), NULL, 0, &pErrMsg) != SQLITE_OK) {
		std::cerr << "Error creating table: " << pErrMsg << std::endl;
		// Free the memory to avoid leaks
		sqlite3_free(pErrMsg);
	}
	else {
		std::cout << "Table created succesfully" << std::endl;
	}

	//// Close DB Connection
	SQLiteDatabase::CloseDB();
}


void SQLiteDatabase::InsertData(std::string& Expense, double& Price, std::string& Category, std::string& DateTimeEntryMade) {
	//// Open DB Connection
	SQLiteDatabase::OpenDB(DBName);

	// Create SQL String -- Put this into seperate function later on
	std::string SQLInsertData = "INSERT INTO MONEYSPEND (ID_Num, Expense, Price, Category, EntryMade) VALUES (NULL,'" + Expense + "','" + std::to_string(Price) + "','" + Category + "','" + DateTimeEntryMade + "');";
	std::cout << SQLInsertData << std::endl;
	// Prepare SQL Statement for execution and save result in int SuccessPrepare
	SuccessPrepare = sqlite3_prepare_v2(DB, SQLInsertData.c_str(), SQLInsertData.size(), &stmt, NULL);
	// Run step to execute SQL Statement and finalize (destroy object after execution) either way, to avoid memory leaks
	if (sqlite3_step(stmt) != SQLITE_DONE) {
		std::cout << "Didn't Insert Item! Error:" << sqlite3_step(stmt) << std::endl;
		sqlite3_finalize(stmt);
	}
	else {
		std::cout << "Entry made." << std::endl;
		sqlite3_finalize(stmt);
	}

	//// Close DB Connection
	SQLiteDatabase::CloseDB();
}


void SQLiteDatabase::ShowData() {
	//// Open DB Connection
	SQLiteDatabase::OpenDB(DBName);

	SuccessFileOpen = sqlite3_exec(DB, SHOWTABLE.c_str(), callback, 0, &pErrMsg);

	//// Close DB Connection
	SQLiteDatabase::CloseDB();
}


int SQLiteDatabase::callback(void* NotUsed, int argc, char** argv, char** azColName) {
	int i;
	for (i = 0; i < argc; i++) {
		std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
	}
	std::cout << std::endl;
	return 0;
}


void SQLiteDatabase::DeleteCategoryData(std::string& DelCategory) {
	//// Open DB Connection
	SQLiteDatabase::OpenDB(DBName);

	SQLDelCategory = "DELETE FROM MONEYSPEND WHERE Category= \"" + DelCategory + "\";";
	std::cout << SQLDelCategory << std::endl;
	sqlite3_prepare_v2(DB, SQLDelCategory.c_str(), SQLDelCategory.size(), &stmt, NULL);

	if (sqlite3_step(stmt) != SQLITE_DONE) {
		std::cout << "Didn't delete Item(s)! Error:" << sqlite3_step(stmt) << std::endl;
		sqlite3_finalize(stmt);
	}
	else {
		std::cout << "Item(s) deleted." << std::endl;
		sqlite3_finalize(stmt);
	}

	//// Close DB Connection
	SQLiteDatabase::CloseDB();
}

void SQLiteDatabase::DeleteExpenseData(std::string& DelExpense) {
	//// Open DB Connection
	SQLiteDatabase::OpenDB(DBName);

	SQLDelExpense = "DELETE FROM MONEYSPEND WHERE Expense= \"" + DelExpense + "\";";
	std::cout << SQLDelExpense << std::endl;
	sqlite3_prepare_v2(DB, SQLDelExpense.c_str(), SQLDelExpense.size(), &stmt, NULL);

	if (sqlite3_step(stmt) != SQLITE_DONE) {
		std::cout << "Didn't delete Item(s)! Error:" << sqlite3_step(stmt) << std::endl;
		sqlite3_finalize(stmt);
	}
	else {
		std::cout << "Item(s) deleted." << std::endl;
		sqlite3_finalize(stmt);
	}

	//// Close DB Connection
	SQLiteDatabase::CloseDB();
}

void SQLiteDatabase::DeleteID_NumData(int& DelID_Num) {
	//// Open DB Connection
	SQLiteDatabase::OpenDB(DBName);

	SQLDelID_Num = "DELETE FROM MONEYSPEND WHERE ID_Num= \"" + std::to_string(DelID_Num) + "\";";
	std::cout << SQLDelID_Num << std::endl;
	sqlite3_prepare_v2(DB, SQLDelID_Num.c_str(), SQLDelID_Num.size(), &stmt, NULL);

	if (sqlite3_step(stmt) != SQLITE_DONE) {
		std::cout << "Didn't delete Item(s)! Error:" << sqlite3_step(stmt) << std::endl;
		sqlite3_finalize(stmt);
	}
	else {
		std::cout << "Item(s) deleted." << std::endl;
		sqlite3_finalize(stmt);
	}

	//// Close DB Connection
	SQLiteDatabase::CloseDB();
}

void SQLiteDatabase::DeleteAllData() {
	//// Open DB Connection
	SQLiteDatabase::OpenDB(DBName);

	SQLDellAll = "DELETE FROM MONEYSPEND;";
	std::cout << SQLDellAll << std::endl;
	sqlite3_prepare_v2(DB, SQLDellAll.c_str(), SQLDellAll.size(), &stmt, NULL);

	if (sqlite3_step(stmt) != SQLITE_DONE) {
		std::cout << "Could not empty database! Error:" << sqlite3_step(stmt) << std::endl;
		sqlite3_finalize(stmt);
	}
	else {
		std::cout << "Database emptied." << std::endl;
		sqlite3_finalize(stmt);
	}

	//// Close DB Connection
	SQLiteDatabase::CloseDB();
}

void SQLiteDatabase::SelectCategory() {

}

