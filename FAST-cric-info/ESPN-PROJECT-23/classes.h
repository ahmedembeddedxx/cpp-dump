#pragma once
#include <conio.h>
#include <iostream>
#include <windows.h>
#include <vector>
#include <cmath>
#include <fstream>
#include <string.h>
#include <string>
#include <cstring>
#include <ctime>
#include <sstream>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_RIGHT 77
#define KEY_LEFT 75
#define ENTER_KEY 13
#define KEY_BACKSPACE 8
#define KEY_ESCAPE 27
#define KEY_SPACE 32

//For Arrow Keys

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
using namespace std;
bool is_developer = 0;
int option1 = 0, option2 = 0;
void maintainmenu();
template<class T>
int retname(vector<T>& A);
template<class T>
int retname(vector<T>& A);
template<class T>
void updatethem(vector<T>& A);
template<class T>
void addthis(vector<T>& A);
void printscore(int balls, int runs, int wickets, int innings, string s1, string s2, string s3);
void print_str(string str, int v, int n = 8, int i = 0)
{
	//Print String with Different Color, distiction in colors//
	if (v == 1 && i == 1)
	{
		SetConsoleTextAttribute(h, n);
		cout << char(249);
	}
	if (v == 1 && i == 0)
		SetConsoleTextAttribute(h, n);
	cout << str;
	SetConsoleTextAttribute(h, 7);
	cout << "\t\t";
}
int getnonnegative();
bool isBBIFormatValid(const string& bbi);
bool isDateFormatValid(const string& date);
string getValidDate();
string getValidBBI();
void printdelivery(int& opt, int balls, int innings);
string gettypeball(char a);
void case0(int op);
void case1(int op);
void case2(int op);
void case3(int op);
void case4(int op);
void case5();
void runProg(int& opt_major, int& opt_minor);

class Players
{
protected:
	Players()
	{
		this->matches = 0;
		this->innings = 0;
		this->name = "Nil";
		this->country = "Nil";
		this->role = "Nil";
		this->dob = "01/01/1999";
		// Extract the year part "2004"
		int yearOfBirth = stoi(dob.substr(6, 4));  // Convert the year string to an integer
		age = 2023 - yearOfBirth;
		this->debut = "01/01/2014";
	}
	int matches, innings, iccrank;
	double age;
	string name, country, role, dob, debut;

public:
	Players(int matches, int innings, string name, string country, string role, string dob, string debut, int iccrank = 0)
	{
		if (matches < 0)
			matches = 0;
		if (innings < 0)
			innings = 0;
		if (age < 14)
			age = 14;
		this->iccrank = iccrank;
		this->matches = matches;
		this->innings = innings;
		this->name = name;
		this->country = country;
		this->role = role;
		this->dob = dob;
		string yearString = dob.substr(6, 4);  // Extract the year part "2004"
		int yearOfBirth = stoi(yearString);  // Convert the year string to an integer
		age = 2023 - yearOfBirth;
		this->debut = debut;
	}
	~Players()
	{
		//Explicitly no code here, as of no pointers or dynanmic memory allocation//
	}
	virtual void display() = 0;//Abstract Class, no possible obbjects from this class//
	//Setters for Admin Options, no need of Getters
	string getname()
	{
		return name;
	}
	virtual void updatestats() = 0;

};
class Batters : public virtual Players
{
	friend class AllRounders; //Accessible and Modifiable Members
protected:
	int notouts, battingruns, hs, ballfaced, hundreds, fifties, fours, sixes, catches, dismissals, stumps;
	string battingstyle;

public:
	//Default Constructor
	Batters()
	{
		this->notouts = 0;
		this->battingruns = 0;
		this->hs = 0;
		this->ballfaced = 0;
		this->hundreds = 0;
		this->fifties = 0;
		this->fours = 0;
		this->sixes = 0;
		this->catches = 0;
		this->battingstyle = "Nil";
		this->stumps = 0;
		this->iccrank = 11;
	}
	~Batters()
	{
		//Explicitly no code here, as of no pointers or dynanmic memory allocation//
	}
	//Parameterized Constructor
	Batters(int matches, int innings, string name, string country,
		string role, string dob, string debut, int notouts, int battingruns, int hs,
		int ballfaced, int hundreds, int fifties, int fours, int sixes,
		int catches, string battingstyle, int stumps, int iccrank)
		:Players(matches, innings, name, country, role, dob, debut, iccrank)
	{
		if (notouts < 0) notouts = 0;
		if (battingruns < 0) battingruns = 0;
		if (hs < 0) hs = 0;
		if (ballfaced < 0) ballfaced = 0;
		if (hundreds < 0) hundreds = 0;
		if (fifties < 0) fifties = 0;
		if (fours < 0) fours = 0;
		if (sixes < 0) sixes = 0;
		if (catches < 0) catches = 0;
		if (stumps < 0) stumps = 0;


		this->notouts = notouts;
		this->battingruns = battingruns;
		this->hs = hs;
		this->ballfaced = ballfaced;
		this->hundreds = fifties;
		this->fifties = fifties;
		this->fours = fours;
		this->sixes = sixes;
		this->catches = catches;
		this->battingstyle = battingstyle;
		this->stumps = stumps;
	}
	//Override incase of All Rounders
	virtual void reset()
	{
		this->name = "Nil";
		this->country = "Nil";
		this->role = "Nil";
		this->dob = "01/01/1999";
		age = 2023 - 1999;
		this->debut = "01/01/2014";
		matches = innings = notouts = battingruns = hs = ballfaced = hundreds =
			fifties = iccrank = fours = sixes = catches = stumps = 0;
	}
	void display()
	{

	}
	void updatestats()
	{
		cout << "1. Update Matches\n";
		cout << "2. Update Innings\n";
		cout << "3. Update Notouts\n";
		cout << "4. Update batting Runs\n";
		cout << "5. Update HS\n";
		cout << "6. Update ballfaced\n";
		cout << "7. Update Hundreds\n";
		cout << "8. Update Fifties\n";
		cout << "9. Update Fours\n";
		cout << "10. Update Sixes\n";
		cout << "11. Update Catches\n";
		cout << "12. Update Stumps\n";
		int i = 0;
		cout << "Press KEY to choose the stat: ";
		cin >> i;
		cout << "Enter Updated Stat: \n";
		switch (i)
		{
		case 1: matches = getnonnegative(); break;
		case 2: innings = getnonnegative(); break;
		case 3: notouts = getnonnegative(); break;
		case 4: battingruns = getnonnegative(); break;
		case 5: hs = getnonnegative(); break;
		case 6: ballfaced = getnonnegative(); break;
		case 7: hundreds = getnonnegative(); break;
		case 8: fifties = getnonnegative(); break;
		case 9: fours = getnonnegative(); break;
		case 10: sixes = getnonnegative(); break;
		case 11: catches = getnonnegative(); break;
		case 12: stumps = getnonnegative(); break;

		default:
			break;
		}

	}

	//Operators, for both console and file stream
	friend ostream& operator<<(ostream& COUT, Batters A)
	{
		float sr = 0, avg = 0;
		if (A.ballfaced > 0)
			sr = (A.battingruns * 60.0) / A.ballfaced;
		if ((A.innings - A.notouts) > 0)
			avg = A.battingruns * 1.0 / (A.innings - A.notouts);
		print_str(A.name, 1, 112, 0);
		COUT << "\n" << "Country: " << A.country << "\n" << "Age: " << A.age << endl;
		COUT << "Role: " << A.role << "\n" << "Debut: " << A.debut << "\n" << "DOB: " << A.dob << endl;
		COUT << "Matches: " << A.matches << "\n" << "Innings: " << A.innings << endl << "ICC Rank: " << A.iccrank << endl;
		SetConsoleTextAttribute(h, 112);
		COUT << "\nBatting Stats: \n";
		SetConsoleTextAttribute(h, 7);
		COUT << "Hundreds: " << A.hundreds << "\n" << "Fifties: " << A.fifties << "\n" << "Fours: " << A.fours << endl;
		COUT << "Sixes: " << A.sixes << "\n" << "Not Outs: " << A.notouts << "\n" << "Runs: " << A.battingruns << endl;
		COUT << "Ball Faced: " << A.ballfaced << "\n" << "Catches: " << A.catches << "\n" << "Stumps: " << A.stumps << endl;
		COUT << "HS: " << A.hs << "\n" << "Batting Style: " << A.battingstyle << "\n" << "SR: " << sr << endl << "Average: " << avg << endl;
		return COUT;
	}
	friend ofstream& operator<<(ofstream& fout, vector <Batters> A)
	{
		for (int i = 0; i < A.size(); i++)
		{
			fout << A[i].matches << '*' << A[i].innings << '*' << A[i].name << '*' << A[i].country << '*' << A[i].role << '*' << A[i].dob << '*' << A[i].debut << '*'
				<< A[i].notouts << '*' << A[i].battingruns << '*' << A[i].hs << '*' << A[i].ballfaced << '*' << A[i].hundreds << '*' << A[i].fifties << '*'
				<< A[i].fours << '*' << A[i].sixes << '*' << A[i].catches << '*' << A[i].battingstyle << '*' << A[i].stumps << '*' << A[i].iccrank << '*' << endl;
		}
		return fout;
	}
	friend ifstream& operator>>(ifstream& fin, vector <Batters>& P)
	{
		string data;
		Batters B;
		while (getline(fin, data))
		{
			if (data[0] == '}')
				break;
			int var = 0;
			for (int i = 0; data[i] != '\0'; i++, var++)
			{
				char datasegment[40] = "\0";
				int j = 0;
				for (j = 0; data[i] != '*'; j++, i++)
					datasegment[j] = data[i];
				datasegment[j] = '\0';
				if (var == 0) 	B.matches = stoi(datasegment);
				if (var == 1)	B.innings = stoi(datasegment);
				if (var == 2)	B.name = (datasegment);
				if (var == 3)	B.country = (datasegment);
				if (var == 4)	B.role = (datasegment);
				if (var == 5)	B.dob = (datasegment);
				if (var == 6)	B.debut = (datasegment);
				if (var == 7)	B.notouts = stoi(datasegment);
				if (var == 8)	B.battingruns = stoi(datasegment);
				if (var == 9)	B.hs = stoi(datasegment);
				if (var == 10)	B.ballfaced = stoi(datasegment);
				if (var == 11)	B.hundreds = stoi(datasegment);
				if (var == 12)	B.fifties = stoi(datasegment);
				if (var == 13)	B.fours = stoi(datasegment);
				if (var == 14)	B.sixes = stoi(datasegment);
				if (var == 15)	B.catches = stoi(datasegment);
				if (var == 16)	B.battingstyle = (datasegment);
				if (var == 17)	B.stumps = stoi(datasegment);
				if (var == 18)	B.iccrank = stoi(datasegment);
			}
			P.push_back(B);
		}
		return fin;
	}
	friend istream& operator>>(istream& CIN, Batters& B)
	{
		print_str("Batting Stats", 1, 112);
		cout << '\n';
		cout << "Enter Name: ";
		getline(CIN, B.name);
		CIN.ignore();
		cout << "Matches Played: ";
		B.matches = getnonnegative();
		cout << "Innings Played: ";
		B.innings = getnonnegative();
		cout << "Enter Country: ";
		CIN >> B.country;
		CIN.ignore();
		cout << "Enter Role: ";
		getline(CIN, B.role);
		CIN.ignore();
		cout << "DOB (dd-mm-yyyy): ";
		B.dob = getValidDate();
		cout << "Debut (dd-mm-yyyy): ";
		B.debut = getValidDate();
		cout << "Not Outs: ";
		B.notouts = getnonnegative();
		cout << "Batting Runs: ";
		B.battingruns = getnonnegative();
		cout << "Highest Score: ";
		B.hs = getnonnegative();
		cout << "Ball Faced: ";
		B.ballfaced = getnonnegative();
		cout << "Hundreds: ";
		B.hundreds = getnonnegative();
		cout << "Fifties: ";
		B.fifties = getnonnegative();
		cout << "Fours: ";
		B.fours = getnonnegative();
		cout << "Sixes: ";
		B.sixes = getnonnegative();
		cout << "Catches: ";
		B.catches = getnonnegative();
		cout << "Stumps: ";
		B.stumps = getnonnegative();
		cout << "Dismissals: ";
		B.stumps = getnonnegative();
		cout << "ICC Rank: ";
		B.iccrank = getnonnegative();
		cout << "Enter Batting Style: ";
		getline(CIN, B.battingstyle);
		CIN.ignore();

		return CIN;
	}
};
class Bowlers : public virtual Players
{
	friend class AllRounders;
protected:
	int ballsbowled, bowlingruns, wickets, fiveW, tenW, noballs;
	string BBI, bowlingstyle;
public:
	//Default Constructor
	Bowlers()
		:Players()
	{
		this->ballsbowled = 0;
		this->bowlingruns = 0;
		this->wickets = 0;
		this->fiveW = 0;
		this->tenW = 0;
		this->noballs = 0;
		this->BBI = "Nil";
		this->bowlingstyle = "Nil";
	}
	//Parameterized Constructor
	Bowlers(int matches, int innings, string name, string country,
		string role, string dob, string debut, int ballsbowled, int bowlingruns, int wickets,
		int  fiveW, int  tenW, int  noballs, string BBI, string bowlingstyle, int iccrank)
		:Players(matches, innings, name, country, role, dob, debut, iccrank)
	{
		if (ballsbowled < 0) ballsbowled = 0;
		if (bowlingruns < 0) bowlingruns = 0;
		if (wickets < 0) wickets = 0;
		if (fiveW < 0) fiveW = 0;
		if (tenW < 0) tenW = 0;
		if (noballs < 0) noballs = 0;
		this->ballsbowled = ballsbowled;
		this->bowlingruns = bowlingruns;
		this->wickets = wickets;
		this->fiveW = fiveW;
		this->tenW = tenW;
		this->noballs = noballs;
		this->BBI = BBI;
		this->bowlingstyle = bowlingstyle;
	}
	~Bowlers()
	{

	}
	virtual void reset()
	{
		this->name = "Nil";
		this->country = "Nil";
		this->role = "Nil";
		this->dob = "01/01/1999";
		age = 2023 - 1999;
		this->debut = "01/01/2014";
		matches = innings = ballsbowled = bowlingruns = iccrank = wickets = fiveW = tenW = noballs = 0;
	}
	void updatestats()
	{
		cout << "1. Update Bowls Balled\n";
		cout << "2. Update Bowling Runs\n";
		cout << "3. Update Wickets\n";
		cout << "4. Update 5Ws\n";
		cout << "5. Update 10Ws\n";
		cout << "6. Update No Balls\n";
		cout << "7. Update BBI\n";
		cout << "8. Update Ranking\n";
		int i = 0;
		cout << "Press KEY to choose the stat: ";
		cin >> i;
		cout << "Enter Updated Stat: \n";
		switch (i)
		{
		case 1: ballsbowled = getnonnegative(); break;
		case 2: bowlingruns = getnonnegative(); break;
		case 3: wickets = getnonnegative(); break;
		case 4: fiveW = getnonnegative(); break;
		case 5: tenW = getnonnegative(); break;
		case 6: noballs = getnonnegative(); break;
		case 7: BBI = getValidBBI(); break;
		case 8: iccrank = getnonnegative(); break;

		default:
			break;
		}

	}

	void display()
	{
		float econ = (bowlingruns * 6.0) / (ballsbowled);
		float sr = (ballsbowled * 1.0) / wickets;
		float avg = bowlingruns * 1.0 / wickets;
		if (wickets == 0)
			sr = avg = 0;
		if (ballsbowled == 0)
			econ = 0;
		SetConsoleTextAttribute(h, 112);
		cout << "\nBowling Stats: \n";
		SetConsoleTextAttribute(h, 7);
		cout << "Wickets: " << wickets << "\n" << "5W: " << fiveW << "\n" << "10W: " << tenW << endl;
		cout << "No Balls: " << noballs << "\n" << "BBI: " << BBI << "\n" << "Economy: " << econ << endl;
		cout << "Bowling Style: " << bowlingstyle << endl << "Ball Bowled: " << ballsbowled << "\n" << "SR: " << sr << endl;
		cout << "Runs: " << bowlingruns << "\n" << "Average: " << avg << endl;
	}

	//Operator for both file and console I/O
	friend ostream& operator << (ostream& COUT, Bowlers B)
	{

		float econ = (B.bowlingruns * 6.0) / (B.ballsbowled);
		float sr = (B.ballsbowled * 1.0) / B.wickets;
		float avg = B.bowlingruns * 1.0 / B.wickets;
		if (B.wickets == 0)
			sr = avg = 0;
		if (B.ballsbowled == 0)
			econ = 0;
		print_str(B.name, 1, 112, 0);
		COUT << "\n" << "Country: " << B.country << "\n" << "Age: " << B.age << endl;
		COUT << "Role: " << B.role << "\n" << "Debut: " << B.debut << "\n" << "DOB: " << B.dob << endl;
		COUT << "Matches: " << B.matches << "\n" << "Innings: " << B.innings << endl;
		COUT << "ICC Rank: " << B.iccrank;
		SetConsoleTextAttribute(h, 112);
		COUT << "\nBowling Stats: \n";
		SetConsoleTextAttribute(h, 7);
		COUT << "Wickets: " << B.wickets << "\n" << "5W: " << B.fiveW << "\n" << "10W: " << B.tenW << endl;
		COUT << "No Balls: " << B.noballs << "\n" << "BBI: " << B.BBI << "\n" << "Economy: " << econ << endl;
		COUT << "Bowling Style: " << B.bowlingstyle << endl << "Ball Bowled: " << B.ballsbowled << "\n" << "SR: " << sr << endl;
		COUT << "Runs: " << B.bowlingruns << "\n" << "Average: " << avg << endl;
		return COUT;
	}
	friend istream& operator >> (istream& CIN, Bowlers& B)
	{
		print_str("Bowling Stats", 1, 112);
		cout << '\n';
		cout << "Enter Name: ";
		getline(CIN, B.name);
		CIN.ignore();
		cout << "Matches Played: ";
		B.matches = getnonnegative();
		cout << "Innings Played: ";
		B.innings = getnonnegative();
		cout << "Enter Country: ";
		CIN >> B.country;
		CIN.ignore();
		cout << "Enter Role: ";
		getline(CIN, B.role);
		CIN.ignore();
		cout << "DOB (dd-mm-yyyy): ";
		B.dob = getValidDate();
		cout << "Debut (dd-mm-yyyy): ";
		B.debut = getValidDate();
		cout << "Balls Bowled: ";
		B.ballsbowled = getnonnegative();
		cout << "Bowling Runs: ";
		B.bowlingruns = getnonnegative();
		cout << "Wickets: ";
		B.wickets = getnonnegative();
		cout << "Five W: ";
		B.fiveW = getnonnegative();
		cout << "Ten W: ";
		B.tenW = getnonnegative();
		cout << "No Balls: ";
		B.noballs = getnonnegative();
		cout << "ICC Rank: ";
		B.iccrank = getnonnegative();
		cout << "Enter BBI (ww/rr): ";
		B.BBI = getValidBBI();
		cout << "Enter Bowling Style: ";
		getline(CIN, B.bowlingstyle);
		CIN.ignore();

		return CIN;
	}
	friend ofstream& operator<<(ofstream& fout, vector <Bowlers> A)
	{
		for (int i = 0; i < A.size(); i++)
		{
			fout << A[i].matches << '*' << A[i].innings << '*' << A[i].name << '*' << A[i].country << '*' << A[i].role << '*' << A[i].dob << '*' << A[i].debut << '*'
				<< A[i].ballsbowled << '*' << A[i].bowlingruns << '*' << A[i].wickets << '*' << A[i].fiveW << '*' << A[i].tenW << '*' << A[i].noballs << '*' << A[i].BBI << '*'
				<< A[i].bowlingstyle << '*' << A[i].iccrank << "*" << endl;
		}
		return fout;
	}
	friend ifstream& operator>>(ifstream& fin, vector <Bowlers>& P)
	{
		string data;
		Bowlers B;
		while (getline(fin, data))
		{
			if (data[0] == '}')
				break;
			int var = 0;
			for (int i = 0; data[i] != '\0'; i++, var++)
			{
				char datasegment[40] = "\0";

				int j = 0;
				for (j = 0; data[i] != '*'; j++, i++)
					datasegment[j] = data[i];
				datasegment[j] = '\0';
				if (var == 0) 	B.matches = stoi(datasegment);
				if (var == 1)	B.innings = stoi(datasegment);
				if (var == 2)	B.name = (datasegment);
				if (var == 3)	B.country = (datasegment);
				if (var == 4)	B.role = (datasegment);
				if (var == 5)	B.dob = (datasegment);
				if (var == 6)	B.debut = (datasegment);
				if (var == 7)	B.ballsbowled = stoi(datasegment);
				if (var == 8)	B.bowlingruns = stoi(datasegment);
				if (var == 9)	B.wickets = stoi(datasegment);
				if (var == 10)	B.fiveW = stoi(datasegment);
				if (var == 11)	B.tenW = stoi(datasegment);
				if (var == 12)	B.noballs = stoi(datasegment);
				if (var == 13)	B.BBI = (datasegment);
				if (var == 14)	B.bowlingstyle = (datasegment);
				if (var == 15)	B.iccrank = stoi(datasegment);
			}
			P.push_back(B);
		}
		return fin;
	}
};
class AllRounders : public virtual Batters, public virtual Bowlers
{
	//Explicitly, no members
public:
	//Default Constructor
	AllRounders()
		:Batters(), Bowlers(), Players()
	{
	}
	//Parameterized Constructor
	AllRounders(int matches, int innings, string name, string country,
		string role, string dob, string debut, int notouts, int battingruns, int hs,
		int ballfaced, int hundreds, int fifties, int fours, int sixes,
		int catches, string battingstyle, int stumps, int ballsbowled, int bowlingruns, int wickets,
		int fiveW, int tenW, int noballs, string BBI, string bowlingstyle, int iccrank)
		: Batters(matches, innings, name, country, role, dob, debut, notouts, battingruns, hs,
			ballfaced, hundreds, fifties, fours, sixes, catches, battingstyle, stumps, iccrank),
		Bowlers(matches, innings, name, country, role, dob, debut, ballsbowled, bowlingruns, wickets,
			fiveW, tenW, noballs, BBI, bowlingstyle, iccrank),
		Players(matches, innings, name, country, role, dob, debut, iccrank)
	{
	}
	~AllRounders()
	{

	}
	void reset()
	{
		this->name = "Nil";
		this->country = "Nil";
		this->role = "Nil";
		this->dob = "01/01/1999";
		age = 2023 - 1999;
		this->debut = "01/01/2014";
		ballsbowled = bowlingruns = wickets = fiveW = tenW = noballs = 0;
		matches = innings = notouts = battingruns = hs = ballfaced = hundreds = fifties = fours = sixes = catches = stumps = 0;
	}
	void updatestats()
	{
		cout << "1. Update Bowling Stats\n2. Update Battings Stats\n";
		int i = 0;
		cout << "Select by Number: ";
		cin >> i;
		if (i == 1)
			static_cast<Bowlers>(*this).updatestats();
		if (i == 2)
			static_cast<Batters>(*this).updatestats();

	}
	void display() {

	}
	//Operators for both I/O from Console and File Streams
	friend ostream& operator<<(ostream& COUT, AllRounders A)
	{
		COUT << static_cast<Batters>(A) << endl;
		static_cast<Bowlers>(A).display();

		return COUT;
	}
	friend ofstream& operator<<(ofstream& fout, vector <AllRounders> A)
	{
		for (int i = 0; i < A.size(); i++)
		{
			fout << (A[i]).matches << '*' << (A[i]).innings << '*' << (A[i]).name << '*' << (A[i]).country
				<< '*' << (A[i]).role << '*' << (A[i]).dob << '*' << (A[i]).debut << '*'
				<< A[i].ballsbowled << '*' << A[i].bowlingruns << '*' << A[i].wickets << '*' << A[i].fiveW << '*' << A[i].tenW << '*' << A[i].noballs << '*' << A[i].BBI << '*'
				<< A[i].bowlingstyle << '*' << A[i].notouts << '*' << A[i].battingruns << '*' << A[i].hs << '*' << A[i].ballfaced << '*' << A[i].hundreds << '*' << A[i].fifties << '*'
				<< A[i].fours << '*' << A[i].sixes << '*' << A[i].catches << '*' << A[i].battingstyle << '*' << A[i].stumps << '*' << A[i].iccrank << "*" << endl;
		}
		return fout;
	}
	friend ifstream& operator>>(ifstream& fin, vector<AllRounders>& P)
	{
		string data;
		AllRounders B;
		while (getline(fin, data))
		{
			int var = 0;
			for (int i = 0; data[i] != '\0'; i++, var++)
			{
				char datasegment[40] = "\0";
				int j = 0;
				for (j = 0; data[i] != '*'; j++, i++)
					datasegment[j] = data[i];
				datasegment[j] = '\0';
				if (var == 0) 	B.matches = (stoi(datasegment));
				if (var == 1)	B.innings = (stoi(datasegment));
				if (var == 2)	B.name = (datasegment);
				if (var == 3)	B.country = (datasegment);
				if (var == 4)	B.role = (datasegment);
				if (var == 5)	B.dob = (datasegment);
				if (var == 6)	B.debut = (datasegment);
				if (var == 7)	B.ballsbowled = stoi(datasegment);
				if (var == 8)	B.bowlingruns = stoi(datasegment);
				if (var == 9)	B.wickets = stoi(datasegment);
				if (var == 10)	B.fiveW = stoi(datasegment);
				if (var == 11)	B.tenW = stoi(datasegment);
				if (var == 12)	B.noballs = stoi(datasegment);
				if (var == 13)	B.BBI = (datasegment);
				if (var == 14)	B.bowlingstyle = (datasegment);
				if (var == 15)	B.notouts = stoi(datasegment);
				if (var == 16)	B.battingruns = stoi(datasegment);
				if (var == 17)	B.hs = stoi(datasegment);
				if (var == 18)	B.ballfaced = stoi(datasegment);
				if (var == 19)	B.hundreds = stoi(datasegment);
				if (var == 20)	B.fifties = stoi(datasegment);
				if (var == 21)	B.fours = stoi(datasegment);
				if (var == 22)	B.sixes = stoi(datasegment);
				if (var == 23)	B.catches = stoi(datasegment);
				if (var == 24)	B.battingstyle = (datasegment);
				if (var == 25)	B.stumps = stoi(datasegment);
				if (var == 26)	B.iccrank = stoi(datasegment);

			}
			P.push_back(B);
		}
		return fin;
	}
	friend istream& operator>>(istream& CIN, AllRounders& B)
	{
		print_str("Batting Stats", 1, 112);
		cout << '\n';
		cout << "Enter Name: ";
		getline(CIN, B.name);
		cout << "Matches Played: ";
		B.matches = getnonnegative();
		cout << "Innings Played: ";
		B.innings = getnonnegative();
		cout << "Enter Country: ";
		CIN >> B.country;
		CIN.ignore();
		cout << "Enter Role: ";
		getline(CIN, B.role);
		CIN.ignore();
		cout << "DOB (dd-mm-yyyy): ";
		B.dob = getValidDate();
		cout << "Debut (dd-mm-yyyy): ";
		B.debut = getValidDate();
		CIN.ignore();
		cout << "Enter Batting Style: ";
		getline(CIN, B.battingstyle);
		CIN.ignore();
		cout << "Not Outs: ";
		B.notouts = getnonnegative();
		cout << "Batting Runs: ";
		B.battingruns = getnonnegative();
		cout << "Highest Score: ";
		B.hs = getnonnegative();
		cout << "Ball Faced: ";
		B.ballfaced = getnonnegative();
		cout << "Hundreds: ";
		B.hundreds = getnonnegative();
		cout << "Fifties: ";
		B.fifties = getnonnegative();
		cout << "Fours: ";
		B.fours = getnonnegative();
		cout << "Sixes: ";
		B.sixes = getnonnegative();
		cout << "Catches: ";
		B.catches = getnonnegative();
		cout << "Stumps: ";
		B.stumps = getnonnegative();
		cout << "Dismissals: ";
		B.dismissals = getnonnegative();
		print_str("Bowling Stats", 1, 112);
		cout << '\n';
		cout << "Balls Bowled: ";
		B.ballsbowled = getnonnegative();
		cout << "Bowling Runs: ";
		B.bowlingruns = getnonnegative();
		cout << "Wickets: ";
		B.wickets = getnonnegative();
		cout << "Five W: ";
		B.fiveW = getnonnegative();
		cout << "Ten W: ";
		B.tenW = getnonnegative();
		cout << "No Balls: ";
		B.noballs = getnonnegative();
		cout << "Enter BBI (ww/rr): ";
		B.BBI = getValidBBI();
		cout << "Enter Bowling Style: ";
		getline(CIN, B.bowlingstyle);

		return CIN;
	}
};
class Teams
{//Abstract Class
protected:
	friend class Matches;
	string name;
	string coach;
	string captain;
	int wins, losses, draws;
	double ratio = wins / (wins + losses + draws);
	string teamXI[11];
public:

	Teams(string name, string coach, string captain,
		int wins, int losses, int draws, string teamXI[11])
	{
		this->name = name;
		this->coach = coach;
		this->captain = captain;
		this->wins = wins;
		this->losses = losses;
		this->draws = draws;
		this->ratio = (double)wins / (wins + losses + draws);
		for (int i = 0; i < 11; i++)
			this->teamXI[i] = teamXI[i];
	}
	virtual void reset() = 0;
	virtual void updatestats() = 0;


	string getname()
	{
		return name;
	}
	Teams()
	{
		name = "Nil";
		coach = "Nil";
		captain = "Nil";
		for (int i = 0; i < 11; i++)
			teamXI[i] = "Nil";
		wins = losses = draws = 0;
		ratio = 0;
	}
	~Teams()
	{
		//No as such destructor, as no dynamic memory allocation//
	}
};
class LocalTeams : public Teams
{
	int localcups;
public:
	LocalTeams(string name, string coach, string captain,
		int wins, int losses, int draws, string teamXI[11], int localcups)
		:Teams(name, coach, captain, wins, losses, draws, teamXI)
	{
		this->localcups = localcups;
	}

	LocalTeams()
		:Teams()
	{
		this->localcups = 0;
	}
	void reset()
	{
		name = "Nil";
		coach = "Nil";
		captain = "Nil";
		for (int i = 0; i < 11; i++)
			teamXI[i] = "Nil";
		wins = losses = draws = 0;
		ratio = 0;
		localcups = 0;
	}
	~LocalTeams()
	{
	}
	void updatestats()
	{
		cout << "1. Update Coach" << endl;
		cout << "2. Update Captain" << endl;
		cout << "3. Update Wins" << endl;
		cout << "4. Update Losses" << endl;
		cout << "5. Update Draws" << endl;
		cout << "6. Update LocalCups" << endl;
		cout << "7. Update TeamXI" << endl;
		int i = 0;
		cout << "Enter Number of the Stat: ";
		cin >> i;
		cin.ignore();
		cout << "Enter Updated Stat: \n";
		switch (i)
		{
		case 1: getline(cin, coach); break;
		case 2: getline(cin, captain); break;
		case 3: wins = getnonnegative(); break;
		case 4: losses = getnonnegative(); break;
		case 5: draws = getnonnegative(); break;
		case 6: localcups = getnonnegative(); break;
		case 7:
		{
			cin.ignore();
			cout << "Start Updating Names: \n";
			for (int k = 0; k < 11; k++)
				getline(cin, teamXI[k]);
			cin.ignore();
			break;
		}
		default:
			break;
		}

	}
	friend ifstream& operator>>(ifstream& fin, vector<LocalTeams>& LT)
	{
		string data;
		LocalTeams B;
		while (getline(fin, data))
		{
			if (data[0] == '}')
				break;
			int var = 0;
			for (int i = 0; data[i] != '\0'; i++, var++)
			{
				char datasegment[40] = "\0";
				int j = 0;
				for (j = 0; data[i] != '*'; j++, i++)
					datasegment[j] = data[i];
				datasegment[j] = '\0';
				if (var == 0) 	B.name = datasegment;
				if (var == 1)	B.coach = datasegment;
				if (var == 2)	B.captain = datasegment;
				if (var == 3)	B.wins = stoi(datasegment);
				if (var == 4)	B.losses = stoi(datasegment);
				if (var == 5)	B.draws = stoi(datasegment);
				if (var >= 6 && var <= 16) B.teamXI[var - 6] = datasegment;
				if (var == 17)	B.localcups = stoi(datasegment);
			}
			LT.push_back(B);
		}


		return fin;
	}
	friend istream& operator>>(istream& CIN, LocalTeams& LT)
	{
		char data[40] = "\0";
		cout << "Enter Name: ";
		CIN.getline(data, 40);
		LT.name = data;
		cout << "Enter Coach: ";
		CIN.getline(data, 40);
		LT.coach = data;
		cout << "Enter Captain: ";
		CIN.getline(data, 40);
		LT.captain = data;
		cout << "Enter Wins: ";
		LT.wins = getnonnegative();
		cout << "Enter Losses: ";
		LT.losses = getnonnegative();
		cout << "Enter Draws: ";
		LT.draws = getnonnegative();
		cout << "Enter Local Cups: ";
		LT.localcups = getnonnegative();
		CIN.ignore();
		cout << "Enter Team Members: \n";
		for (int i = 0; i < 11; i++)
		{
			CIN.getline(data, 40);
			LT.teamXI[i] = data;
		}
		cout << "Submit Record: ";
		CIN.ignore();
		return CIN;
	}
	friend ofstream& operator<<(ofstream& fout, vector<LocalTeams> LT)
	{
		for (int i = 0; i < LT.size(); i++)
		{
			fout << LT[i].name << "*" << LT[i].coach << "*" << LT[i].captain << "*" << LT[i].wins << "*" << LT[i].losses << "*"
				<< LT[i].draws << "*" << LT[i].teamXI[0] << "*" << LT[i].teamXI[1] << "*" << LT[i].teamXI[2] << "*" << LT[i].teamXI[3] << "*"
				<< LT[i].teamXI[4] << "*" << LT[i].teamXI[5] << "*" << LT[i].teamXI[6] << "*" << LT[i].teamXI[7] << "*" << LT[i].teamXI[8] << "*"
				<< LT[i].teamXI[9] << "*" << LT[i].teamXI[10] << "*" << LT[i].localcups << "*" << endl;
		}
		return fout;
	}
	friend ostream& operator<<(ostream& COUT, LocalTeams LT)
	{
		LT.ratio = (double)LT.wins / (LT.wins + LT.losses + LT.draws);

		print_str(LT.name, 1, 112, 0); COUT << endl;
		COUT << "Coach: " << LT.coach << endl;
		COUT << "Captain: " << LT.captain << endl;
		COUT << "Wins: " << LT.wins << endl;
		COUT << "Losses: " << LT.losses << endl;
		COUT << "Draws: " << LT.draws << endl;
		COUT << "Local Cups: " << LT.localcups << endl << endl;
		COUT << "Team Members:" << endl;

		for (int i = 0; i < 11; i++)
		{
			COUT << LT.teamXI[i];
			if (i <= 2)
				COUT << "\t(Top Order Batter)";
			if (i >= 3 && i <= 5)
				COUT << "\t(Middle Order Batter)";
			if (i >= 6 && i <= 8)
				COUT << "\t(All Rounder)";
			if (i > 8)
				COUT << "\t(Bowler)";
			COUT << endl;
		}
		return COUT;
	}
};
class InternationalTeams : public Teams
{
	string homeground;
	int WCups, iccRanking;
	string boardName;
public:
	InternationalTeams(string name, string coach, string captain,
		int wins, int losses, int draws, string teamXI[11], string homeground, int Wcups, int iccRanking, string boardName)
		:Teams(name, coach, captain, wins, losses, draws, teamXI)
	{
		this->homeground = homeground;
		this->WCups = Wcups;
		this->iccRanking = iccRanking;
		this->boardName = boardName;
	}
	InternationalTeams()
		:Teams()
	{
		this->homeground = "Nil";
		this->WCups = 0;
		this->iccRanking = 0;
		this->boardName = "Nil";
	}
	void reset()
	{
		name = "Nil";
		coach = "Nil";
		captain = "Nil";
		for (int i = 0; i < 11; i++)
			teamXI[i] = "Nil";
		wins = losses = draws = 0;
		ratio = 0;
		WCups = iccRanking = 0;
		boardName = "Nil";
		homeground = "Nil";
	}
	~InternationalTeams()
	{

	}
	void updatestats()
	{

		cout << "1. Update Coach" << endl;
		cout << "2. Update Captain" << endl;
		cout << "3. Update Wins" << endl;
		cout << "4. Update Losses" << endl;
		cout << "5. Update Draws" << endl;
		cout << "6. Update World Cups" << endl;
		cout << "7. Update TeamXI" << endl;
		int i = 0;
		cout << "Enter Number of the Stat: ";
		cin >> i;
		cin.ignore();
		cout << "Enter Updated Stat: \n";
		switch (i)
		{

		case 1: getline(cin, coach); break;
		case 2: getline(cin, captain); break;
		case 3: wins = getnonnegative(); break;
		case 4: losses = getnonnegative(); break;
		case 5: draws = getnonnegative(); break;
		case 6: WCups = getnonnegative(); break;
		case 7:
		{
			cin.ignore();
			cout << "Start Updating Names: \n";
			for (int k = 0; k < 11; k++)
				getline(cin, teamXI[k]);
			cin.ignore();
			break;
		}
		case 8: iccRanking = getnonnegative();
		default:
			break;
		}
	}
	friend istream& operator>>(istream& CIN, InternationalTeams& LT)
	{
		char data[40] = "\0";
		cout << "Enter Name: ";
		CIN.getline(data, 40);
		LT.name = data;
		cout << "Enter Coach: ";
		CIN.getline(data, 40);
		LT.coach = data;
		cout << "Enter Captain: ";
		CIN.getline(data, 40);
		LT.captain = data;
		cout << "Enter Wins: ";
		LT.wins = getnonnegative();
		cout << "Enter Losses: ";
		LT.losses = getnonnegative();
		cout << "Enter Draws: ";
		LT.draws = getnonnegative();
		cout << "Enter Homeground: ";
		CIN.getline(data, 40);
		LT.homeground = data;
		cout << "Enter Boardname: ";
		CIN.getline(data, 40);
		LT.boardName = data;
		cout << "Enter WCs: ";
		LT.WCups = getnonnegative();
		cout << "Enter ICC Rank: ";
		LT.iccRanking = getnonnegative();
		CIN.ignore();
		cout << "Enter Team Members: \n";
		for (int i = 0; i < 11; i++)
		{
			CIN.getline(data, 40);
			LT.teamXI[i] = data;
		}
		cout << "Submit Record: ";
		CIN.ignore();
		return CIN;
	}
	friend ofstream& operator<<(ofstream& fout, vector < InternationalTeams> LT)
	{
		for (int i = 0; i < LT.size(); i++)
		{
			fout << LT[i].name << "*" << LT[i].coach << "*" << LT[i].captain << "*" << LT[i].wins << "*" << LT[i].losses << "*"
				<< LT[i].draws << "*" << LT[i].teamXI[0] << "*" << LT[i].teamXI[1] << "*" << LT[i].teamXI[2] << "*" << LT[i].teamXI[3] << "*"
				<< LT[i].teamXI[4] << "*" << LT[i].teamXI[5] << "*" << LT[i].teamXI[6] << "*" << LT[i].teamXI[7] << "*" << LT[i].teamXI[8] << "*"
				<< LT[i].teamXI[9] << "*" << LT[i].teamXI[10] << "*" << LT[i].homeground << "*"
				<< LT[i].WCups << "*" << LT[i].iccRanking << "*" << LT[i].boardName << "*" << endl;
		}
		return fout;
	}
	friend ifstream& operator>>(ifstream& fin, vector<InternationalTeams>& LT)
	{
		string data;
		InternationalTeams B;
		while (getline(fin, data))
		{
			if (data[0] == '}')
				break;
			int var = 0;
			for (int i = 0; data[i] != '\0'; i++, var++)
			{
				char datasegment[40] = "\0";
				int j = 0;
				for (j = 0; data[i] != '*'; j++, i++)
					datasegment[j] = data[i];
				datasegment[j] = '\0';
				if (var == 0) 	B.name = datasegment;
				if (var == 1)	B.coach = datasegment;
				if (var == 2)	B.captain = datasegment;
				if (var == 3)	B.wins = stoi(datasegment);
				if (var == 4)	B.losses = stoi(datasegment);
				if (var == 5)	B.draws = stoi(datasegment);
				if (var >= 6 && var <= 16) B.teamXI[var - 6] = datasegment;
				if (var == 17)	B.homeground = (datasegment);
				if (var == 18)	B.WCups = stoi(datasegment);
				if (var == 19)	B.iccRanking = stoi(datasegment);
				if (var == 20)	B.boardName = (datasegment);

			}
			LT.push_back(B);
		}

		return fin;
	}
	friend ostream& operator<<(ostream& COUT, InternationalTeams LT)
	{
		LT.ratio = (double)LT.wins / (LT.wins + LT.losses + LT.draws);

		print_str(LT.name, 1, 112, 0);
		COUT << endl;
		COUT << "Coach: " << LT.coach << endl;
		COUT << "Board Name: " << LT.boardName << endl;
		COUT << "Captain: " << LT.captain << endl;
		COUT << "Wins: " << LT.wins << endl;
		COUT << "Losses: " << LT.losses << endl;
		COUT << "Draws: " << LT.draws << endl;
		COUT << "ICC Ranking: " << LT.iccRanking << endl;
		COUT << "WCups: " << LT.WCups << endl;
		COUT << "Homeground: " << LT.homeground << endl << endl;
		COUT << "Team Members:" << endl;
		for (int i = 0; i < 11; i++)
		{
			COUT << LT.teamXI[i];
			if (i <= 2)
				COUT << "\t(Top Order Batter)";
			if (i >= 3 && i <= 5)
				COUT << "\t(Middle Order Batter)";
			if (i > 6 && i <= 8)
				COUT << "\t(All Rounder)";
			if (i > 8)
				COUT << "\t(Bowler)";
			COUT << endl;
		}
		return COUT;
	}

};
vector <LocalTeams> LT;
vector <InternationalTeams> IT;
vector <Bowlers> BW;
vector <Batters> BT;
vector <AllRounders> AR;

class Matches {
	string toss, result, venue, date;
	int score[2];
	int wickets[2];
	string umpire1, umpire2, umpire3;
	Teams* T[2] = { nullptr, nullptr };

	int oversperinnings, innings;
	vector <char> data[4];
	bool test = false, limi = true;
	string team1, team2;
public:
	bool playing_status;
	Matches()
	{
		toss = "Nil";
		result = "Nil";
		venue = "Nil";
		score[0] = score[1] = wickets[0] = wickets[1] = 0;
		innings = 2, oversperinnings = 20;
		date = "01/01/1990";
		playing_status = 0;
		umpire1 = "Nil";
		umpire2 = "Nil";
		umpire3 = "Nil";
		test = 0;
		limi = 1;
	}
	void startMatch()
	{
		if (playing_status == 1)
		{
			cout << "Match already completed!!\n";
			_getch();
			return;
		}
		bool k = 0;
		do
		{
			cout << "TOSS: \n";
			cout << "\n0. " << T[0]->getname() << ", 1. " << T[1]->getname() << "\n";
			cout << "Select by Number: ";
			cin >> k;
			if (k == 0 || k == 1)
				break;
		} while (true);

		toss = T[k]->getname();
		playing_status = 1;

		for (int i = 0; i < innings; i++, k = !k)
		{
			string batter1 = T[k]->teamXI[0];
			string batter2 = T[k]->teamXI[1];
			string bowler = T[!k]->teamXI[9];
			int opt = 0;
			cout << "Press Enter to START innings# " << i + 1;
			int balls = 0;
			bool dec = 0;
			printdelivery(opt, balls, i);
			printscore(balls, score[k], wickets[k], i, batter1, batter2, bowler);
			while (true)
			{
				if (limi == true && wickets[k] == 10)
					break;
				if (test == true && wickets[k] == 20)
					break;
				if (limi == true && balls >= oversperinnings * 6)
					break;
				if (limi == true && score[k] > score[!k] && i == 1)
					break;
				if (dec == true && test == true)
					break;
				if (i == 3 && test == true && score[k] > score[!k])
					break;

				char c = _getch();
				switch (c)
				{
				case ENTER_KEY:
				{

					switch (opt)
					{
						if (balls % 6 == 0)
						{
							swap(batter1, batter2);
							int i = (balls / 6) % oversperinnings + 6;
							bowler = T[!k]->teamXI[i];
						}
					case 0:balls++; data[i].push_back('a');   break;
					case 1:balls++; score[k]++; data[i].push_back('b'); swap(batter1, batter2); break;
					case 2:balls++, score[k] += 2; data[i].push_back('c'); break;
					case 3:balls++, score[k] += 3; data[i].push_back('d'); swap(batter1, batter2); break;
					case 4:balls++, score[k] += 4; data[i].push_back('e'); break;
					case 5:balls++, score[k] += 6; data[i].push_back('f'); break;
					case 6:balls++; wickets[k]++; data[i].push_back('g'); break;
					case 7: if (limi == true) { score[k]++; data[i].push_back('h'); } break;
					case 8: if (limi == true) { score[k] += 2; data[i].push_back('i'); } break;
					case 9: if (limi == true) { score[k] += 3; data[i].push_back('j'); swap(batter1, batter2); }break;
					case 10:if (limi == true) { score[k] += 4; data[i].push_back('k'); } break;
					case 11:if (limi == true) { score[k] += 5; data[i].push_back('l'); swap(batter1, batter2); } break;
					case 12: break;
					case 13:score[k]++; data[i].push_back('m'); swap(batter1, batter2); break;
					case 14:score[k] += 2; data[i].push_back('n'); break;
					case 15:score[k] += 3; data[i].push_back('o'); swap(batter1, batter2); break;
					case 16:score[k] += 4; data[i].push_back('p'); break;
					case 17:score[k] += 6; data[i].push_back('q'); break;
					case 18:dec = true; data[i].push_back('r'); break;
					default:
						break;
					}
					printdelivery(opt, balls, i);
					printscore(balls, score[k], wickets[k], i, batter1, batter2, bowler);
					break;
				}
				case KEY_UP:
				{
					opt--;
					printdelivery(opt, balls, i);
					printscore(balls, score[k], wickets[k], i, batter1, batter2, bowler);
					break;
				}
				case KEY_DOWN:
				{
					opt++;
					printdelivery(opt, balls, i);
					printscore(balls, score[k], wickets[k], i, batter1, batter2, bowler);
					break;
				}
				default:
					break;
				}


			}
			_getch();
		}
		if (score[k] > score[!k])
		{
			result = T[k]->getname();
			cout << "Winner: " << result << endl;
			_getch();
		}
		else if (score[k] < score[!k])
		{
			result = T[!k]->getname();
			cout << "Winner: " << result << endl;
			_getch();
		}
		else
		{
			result = "Match Drawn";
			cout << "Winner: " << result << endl;
			_getch();
		}
	}
	string getname()
	{
		return team1 + " Vs. " + team2;
	}
	friend ostream& operator<<(ostream& COUT, Matches M)
	{
		if (M.playing_status == 0)
		{
			cout << "Match: " << M.team1 << " Vs. " << M.team2 << endl;
			cout << "Venue: " << M.venue << endl;
			cout << "Date: " << M.date << endl;
			cout << "Umpire-1: " << M.umpire1 << endl;
			cout << "Umpire-2: " << M.umpire2 << endl;
			cout << "Umpire-3: " << M.umpire3 << endl;
			cout << "Innings: " << M.innings << endl;
			cout << "Overs(per Inning): " << M.oversperinnings << endl;
		}
		else if (M.playing_status == 1)
		{
			cout << "Match: " << M.team1 << " Vs. " << M.team2 << endl;
			cout << "Venue: " << M.venue << endl;
			cout << "Date: " << M.date << endl;
			cout << "Umpire-1: " << M.umpire1 << endl;
			cout << "Umpire-2: " << M.umpire2 << endl;
			cout << "Umpire-3: " << M.umpire3 << endl;
			cout << "Innings: " << M.innings << endl;
			cout << "Overs(per Inning): " << M.oversperinnings << endl;
			cout << "Score-1: " << M.score[0] << endl;
			cout << "Score-2: " << M.score[1] << endl;
			cout << "Result: " << M.result << endl;
			print_str("Press any key to load ball-by-ball record", 1, 8, 1);
			_getch();

			for (int i = 0; i < M.innings; i++)
			{
				cout << "\nInnings# " << i + 1 << endl;
				for (int j = 0; j < M.data[i].size(); j++)
					cout << gettypeball(M.data[i][j]) << " ";
				cout << endl;
			}

		}
		return COUT;
	}
	friend ofstream& operator<<(ofstream& fout, const vector<Matches>& M) {
		for (const Matches& match : M) {
			fout << match.toss << '*'
				<< match.result << '*'
				<< match.venue << '*'
				<< match.date << '*'
				<< match.score[0] << '*'
				<< match.score[1] << '*'
				<< match.umpire1 << '*'
				<< match.umpire2 << '*'
				<< match.umpire3 << '*'
				<< match.oversperinnings << '*'
				<< match.innings << '*'
				<< match.test << '*'
				<< match.limi << '*'
				<< match.team1 << '*'
				<< match.team2 << '*'
				<< match.playing_status << '*';

			if (match.innings == 2) {
				fout.write(match.data[0].data(), match.data[0].size());
				fout << '*';
				fout.write(match.data[1].data(), match.data[1].size());
				fout << '*';
			}
			else if (match.innings == 4) {
				fout.write(match.data[0].data(), match.data[0].size());
				fout << '*';
				fout.write(match.data[1].data(), match.data[1].size());
				fout << '*';
				fout.write(match.data[2].data(), match.data[2].size());
				fout << '*';
				fout.write(match.data[3].data(), match.data[3].size());
				fout << '*';
			}

			fout << endl;
		}
		return fout;
	}
	friend istream& operator>>(istream& CIN, Matches& M)
	{

		int i, j;
		int k = 0;
		do
		{
			cout << "\n1. International Match, 2. Local Match\n";
			cout << "Select by Number: ";
			cin >> k;
			if (k == 1 || k == 2)
				break;
		} while (true);
		if (k == 1)
		{
			do
			{
				i = retname(IT);
				j = retname(IT);
				if (i != j && i != -1 && j != -1)
					break;
			} while (true);
			M.T[0] = new InternationalTeams(IT[i]);
			M.T[1] = new InternationalTeams(IT[j]);

		}
		else
		{
			do
			{
				i = retname(LT);
				j = retname(LT);
				if (i != j && i != -1 && j != -1)
					break;
			} while (true);
			M.T[0] = new LocalTeams(LT[i]);
			M.T[1] = new LocalTeams(LT[j]);

		}
		M.team1 = M.T[0]->getname();
		M.team2 = M.T[1]->getname();

		do
		{
			cout << "\n1. Limited, 2. Test\n";
			cout << "Select by Number: ";
			cin >> k;
			if (k == 1 || k == 2)
				break;
		} while (true);
		M.innings = k * 2;
		if (M.innings == 4)
			M.test = true;
		else
			M.limi = true;
		cout << "Enter Overs per Inning: ";
		M.oversperinnings = getnonnegative();
		M.date = getValidDate();
		cout << "Enter Umpire-1: ";
		cin >> M.umpire1;
		cout << "Enter Umpire-2: ";
		cin >> M.umpire2;
		cout << "Enter Umpire-3: ";
		cin >> M.umpire3;
		cout << "Enter Venue: ";
		cin >> M.venue;

		return CIN;
	}
	friend ifstream& operator>>(ifstream& fin, vector<Matches>& M) {
		string line;
		while (getline(fin, line)) {
			Matches match;
			size_t pos = 0;
			string token;
			int i = 0;

			while ((pos = line.find('*')) != string::npos) {
				token = line.substr(0, pos);
				line.erase(0, pos + 1);

				if (i == 0)
					match.toss = token;
				else if (i == 1)
					match.result = token;
				else if (i == 2)
					match.venue = token;
				else if (i == 3)
					match.date = token;
				else if (i == 4)
					match.score[0] = stoi(token);
				else if (i == 5)
					match.score[1] = stoi(token);
				else if (i == 6)
					match.umpire1 = token;
				else if (i == 7)
					match.umpire2 = token;
				else if (i == 8)
					match.umpire3 = token;
				else if (i == 9)
					match.oversperinnings = stoi(token);
				else if (i == 10)
					match.innings = stoi(token);
				else if (i == 11)
					match.test = (token == "1");
				else if (i == 12)
					match.limi = (token == "1");
				else if (i == 13)
					match.team1 = token;
				else if (i == 14)
					match.team2 = token;
				else if (i == 15)
					match.playing_status = (token == "1");
				else if (i >= 16 && i <= 19)
					match.data[i - 16].insert(match.data[i - 16].end(), token.begin(), token.end());

				i++;
			}

			M.push_back(match);
		}
		return fin;
	}


	~Matches()
	{

	}
};

vector <Matches> MT;