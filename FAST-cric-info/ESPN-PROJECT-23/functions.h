#pragma once
#include "classes.h"

void printLogo()
{


	cout << "\t\t\t\t________________   ____________________" << endl;
	cout << "\t\t\t\t\\_  _____/  _  \\  /   _____/\\__    ___/" << endl;
	cout << "\t\t\t\t|    __)/  /_\\  \\ \\_____  \\   |    |   " << endl;
	cout << "\t\t\t\t|     \\/    |    \\/        \\  |    |   " << endl;
	cout << "\t\t\t\t\\___  /\\____|__  /_______  /  |____|   " << endl;
	cout << "\t\t\t\t    \\/         \\/        \\/           \tAs of " << __DATE__ << endl << endl;

}
void print_menu(int& opt)
{
	const int si = 6;
	int arr[si] = { 0 };

	opt %= si;
	opt += si;
	opt %= si;
	arr[opt] = 1;
	system("cls");
	printLogo();

	for (size_t i = 0; i < 100; i++)
		cout << char(223);
	cout << endl;
	print_str("Matches", arr[0], 143);
	print_str("Ranking", arr[1], 143);
	print_str("Players", arr[2], 143);
	print_str("Teams", arr[3], 143);
	print_str("Admin Login", arr[4], 143);
	print_str("Exit", arr[5], 12);
	cout << "\n\n";

}
void sub_print_menu(int& opt, int& op)
{
	opt %= 6;
	opt += 6;
	opt %= 6;

	if (opt == 0)
	{
		const int k = 2;
		op %= k;
		op += k;
		op %= k;
		int arr[k] = { 0 };
		if (op > -1)
			arr[op] = 1;
		print_str("Check All Matches", arr[0], 8, arr[0]);
		cout << endl;
		print_str("Show Fixtures", arr[1], 8, arr[1]);
		cout << endl << endl << endl;
	}
	if (opt == 1)
	{
		const int k = 2;
		int arr[k] = { 0 };
		op %= k;
		op += k;
		op %= k;
		if (op > -1)
			arr[op] = 1;

		cout << "\t\t";
		print_str("Players Ranking", arr[0], 8, arr[0]);
		cout << "\n\t\t";
		print_str("Teams Ranking", arr[1], 8, arr[1]);
		cout << endl;
	}
	if (opt == 2)
	{
		const int k = 3;
		int arr[k] = { 0 };
		op %= k;
		op += k;
		op %= k;
		if (op > -1)
			arr[op] = 1;
		cout << "\t\t\t\t";
		print_str("Batters", arr[0], 8, arr[0]);
		cout << "\n\t\t\t\t";
		print_str("Bowlers", arr[1], 8, arr[1]);
		cout << "\n\t\t\t\t";
		print_str("All Rounders", arr[2], 8, arr[2]);
		cout << endl;
	}
	if (opt == 3)
	{
		const int k = 2;
		int arr[k] = { 0 };
		op %= k;
		op += k;
		op %= k;
		if (op > -1)
			arr[op] = 1;
		cout << "\t\t\t\t\t\t";
		print_str("International Teams", arr[0], 8, arr[0]);
		cout << "\n\t\t\t\t\t\t";
		print_str("Local Teams", arr[1], 8, arr[1]);
		cout << endl;
	}
	if (opt == 4 && is_developer == true)
	{
		const int k = 10;
		int arr[k] = { 0 };
		op %= k;
		op += k;
		op %= k;
		if (op > -1)
			arr[op] = 1;

		cout << "\n\t\t\t\t\t\t\t\t";
		print_str("Add Match Fixture", arr[0], 8, arr[0]);
		cout << "\n\t\t\t\t\t\t\t\t";
		print_str("Start Live Match", arr[1], 8, arr[1]);
		cout << "\n\t\t\t\t\t\t\t\t";
		print_str("Update Player", arr[2], 8, arr[2]);
		cout << "\n\t\t\t\t\t\t\t\t";
		print_str("Update Team", arr[3], 8, arr[3]);
		cout << "\n\t\t\t\t\t\t\t\t";
		print_str("Add Team", arr[4], 8, arr[4]);
		cout << "\n\t\t\t\t\t\t\t\t";
		print_str("Add Player", arr[5], 8, arr[5]);
		cout << "\n\t\t\t\t\t\t\t\t";
		print_str("Remove Team", arr[6], 12, arr[6]);
		cout << "\n\t\t\t\t\t\t\t\t";
		print_str("Remove Player", arr[7], 12, arr[7]);
		cout << "\n\t\t\t\t\t\t\t\t";
		print_str("Remove Match Record", arr[8], 12, arr[8]);
		cout << "\n\t\t\t\t\t\t\t\t";
		print_str("Log Out", arr[9], 12, arr[9]);
		cout << "\n";
	}
	if (opt == 4 && is_developer == false)
	{
		const int k = 1;
		int arr[k] = { 0 };
		op %= k;
		op += k;
		op %= k;
		if (op > -1)
			arr[op] = 1;
		cout << "\t\t\t\t\t\t\t\t";
		print_str("Login/Sign in", arr[0], 8, arr[0]);
		cout << "\n";
	}
}
bool loginPage()
{
	cout << "Enter RN(Last 4 Digits): ";
	int rollnum;
	cin >> rollnum;
	cout << "Enter Password(Last 4 Digits): ";
	int pass;
	cin >> pass;

	if (pass == rollnum)
		return true;
	else
		return false;
}
void maintainmenu()
{
	system("cls");
	print_menu(option1);
	sub_print_menu(option1, option2);
}
void filedata(bool i)
{
	if (i == 0)
	{
		ifstream U, V, W, X, Y, Z;
		U.open("matches.txt");
		V.open("localteams.txt");
		W.open("internationalteams.txt");
		X.open("batters.txt");
		Y.open("bowlers.txt");
		Z.open("allrounders.txt");
		U >> MT;
		V >> LT;
		W >> IT;
		X >> BT;
		Y >> BW;
		Z >> AR;
		U.close();
		V.close();
		W.close();
		X.close();
		Y.close();
		Z.close();

	}
	if (i == 1)
	{
		ofstream U, V, W, X, Y, Z;
		U.open("matches.txt");
		V.open("localteams.txt");
		W.open("internationalteams.txt");
		X.open("batters.txt");
		Y.open("bowlers.txt");
		Z.open("allrounders.txt");
		U << MT;
		V << LT;
		W << IT;
		X << BT;
		Y << BW;
		Z << AR;
		U.close();
		V.close();
		W.close();
		X.close();
		Y.close();
		Z.close();

	}
}
template<class T>
void getstats(vector<T>& A) {

	int i = 0;
	i = retname(A);
	if (i >= 0)
	{
		cout << A[i];
		cout << "\n\n*****Press Any Key to Return to main menu...****";
		_getch();
	}
}
template<class T>
int retname(vector<T>& A)
{
	int* arr = new int[A.size()];
	int j = 0;
	arr[j] = 1;
	maintainmenu();

	for (int i = 0; i < A.size(); i++) {
		print_str(A[i].getname(), arr[i], 8, arr[i]);
		cout << endl;
	}
	cout << "\nPress SPACE KEY to back...\n";

	char c;

	while ((c = _getch())) {
		for (int i = 0; i < A.size(); i++)
			arr[i] = 0;


		switch (c) {
		case KEY_UP:
			maintainmenu();

			j = (j - 1 + A.size()) % A.size();
			arr[j] = 1;

			for (int i = 0; i < A.size(); i++) {
				print_str(A[i].getname(), arr[i], 8, arr[i]);
				cout << endl;
			}
			cout << "\nPress SPACE KEY to back...\n";

			break;

		case KEY_DOWN:
			maintainmenu();

			j = (j + 1 + A.size()) % A.size();
			arr[j] = 1;

			for (int i = 0; i < A.size(); i++) {
				print_str(A[i].getname(), arr[i], 8, arr[i]);
				cout << endl;
			}
			cout << "\nPress SPACE KEY to back...\n";
			break;

		case ENTER_KEY:
			maintainmenu();

			return j;
			break;
		case KEY_ESCAPE:
			exit(1);
		case KEY_SPACE:
			delete[] arr;
			return -1;
		}
	}

	delete[] arr;
}
template<class T>
void deletethis(vector<T>& A)
{
	int i = 0;
	i = retname(A);
	if (i >= 0)
	{
		A.erase(A.begin() + i);
		cout << "Record has been erased\n";
		_getch();
	}
}
template<class T>
void addthis(vector<T>& A)
{
	T B;
	cin >> B;
	A.push_back(B);
}
template<class T>
void updatethem(vector<T>& A)
{
	int l = retname(A);
	if (l != -1)
		A[l].updatestats();
}
void printscore(int balls, int runs, int wickets, int innings, string s1, string s2, string s3)
{
	cout << "\n\n\n";
	cout << wickets << "\\" << runs << endl;
	int overs = balls / 6;
	balls %= 6;
	cout << "Overs# " << overs << "." << balls << endl;
	cout << "*Batter1: " << s1 << endl;
	cout << "Batter2: " << s2 << endl;
	cout << "Bowler: " << s3 << endl;
}
int getnonnegative()
{
	//getting positive/non-zero number for different variables, and to reduces no of lines of code//
	int num = 0;
	do
	{
		cin >> num;
		if (num >= 0)
			break;
		else
			cout << "Invalid Number.\nInput Again:";
	} while (true);
	return num;
}
bool isBBIFormatValid(const string& bbi) {
	//Get till it gets the right formatted BBI
	if (bbi.length() < 3 || bbi.length() > 5)
		return false;

	size_t dashPos = bbi.find('/');
	if (dashPos == string::npos || dashPos == 0 || dashPos == bbi.length() - 1)
		return false;

	string wicketsStr = bbi.substr(0, dashPos);
	string runsStr = bbi.substr(dashPos + 1);

	if (wicketsStr.empty() || runsStr.empty())
		return false;

	for (char c : wicketsStr) {
		if (!isdigit(c))
			return false;
	}

	for (char c : runsStr) {
		if (!isdigit(c))
			return false;
	}

	int wickets = stoi(wicketsStr);
	int runs = stoi(runsStr);

	if (wickets < 0 || runs < 0 || runs > 999)
		return false;

	return true;
}
bool isDateFormatValid(const string& date) {
	//Get till it gets the right formatted date

	if (date.length() != 10)
		return false;

	if (date[2] != '/' || date[5] != '/')
		return false;

	int day = stoi(date.substr(0, 2));
	int month = stoi(date.substr(3, 2));
	int year = stoi(date.substr(6, 4));

	if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1000 || year > 9999)
		return false;

	return true;
}
string getValidDate() {
	string date;
	int i = 0;
	do {
		if (i != 0)
			cout << "\nEnter Date: ";
		getline(cin, date);
		i++;
	} while (!isDateFormatValid(date));

	return date;
}
string getValidBBI() {
	string bbi;

	do {
		getline(cin, bbi);
	} while (!isBBIFormatValid(bbi));

	return bbi;
}
void printdelivery(int& opt, int balls, int innings)
{
	int arr[19] = { 0 };
	opt %= 19;
	opt += 19;
	opt %= 19;
	maintainmenu();
	arr[opt] = 1;
	cout << "Innings# " << innings + 1 << endl;
	cout << "Enter Delivery Type:\n";
	print_str("Dot", arr[0]);
	cout << endl;
	print_str("Single", arr[1]);
	cout << endl;
	print_str("Double", arr[2]);
	cout << endl;
	print_str("Triple", arr[3]);
	cout << endl;
	print_str("Four", arr[4]);
	cout << endl;
	print_str("Six", arr[5]);
	cout << endl;
	print_str("Wicket", arr[6]);
	cout << endl;
	print_str("Wide 1", arr[7]);
	cout << endl;
	print_str("Wide 2", arr[8]);
	cout << endl;
	print_str("Wide 3", arr[9]);
	cout << endl;
	print_str("Wide 4", arr[10]);
	cout << endl;
	print_str("Wide 5", arr[11]);
	cout << endl;
	print_str("NB 0", arr[12]);
	cout << endl;
	print_str("NB 1", arr[13]);
	cout << endl;
	print_str("NB 2", arr[14]);
	cout << endl;
	print_str("NB 3", arr[15]);
	cout << endl;
	print_str("NB 4", arr[16]);
	cout << endl;
	print_str("NB 6", arr[17]);
	cout << endl;
	print_str("Declare", arr[18]);
	cout << endl;

}
string gettypeball(char a)
{
	switch (a)
	{
	case 'a': return ".";
	case 'b': return "1 ";
	case 'c': return "2 ";
	case 'd': return "3 ";
	case 'e': return "4 ";
	case 'f': return "6 ";
	case 'g': return "W ";
	case 'h': return "w1 ";
	case 'i': return "w2 ";
	case 'j': return "w3 ";
	case 'k': return "w4 ";
	case 'l': return "w5 ";
	case 'm': return "NB1 ";
	case 'n': return "NB2 ";
	case 'o': return "NB3 ";
	case 'p': return "NB4 ";
	case 'q': return "NB6 ";
	case 'r': return "Dec ";

	default:
		break;
	}
}

void case0(int op)
{
	if (op == 0)
	{
		getstats(MT);
		_getch();
	}
	if (op == 1)
	{
		bool is_empty = true;;
		for (int i = 0; i < MT.size(); i++)
			if (MT[i].playing_status == 0)
			{
				is_empty = false;
				cout << MT[i].getname() << endl;
			}
		if (is_empty == true && is_developer == true)
		{
			print_str("Schedule Any Match First to Start Fixture", 1, 112, 0);
			cout << endl;
		}
		else if (is_empty == true && is_developer == false)
		{
			print_str("No Record to Show", 1, 112, 0);
			cout << endl;
		}
		_getch();
	}
}
void case1(int op)
{
	if (op == 0)
	{
		maintainmenu();
		print_str("Batters", 1, 112, 0);
		cout << endl << endl;
		for (int i = 0; i < BT.size(); i++)
			cout << i + 1 << ". " << BT[i].getname() << "\n";
		cout << endl;
		print_str("Bowlers", 1, 112, 0);
		cout << endl << endl;
		for (int i = 0; i < BW.size(); i++)
			cout << i + 1 << ". " << BW[i].getname() << "\n";
		cout << endl;
		print_str("All Rounders", 1, 112, 0);
		cout << endl << endl;
		for (int i = 0; i < AR.size(); i++)
			cout << i + 1 << ". " << AR[i].getname() << "\n";


		cout << "\nPress SPACE KEY to back...\n";
		_getch();
	}
	if (op == 1)
	{
		maintainmenu();
		print_str("Red Ball", 1, 112, 0);
		cout << endl << endl;
		for (int i = 0; i < IT.size(); i++)
			cout << i + 1 << ". " << IT[i].getname() << "\n";
		cout << endl;
		print_str("White Ball", 1, 112, 0);
		cout << endl << endl;
		for (int i = IT.size() - 1; i >= 0; i--)
			cout << i + 1 << ". " << IT[i].getname() << "\n";


		cout << "\nPress SPACE KEY to back...\n";
		_getch();
	}
}
void case2(int op)
{
	if (op == 0)
		getstats(BT);
	if (op == 1)
		getstats(BW);
	if (op == 2)
		getstats(AR);
}
void case3(int op)
{
	if (op == 0)
		getstats(IT);
	if (op == 1)
		getstats(LT);
}
void case4(int op)
{
	if (is_developer)
	{
		if (op == 0)
		{
			addthis(MT);
		}
		if (op == 1)
		{
			int i = retname(MT);
			if (i >= 0)
				MT[i].startMatch();
		}
		if (op == 2)
		{
			maintainmenu();

			print_str("Update Batter", 1);
			cout << endl;
			print_str("Update Bowler", 0);
			cout << endl;
			print_str("Update All Rounder", 0);
			cout << endl;
			cout << "\nPress SPACE KEY to back...\n";
			int opt = 0;
			while (char c = _getch())
			{
				switch (c)
				{
				case ENTER_KEY:
				{
					if (opt == 0)
					{
						updatethem(BT);
					}
					if (opt == 1)
					{
						updatethem(BW);
					}
					if (opt == 2)
					{
						updatethem(AR);
					}
					cout << "\Player has been updated. Press SPACE KEY to return\n";
					_getch();
					return;
					break;
				}
				case KEY_UP:
				{
					--opt;
					int arr[3] = { 0 };
					opt %= 3;
					opt += 3;
					opt %= 3;
					maintainmenu();
					arr[opt] = 1;
					print_str("Update Batter", arr[0]);
					cout << endl;
					print_str("Update Bowler", arr[1]);
					cout << endl;
					print_str("Update All Rounder", arr[2]);
					cout << endl;
					cout << "\nPress SPACE KEY to back...\n";
					break;
				}
				case KEY_DOWN:
				{
					++opt;
					int arr[3] = { 0 };
					opt %= 3;
					maintainmenu();

					arr[opt] = 1;
					print_str("Update Batter", arr[0]);
					cout << endl;
					print_str("Update Bowler", arr[1]);
					cout << endl;
					print_str("Update All Rounder", arr[2]);
					cout << endl;
					cout << "\nPress SPACE KEY to back...\n";
					break;
				}
				case KEY_SPACE:
					return;

				default:
					break;
				}
			}
		}
		if (op == 3)
		{
			maintainmenu();

			print_str("Update Local Team", 1);
			cout << endl;
			print_str("Update International Team", 0);
			cout << endl;
			cout << "\nPress SPACE KEY to back...\n";
			int opt = 0;
			while (char c = _getch())
			{
				switch (c)
				{
				case ENTER_KEY:
				{
					if (opt == 0)
					{
						updatethem(LT);
					}
					if (opt == 1)
					{
						updatethem(IT);
					}
					cout << "\Team has been updated. Press SPACE KEY to return\n";
					_getch();
					return;
					break;
				}
				case KEY_UP:
				{
					--opt;
					int arr[2] = { 0 };
					opt %= 2;
					opt += 2;
					opt %= 2;
					maintainmenu();
					arr[opt] = 1;
					print_str("Update Local Team", arr[0]);
					cout << endl;
					print_str("Update International Team", arr[1]);
					cout << endl;
					cout << "\nPress SPACE KEY to back...\n";

					break;
				}
				case KEY_DOWN:
				{
					++opt;
					int arr[2] = { 0 };
					opt %= 2;
					opt += 2;
					opt %= 2;
					maintainmenu();
					arr[opt] = 1;
					print_str("Update Local Team", arr[0]);
					cout << endl;
					print_str("Update International Team", arr[1]);
					cout << endl;
					cout << "\nPress SPACE KEY to back...\n";

					break;
				}
				case KEY_SPACE:
					return;

				default:
					break;
				}
			}
		}
		if (op == 4)
		{
			maintainmenu();

			print_str("Add International Team", 1);
			cout << endl;
			print_str("Add Local Team", 0);
			cout << endl;
			cout << "\nPress SPACE KEY to back...\n";
			int opt = 0;
			while (char c = _getch())
			{
				switch (c)
				{
				case ENTER_KEY:
				{
					if (opt == 0)
					{
						InternationalTeams T;
						cin >> T;
						IT.push_back(T);
					}
					if (opt == 1)
					{
						LocalTeams B;
						cin >> B;
						LT.push_back(B);
					}

					cout << "\Team has been added. Press SPACE KEY to return\n";
					_getch();
					return;
					break;
				}
				case KEY_UP:
				{
					--opt;
					int arr[2] = { 0 };
					opt %= 2;
					opt += 2;
					opt %= 2;

					maintainmenu();

					arr[opt] = 1;
					print_str("Add International Team", arr[0]);
					cout << endl;
					print_str("Add Local Team", arr[1]);
					cout << endl;
					cout << "\nPress SPACE KEY to back...\n";
					break;
				}
				case KEY_DOWN:
				{
					++opt;
					int arr[2] = { 0 };
					opt %= 2;
					maintainmenu();

					arr[opt] = 1;
					print_str("Add International Team", arr[0]);
					cout << endl;
					print_str("Add Local Team", arr[1]);
					cout << endl;
					cout << "\nPress SPACE KEY to back...\n";
					break;
				}
				case KEY_SPACE:
					return;

				default:
					break;
				}
			}
		}
		if (op == 5)
		{
			maintainmenu();

			print_str("Add Batter", 1);
			cout << endl;
			print_str("Add Bowler", 0);
			cout << endl;
			print_str("Add All Rounder", 0);
			cout << endl;
			cout << "\nPress SPACE KEY to back...\n";
			int opt = 0;
			while (char c = _getch())
			{
				switch (c)
				{
				case ENTER_KEY:
				{
					if (opt == 0)
					{
						addthis(BT);
					}
					if (opt == 1)
					{
						addthis(BW);
					}
					if (opt == 2)
					{
						addthis(AR);
					}
					cout << "\Player has been added. Press SPACE KEY to return\n";
					_getch();
					return;
					break;
				}
				case KEY_UP:
				{
					--opt;
					int arr[3] = { 0 };
					opt %= 3;
					opt += 3;
					opt %= 3;
					maintainmenu();

					arr[opt] = 1;
					print_str("Add Batter", arr[0]);
					cout << endl;
					print_str("Add Bowler", arr[1]);
					cout << endl;
					print_str("Add All Rounder", arr[2]);
					cout << endl;
					cout << "\nPress SPACE KEY to back...\n";
					break;
				}
				case KEY_DOWN:
				{
					++opt;
					int arr[3] = { 0 };
					opt %= 3;
					maintainmenu();

					arr[opt] = 1;
					print_str("Add Batter", arr[0]);
					cout << endl;
					print_str("Add Bowler", arr[1]);
					cout << endl;
					print_str("Add All Rounder", arr[2]);
					cout << endl;
					cout << "\nPress SPACE KEY to back...\n";
					break;
				}
				case KEY_SPACE:
					return;

				default:
					break;
				}
			}
			cout << "Player has been added\n";
			cout << "Press SPACE KEY to back...\n";
			_getch();
		}
		if (op == 6)
		{
			maintainmenu();

			print_str("Delete Batter", 1);
			cout << endl;
			print_str("Delete Bowler", 0);
			cout << endl;
			print_str("Delete All Rounder", 0);
			cout << endl;
			cout << "\nPress SPACE KEY to back...\n";
			int opt = 0;
			while (char c = _getch())
			{
				switch (c)
				{
				case ENTER_KEY:
				{
					if (opt == 0)
					{
						deletethis(BT);
					}
					if (opt == 1)
					{
						deletethis(BW);
					}
					if (opt == 2)
					{
						deletethis(AR);
					}
					cout << "\Player has been Removed. Press SPACE KEY to return\n";
					_getch();
					return;
					break;
				}
				case KEY_UP:
				{
					--opt;
					int arr[3] = { 0 };
					opt %= 3;
					opt += 3;
					opt %= 3;
					maintainmenu();

					arr[opt] = 1;
					print_str("Delete Batter", arr[0]);
					cout << endl;
					print_str("Delete Bowler", arr[1]);
					cout << endl;
					print_str("Delete All Rounder", arr[2]);
					cout << endl;
					cout << "\nPress SPACE KEY to back...\n";
					break;
				}
				case KEY_DOWN:
				{
					++opt;
					int arr[3] = { 0 };
					opt %= 3;
					maintainmenu();

					arr[opt] = 1;
					print_str("Delete Batter", arr[0]);
					cout << endl;
					print_str("Delete Bowler", arr[1]);
					cout << endl;
					print_str("Delete All Rounder", arr[2]);
					cout << endl;
					cout << "\nPress SPACE KEY to back...\n";
					break;
				}
				case KEY_SPACE:
					return;

				default:
					break;
				}
			}
			cout << "Player has been added\n";
			cout << "Press SPACE KEY to back...\n";
			_getch();
		}
		if (op == 7)
		{
			maintainmenu();

			print_str("Delete International Team", 1);
			cout << endl;
			print_str("Delete Local Team", 0);
			cout << endl;
			cout << "\nPress SPACE KEY to back...\n";
			int opt = 0;
			while (char c = _getch())
			{
				switch (c)
				{
				case ENTER_KEY:
				{
					if (opt == 0)
					{
						deletethis(IT);
					}
					if (opt == 1)
					{
						deletethis(LT);
					}

					cout << "\Team has been Deleted. Press SPACE KEY to return\n";
					_getch();
					return;
					break;
				}
				case KEY_UP:
				{
					--opt;
					int arr[2] = { 0 };
					opt %= 2;
					opt += 2;
					opt %= 2;

					maintainmenu();

					arr[opt] = 1;
					print_str("Delete International Team", arr[0]);
					cout << endl;
					print_str("Delete Local Team", arr[1]);
					cout << endl;
					cout << "\nPress SPACE KEY to back...\n";
					break;
				}
				case KEY_DOWN:
				{
					++opt;
					int arr[2] = { 0 };
					opt %= 2;
					maintainmenu();

					arr[opt] = 1;
					print_str("Delete International Team", arr[0]);
					cout << endl;
					print_str("Delete Local Team", arr[1]);
					cout << endl;
					cout << "\nPress SPACE KEY to back...\n";
					break;
				}
				case KEY_SPACE:
					return;

				default:
					break;
				}
			}
		}
		if (op == 8)
		{
			deletethis(MT);
		}
		if (op == 9)
		{
			is_developer = 0;
		}
	}
	else
		is_developer = loginPage();

}
void case5()
{
	filedata(1);
	exit(0);
}

void runProg(int& opt_major, int& opt_minor)
{
	filedata(0);
	int c = 0;
	print_menu(opt_major);
	int n = 0;
	sub_print_menu(opt_major, n);
	bool opt_found = false;
	while (c = _getch())
	{
		switch (c)
		{
		case ENTER_KEY:
			switch (opt_major)
			{
			case 0:
				case0(opt_minor);
				break;
			case 1:
				case1(opt_minor);
				break;
			case 2:
				case2(opt_minor);
				break;
			case 3:
				case3(opt_minor);
				break;
			case 4:
				case4(opt_minor);
				break;
			case 5:
				case5();
				break;
			default:
				break;
			}
			opt_major++;

		case KEY_LEFT:
			opt_minor = 0;
			print_menu(--opt_major);
			sub_print_menu(opt_major, n);
			break;
		case KEY_RIGHT:
			opt_minor = 0;
			print_menu(++opt_major);
			sub_print_menu(opt_major, n);
			break;
		case KEY_DOWN:
			print_menu(opt_major);
			sub_print_menu(opt_major, ++opt_minor);
			break;
		case KEY_UP:
			print_menu(opt_major);
			sub_print_menu(opt_major, --opt_minor);
			break;
		case KEY_ESCAPE:
			case5();
		}
		if (opt_found == true)
			break;
	}
}
