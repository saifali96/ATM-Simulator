#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
using namespace std;				// Set the namespace to std

#include "ATM.h"

#if defined _WIN64 || _WIN32
#define CLEAR "CLS"
#else
#define strcpy_s(a, b, c) strcpy(a, c)
#define CLEAR "clear"
#endif

int main(int argc, char* argv[])
{
	// Print the Welcome Message
	cout << welcome_message;

	bool loggedIn = false;
	/*
	strcpy_s(customers[0].name, strlen("Saif Ali") + 1, "Saif Ali");
	customers[0].accnum = 10000001;
	customers[0].balance = 50001120;
	customers[0].ccn = 4485352309418789;
	customers[0].pin = 1234;

	strcpy_s(customers[1].name, strlen("Asad Waseem") + 1, "Asad Waseem");
	customers[1].accnum = 10000002;
	customers[1].balance = 500000;
	customers[1].ccn = 4034900075688294;
	customers[1].pin = 9874;

	strcpy_s(customers[2].name, strlen("Shahzaib Amanat Ali") + 1, "Shazaib Amanat Ali");
	customers[2].accnum = 10000003;
	customers[2].balance = 612000;
	customers[2].ccn = 372765192713004;
	customers[2].pin = 4567;

	strcpy_s(customers[3].name, strlen("Ameer Ali") + 1, "Ameer Ali");
	customers[3].accnum = 10000004;
	customers[3].balance = 780000;
	customers[3].ccn = 5526268066444305;
	customers[3].pin = 7851;

	strcpy_s(customers[4].name, strlen("Mouaaz Bin Aamer") + 1, "Mouaaz Bin Aamer");
	customers[4].accnum = 10000005;
	customers[4].balance = 502100;
	customers[4].ccn = 371705669021003;
	customers[4].pin = 9211;

	ofstream db;
	string current_user;
	for (int i = 0; i < 5; ++i)
	{
		current_user = to_string((customers[i].accnum));
		db.open((current_user + ".db").c_str());
		db << customers[i].name << endl;
		db << customers[i].accnum << endl;
		db << customers[i].balance << endl;
		db << customers[i].ccn << endl;
		db << customers[i].pin << endl;
		db.close();
	}
	*/

	// Print the Login Screen
	while (!loggedIn)
	{
		loggedIn = Login_Menu();
	}

	while (loggedIn)
	{
		Show_Stats(currentUserLoggedIn);
	}

	return 0;
}


bool Login_Menu()
{
	cout << endl << endl << "Please enter your ATM Card Number: ";
	long long int CCN = 0LL;			// Create a variable for CCN
	short int PIN = 0;					// Create a variable for PIN
	cin >> CCN;							// Store the CCN

										// If the CCN is valid
	if (CCN_VALIDATE(CCN))
	{
		if (CCN_OwnerExists(CCN))		// If the owner exists too
		{
			system("CLS");
			// Print the Welcome Message
			cout << welcome_message;

			cout << endl << "Welcome Back " << CCN_GetOwner(CCN) << "!" << endl;		// Greet the owner
			cout << "Please enter your 4-Digit PIN: ";									// Ask for PIN
			cin >> PIN;																	// Get the PIN
																			
			// Validate the PIN
			if (PIN_Validate(CCN, PIN))
			{
				LoginUser(CCN, PIN);													// Log the owner in
				return true;														
			}
			else
			{
				cout << "User doesn't exist!." << endl;
				return false;
			}
		}
		else
		{
			cout << "User doesn't exist!." << endl;
			return false;
		}
	}

	return false;
}

int CCN_VALIDATE(long long CCN)
{
	int digits = CCNLength(CCN);
	bool pass = CCNCheckLuhn(CCN, digits);

	if (pass)
	{
		return 1;
	}

	return 0;
}

int CCNLength(long long cardNumber)
{
	int digits = 0;

	// Counts how many times the number can be divided until it is less than 1
	while (cardNumber >= 1)
	{
		cardNumber = cardNumber / 10;
		digits++;
	}

	return digits;
}

bool CCNCheckLuhn(long long cardNumber, int digits)
{
	// Calculating step 1 of Luhn's Algorithm
	int sum1 = 0;
	for (int i = 2; i <= digits; i += 2)
	{
		int digit = getDigit(cardNumber, i);

		// For a two digit number, we want make sure to add the sum of the digits
		if (2 * digit < 10)
		{
			sum1 = sum1 + digit * 2;
		}
		else
		{
			sum1 = sum1 + 1 + (2 * digit - 10);
		}
	}

	// Calculating step 2 of Luhn's Algorithm   
	int sum2 = 0;
	for (int i = 1; i <= digits; i += 2)
	{
		int digit = getDigit(cardNumber, i);
		sum2 = sum2 + digit;
	}

	// Verifying that the last digit is 0 using modulo
	return ((sum1 + sum2) % 10) == 0;
}


int getDigit(long long cardNumber, int location)
{
	// Casting to a double so decimal places can be kept. Dec stands for with decimal.
	double cardNumberDec = (double)cardNumber;

	// Keeps dividing by 10 until targeted digit is right behind the decimal point
	for (int i = 0; i < location; i++)
	{
		// Only keeps one number behind the decimal point to prevent double from running out of precision
		cardNumberDec = ((long long)cardNumberDec) / 10.0;
	}

	// No Dec stands for no decimal. 
	double cardNumberNoDec = cardNumberDec;

	// Subtracting to isolate digit we want (Ex: 789.7 - 789 = 0.7)
	double difference = cardNumberDec - cardNumberNoDec;

	// Rounding since computers don't multiply by 10 accurately (especially if there are many digits)
	int digit = (int)round((difference * 10));

	return digit;
}

void LoginUser(long long CCN, short PIN)
{
	currentUserLoggedIn = stol(GetAccNum(CCN));
}


string GetAccNum(long long CCN)
{
	ifstream db;
	string current_user, cur_name, cur_accnum, cur_balance, cur_ccn, cur_pin;
	for (int i = 0; i < 5; ++i)
	{
		current_user = to_string(10000001 + i);
		db.open((current_user + ".db").c_str());
		getline(db, cur_name);
		getline(db, cur_accnum);
		getline(db, cur_balance);
		getline(db, cur_ccn);
		getline(db, cur_pin);
		db.close();

		if (to_string(CCN) == cur_ccn)
		{
			return cur_accnum;
		}
	}
	
	return "Error!";
}


void Show_Stats(long accnum)
{
	ifstream db;
	string cur_name, cur_accnum, cur_balance, cur_ccn, cur_pin;
	db.open((to_string(accnum) + ".db").c_str());
	getline(db, cur_name);
	getline(db, cur_accnum);
	getline(db, cur_balance);
	getline(db, cur_ccn);
	getline(db, cur_pin);
	db.close();

	if (to_string(accnum) == cur_accnum)
	{
		system("CLS");
		// Print the Welcome Message
		cout << welcome_message;

		cout << "Welcome " << cur_name << "!" << endl;
		cout << "Account Number: " << cur_accnum << endl;
		cout << "Account Balance: " << cur_balance << endl;
		cout << "Credit Card Number: " << cur_ccn << endl;
		cout << "PIN: " << cur_pin << endl;
	}

	ATMMenu(accnum);
}

bool CCN_OwnerExists(long long CCN)
{
	ifstream db;
	string current_user, cur_name, cur_accnum, cur_balance, cur_ccn, cur_pin;
	current_user = GetAccNum(CCN);
	db.open((current_user + ".db").c_str());
	getline(db, cur_name);
	getline(db, cur_accnum);
	getline(db, cur_balance);
	getline(db, cur_ccn);
	getline(db, cur_pin);
	db.close();

	if (to_string(CCN) ==  cur_ccn)
	{
		return true;
	}

	return false;
}

bool PIN_Validate(long long CCN, short int PIN)
{
	ifstream db;
	string current_user, cur_name, cur_accnum, cur_balance, cur_ccn, cur_pin;
	current_user = GetAccNum(CCN);
	db.open((current_user + ".db").c_str());
	getline(db, cur_name);
	getline(db, cur_accnum);
	getline(db, cur_balance);
	getline(db, cur_ccn);
	getline(db, cur_pin);
	db.close();

	if (to_string(PIN) == cur_pin)
	{
		return true;
	}

	return false;
}

string CCN_GetOwner(long long CCN)
{
	ifstream db;
	string current_user, cur_name, cur_accnum;
	current_user = GetAccNum(CCN);
	db.open((current_user + ".db").c_str());
	getline(db, cur_name);
	getline(db, cur_accnum);
	db.close();

	if (current_user == cur_accnum)
	{
		return cur_name;
	}

	return "Error!";
}


void ATMMenu(long accnum)
{
	cout << "Please choose your service: " << endl << endl;
	char choice = 0;
	cout << "1.\tWithdraw Cash" << endl;
	cout << "2.\tPay Utility Bills" << endl;
	cout << "3.\tCredit Transfer" << endl;
	cout << "4.\tAdd Funds" << endl;
	cout << "5.\tAccount Setup & Update" << endl;
	cout << "6.\tExit" << endl;
	cin >> choice;

	switch (choice)
	{
	case '1':
		cash_withdraw(accnum);
		break;
	case '2':
		pay_utilitybill(accnum);
		break;
	case '3':
		credit_transfer(accnum);
		break;
	case '4':
		add_funds(accnum);
		break;
	case '5':
		acc_update(accnum);
		break;
	case '6':
		exit(0);
	default:
		cout << "Unknown choice!\nExiting..." << endl;
		break;
	}
}

void cash_withdraw(long accnum)
{
	system("CLS");
	// Print the Welcome Message
	cout << welcome_message;
	cout << endl << "Cash Withdraw!" << endl;
	cout << "Enter the amount of the cash to withdraw: ";
	long amount = 0L;
	cin >> amount;

	cout << endl << amount << " of amount is being withdrawn from your account..." << endl;

	ifstream dbo;
	string cur_name, cur_accnum, cur_balance, cur_ccn, cur_pin;
	long int balance = 0L;
	dbo.open((to_string(accnum) + ".db").c_str());
	getline(dbo, cur_name);
	getline(dbo, cur_accnum);
	getline(dbo, cur_balance);
	getline(dbo, cur_ccn);
	getline(dbo, cur_pin);
	dbo.close();
	balance = stol(cur_balance);
	balance -= amount;

	ofstream dbw;
	dbw.open((to_string(accnum) + ".db").c_str());
	dbw << cur_name << endl;
	dbw << cur_accnum << endl;
	dbw << balance << endl;
	dbw << cur_ccn << endl;
	dbw << cur_pin << endl;
	dbw.close();

	cout << "Done!" << endl;
	cout << "Old balance: " << cur_balance;
	cout << "\tNew Balance: " << balance << endl;
	
}


void pay_utilitybill(long accnum)
{
	system("CLS");
	// Print the Welcome Message
	cout << welcome_message;
	cout << endl << "Pay Utililty Bills!" << endl;
	cout << "Enter the total bill amount to pay: ";
	long amount = 0L;
	cin >> amount;

	cout << endl << "The utility bill is being payed using your account..." << endl;

	ifstream dbo;
	string cur_name, cur_accnum, cur_balance, cur_ccn, cur_pin;
	long int balance = 0L;
	dbo.open((to_string(accnum) + ".db").c_str());
	getline(dbo, cur_name);
	getline(dbo, cur_accnum);
	getline(dbo, cur_balance);
	getline(dbo, cur_ccn);
	getline(dbo, cur_pin);
	dbo.close();
	balance = stol(cur_balance);
	balance -= amount;

	ofstream dbw;
	dbw.open((to_string(accnum) + ".db").c_str());
	dbw << cur_name << endl;
	dbw << cur_accnum << endl;
	dbw << balance << endl;
	dbw << cur_ccn << endl;
	dbw << cur_pin << endl;
	dbw.close();

	cout << "Done!" << endl;
	cout << "Old balance: " << cur_balance;
	cout << "\tNew Balance: " << balance << endl;

}


void credit_transfer(long accnum)
{
	system("CLS");
	// Print the Welcome Message
	cout << welcome_message;
	cout << endl << "Credit Transfer Portal" << endl;
	cout << "Enter the account number to transfer the credit to: ";
	long payee = 0L;
	cin >> payee;
	cout << endl << "Enter the amount to transfer: ";
	long amount = 0L;
	cin >> amount;

	cout << endl << "The credit is being transfered..." << endl;

	ifstream dbo;
	string cur_name, cur_accnum, cur_balance, cur_ccn, cur_pin;
	long int balance = 0L;
	dbo.open((to_string(accnum) + ".db").c_str());
	getline(dbo, cur_name);
	getline(dbo, cur_accnum);
	getline(dbo, cur_balance);
	getline(dbo, cur_ccn);
	getline(dbo, cur_pin);
	dbo.close();
	balance = stol(cur_balance);
	balance -= amount;

	ofstream dbw;
	dbw.open((to_string(accnum) + ".db").c_str());
	dbw << cur_name << endl;
	dbw << cur_accnum << endl;
	dbw << balance << endl;
	dbw << cur_ccn << endl;
	dbw << cur_pin << endl;
	dbw.close();

	ifstream dbo2;
	string cur_name2, cur_accnum2, cur_balance2, cur_ccn2, cur_pin2;
	long int balance2 = 0L;
	dbo2.open((to_string(payee) + ".db").c_str());
	getline(dbo2, cur_name2);
	getline(dbo2, cur_accnum2);
	getline(dbo2, cur_balance2);
	getline(dbo2, cur_ccn2);
	getline(dbo2, cur_pin2);
	dbo2.close();
	balance2 = stol(cur_balance2);
	balance2 += amount;

	ofstream dbw2;
	dbw2.open((to_string(payee) + ".db").c_str());
	dbw2 << cur_name2 << endl;
	dbw2 << cur_accnum2 << endl;
	dbw2 << balance2 << endl;
	dbw2 << cur_ccn2 << endl;
	dbw2 << cur_pin2 << endl;
	dbw2.close();
	

	cout << "Done!" << endl;
	cout << "Old balance: " << cur_balance;
	cout << "\tNew Balance: " << balance << endl;

}

void add_funds(long accnum)
{
	system("CLS");
	// Print the Welcome Message
	cout << welcome_message;
	cout << endl << "Add Funds Utility" << endl;
	cout << "Enter the amount of funds to add: ";
	long amount = 0L;
	cin >> amount;

	cout << endl << "The funds and being added..." << endl;

	ifstream dbo;
	string cur_name, cur_accnum, cur_balance, cur_ccn, cur_pin;
	long int balance = 0L;
	dbo.open((to_string(accnum) + ".db").c_str());
	getline(dbo, cur_name);
	getline(dbo, cur_accnum);
	getline(dbo, cur_balance);
	getline(dbo, cur_ccn);
	getline(dbo, cur_pin);
	dbo.close();
	balance = stol(cur_balance);
	balance += amount;

	ofstream dbw;
	dbw.open((to_string(accnum) + ".db").c_str());
	dbw << cur_name << endl;
	dbw << cur_accnum << endl;
	dbw << balance << endl;
	dbw << cur_ccn << endl;
	dbw << cur_pin << endl;
	dbw.close();

	cout << "Done!" << endl;
	cout << "Old balance: " << cur_balance;
	cout << "\tNew Balance: " << balance << endl;

}


void acc_update(long accnum)
{
	system("CLS");
	// Print the Welcome Message
	cout << welcome_message;
	cout << endl << "Account Update Portal" << endl;
	string new_name2;			// Customer's name
	long long int new_ccn;		// Customer's CCN
	short int new_pin;			// Customer's PIN
	cout << "New Name: ";
	cin.ignore();
	getline(cin, new_name2);
	cout << endl << "New CCN:";
	cin >> new_ccn;
	cout << endl << "New PIN:";
	cin >> new_pin;

	cout << endl << "The account is being updated..." << endl;

	ifstream dbo;
	string cur_name, cur_accnum, cur_balance, cur_ccn, cur_pin;
	dbo.open((to_string(accnum) + ".db").c_str());
	getline(dbo, cur_name);
	getline(dbo, cur_accnum);
	getline(dbo, cur_balance);
	getline(dbo, cur_ccn);
	getline(dbo, cur_pin);
	dbo.close();

	ofstream dbw;
	dbw.open((to_string(accnum) + ".db").c_str());
	dbw << new_name2 << endl;
	dbw << cur_accnum << endl;
	dbw << cur_balance << endl;
	dbw << new_ccn << endl;
	dbw << new_pin << endl;
	dbw.close();

	cout << "Done!" << endl;
}