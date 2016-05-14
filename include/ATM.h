#pragma once

/* Customer Structure */
typedef struct customer {
	char name[25];			// Customer's name
	long int accnum;		// Customer's Account Number
	long int balance;		// Customer's Balance
	long long int ccn;		// Customer's CCN
	short int pin;			// Customer's PIN
} customer;


/* Current Logged In Customer */
long int currentUserLoggedIn = 0L;

bool Login_Menu();
int CCN_VALIDATE(long long CCN);
int CCNLength(long long cardNumber);
bool CCNCheckLuhn(long long cardNumber, int digits);
int getDigit(long long cardNumber, int location);
void Show_Stats(long currentUserLoggedIn);
bool CCN_OwnerExists(long long CCN);
bool PIN_Validate(long long CCN, short int PIN);
void LoginUser(long long CCN, short PIN);
string GetAccNum(long long CCN);
string CCN_GetOwner(long long CCN);
void ATMMenu(long accnum);
void cash_withdraw(long accnum);
void pay_utilitybill(long accnum);
void credit_transfer(long accnum);
void acc_update(long accnum);
void add_funds(long accnum);


customer customers[5];

const char* welcome_message = "********************************\n*-->Welcome to Bahria Bank!<---*\n********************************\n";
// Welcome Message