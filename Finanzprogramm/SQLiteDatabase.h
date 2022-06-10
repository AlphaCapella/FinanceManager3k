#pragma once
#include <iostream>
#include "sqlite3.h"

class SQLiteDatabase {
private:
	// String variables for the Databases
	const std::string DBName = "FinanzDB.db";

public:
	// DONE 
	void OpenDB(const std::string&);
	void CloseDB();
	void CreateTable();


	void InsertData(std::string& Expense, double& Price, std::string& Category, std::string& DateTimeEntryMade);
	void ShowData();
	static int callback(void* NotUsed, int argc, char** argv, char** azColName);
	void DeleteCategoryData(std::string& DelCategory);
	void DeleteExpenseData(std::string& DelExpense);
	void DeleteID_NumData(int& DelID_Num);
	void DeleteAllData();


	// TO DO
	void SelectCategory();
	void SelectExpense();
	void FormatDataToTable();
	
	
	

private:
	// Pointer to the SQLite connection
	sqlite3* DB;
	// Holds the string with the SQL-command for table creation
	std::string SQLCreateTableTRANSACTION;
	// SQL command for showing whole table
	std::string SHOWTABLE = "select * from MONEYSPEND;";


	// Hold the error returned by table creation
	char* pErrMsg = nullptr;

	// Compiled SQLite Statement
	sqlite3_stmt* stmt;
	// Save the results of opening a file
	int SuccessFileOpen;
	// Save the results of preparing a sql-statement
	int SuccessPrepare;

	
	std::string SQLDelCategory;
	std::string SQLDelExpense;
	std::string SQLDelID_Num;
	std::string SQLDellAll;

	std::string SQLSelCategory;
	std::string SQLSelExp;

};
