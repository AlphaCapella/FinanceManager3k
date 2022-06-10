#pragma once

// Class for all transaction operations
class Transaction {
public:
	// Function to read the user input and call WriteData() to pass input as arguments
	void ReadData();
	// Writes and format the data into a database-file
	void WriteData(std::string&, double&);
	

private:
	std::string Ausgabe;
	double Preis{ 0.0 };
	
	std::string Expense;
	double Price{ 0.0 };
	std::string ExpenseCategory;
	std::string EntryMadeTimestamp;
};
