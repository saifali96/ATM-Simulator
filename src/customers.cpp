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
	// Comment me out after first compilation
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

}