
//started at 15/11/2023 at 7:57PM//
#include <iostream>
#include <iomanip>
#include <string.h>
#include <string>
#include <cstring>
#include <cstdlib>
#include <windows.h>
#include <chrono>
#include <ctime>
#include <fstream>
#include <list>


using namespace std;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
TCHAR GetKey()
{
	INPUT_RECORD InputRecord;
	DWORD Writtten;
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	while (true)
	{
		ReadConsoleInputA(hStdIn, &InputRecord, 1, &Writtten);
		if (InputRecord.EventType == KEY_EVENT && InputRecord.Event.KeyEvent.bKeyDown) break;
	}
	char ASCII = InputRecord.Event.KeyEvent.uChar.AsciiChar;
	if (ASCII) return ASCII;
	return InputRecord.Event.KeyEvent.wVirtualKeyCode;
}

void printboard(char board[8][8], int turn);
void movepoint(char board[8][8]);

int i = 0;
void moveking(char board[8][8], int e1, int e2, int e3, int e4);
void movepawn(char board[8][8], int e1, int e2, int e3, int e4);
void movequeen(char board[8][8], int e1, int e2, int e3, int e4);
void moverook(char board[8][8], int e1, int e2, int e3, int e4);
void movebishop(char board[8][8], int e1, int e2, int e3, int e4);
void moveknight(char board[8][8], int e1, int e2, int e3, int e4);
bool checkmate(char board[8][8]);
void swapnreplace(char board[8][8], int e1, int e2, int e3, int e4);
void enpassant(char board[8][8], int e1, int e2, int e3, int e4);
void castling(char board[8][8], int e1, int e2, int e3, int e4);
bool safe(char board[8][8], int i, int k);
bool stalemate(char board[8][8]);
void previousgame(char board[8][8]);
void point_sender(char board[8][8], int e1, int e2, int e3, int e4);
bool validmove(char board[8][8], int m, int k);
void frontpage();
void legalcall(char board[8][8], int p, int q);
//Main Function//

int counter_white = 0;
int counter_black = 0;
bool o = false;
fstream fout;
int start_of_prog = time(NULL);
int timeB = 0;
int timeW = 0;
bool good_to_go = true;
bool retrieving = false;
bool chkmt = false;
bool stlmt = false;
bool rsnmt = false;
bool rznmt = false;
bool rapidmode = false;
bool blkmv = false;
bool whtmv = false;
char character;
int settimer = 0;
bool blitzmode = false;
bool lightenmode = false;

int main()
{

	frontpage();

	char board[8][8] =
	{
		{ 'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
		{ 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{ 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
		{ 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}
	};


	if (retrieving == true)
	{
		previousgame(board);
	}

	SetConsoleTextAttribute(h, 15);
	printboard(board, i);
	char choicing = '0';

	while (chkmt == false && stlmt == false && rsnmt == false && i <= 76)
	{

		blkmv = false;
		whtmv = false;

		checkmate(board);
		if (chkmt == true)
		{
			system("cls");
			printboard(board, i);

			if (character == 'K')
			{
				cout << "White has Lost the Game by Checkmate.\n";
			}
			else
			{
				cout << "Black has Lost the Game by Checkmate.\n";
			}
			Beep(600, 1000);
			return 0;
		}
		if (blitzmode == true || rapidmode == true)
		{
			if (i % 2 == 1)
			{
				timeB = timeB + (time(NULL) - start_of_prog);
				start_of_prog = time(NULL);
			}
			if (i % 2 == 0)
			{
				timeW = timeW + (time(NULL) - start_of_prog);
				start_of_prog = time(NULL);
			}
		}
		else if (lightenmode == true)
		{
			if (i % 2 == 1)
			{
				timeB = (time(NULL) - start_of_prog);
				start_of_prog = time(NULL);
			}
			if (i % 2 == 0)
			{
				timeW = (time(NULL) - start_of_prog);
				start_of_prog = time(NULL);
			}
			if (timeB >= 15)
			{
				Beep(600, 1000);
				break;
			}
			else if (timeW >= 15)
			{
				Beep(600, 1000);
				break;
			}

		}
		stalemate(board);
		if (stlmt == true)
		{
			system("cls");
			printboard(board, i);
			cout << "\nGAME ENDED WITH A DRAW\n";
			if (timeB > timeW)
			{
				cout << "\nWhite won the game by Time Advantage\n";
			}
			else
			{
				cout << "\nBlack won the game by Time Advantage\n";
			}
			Beep(600, 2000);
			return 0;
		}
		if (rapidmode == true && (timeB >= settimer || timeW >= settimer))
		{
			Beep(600, 1000);
			break;
		}
		cout << endl;
		{

			movepoint(board);
			if (rznmt == true)
			{
				break;
			}
			if (good_to_go == false)
			{
				system("cls");
				printboard(board, i);
				SetConsoleTextAttribute(h, 11);
				cout << "\n\n\nGame is now Closed and Steps have been Saved\n";
				SetConsoleTextAttribute(h, 7);
				fout.close();
				Beep(600, 100);
				return 0;
			}
			printboard(board, i);
		}
	}
	system("cls");
	printboard(board, i);
	if (i >= 76)
	{
		SetConsoleTextAttribute(h, 11);
		cout << "Game has ended with a Draw(0 Turns Left)\n";
		SetConsoleTextAttribute(h, 7);
	}
	if (rsnmt == true)
	{
		SetConsoleTextAttribute(h, 11);
		Beep(600, 100);
		cout << "Game Ended with a Handshake by ";
		if (i != 2 == 0)
		{
			cout << "White Side\n";
		}
		else
		{
			cout << "Black Side\n";
		}
		SetConsoleTextAttribute(h, 7);
	}
	if (rznmt == true)
	{
		SetConsoleTextAttribute(h, 11);
		Beep(600, 100);
		cout << "Game Ended with a Resignation from ";
		if (i != 2 == 0)
		{
			cout << "White Side\n";
		}
		else
		{
			cout << "Black Side\n";
		}
		SetConsoleTextAttribute(h, 7);

	}
	if ((rapidmode == true || blitzmode == true) && (timeB >= settimer || timeW >= settimer))
	{
		if (timeW >= settimer)
		{
			system("cls");
			SetConsoleTextAttribute(h, 11);
			cout << "Black Winner. White Time Ended\n";
			SetConsoleTextAttribute(h, 7);
			printboard(board, i);
		}
		else
		{
			system("cls");
			SetConsoleTextAttribute(h, 11);
			cout << "White Winner. Black Time Ended\n";
			SetConsoleTextAttribute(h, 7);
			printboard(board, i);
		}
	}
	if (lightenmode == true && (timeB >= 15 || timeW >= 15))
	{
		if (timeW >= 15)
		{
			system("cls");
			SetConsoleTextAttribute(h, 11);
			cout << "Black Winner. White ran Short\n";
			SetConsoleTextAttribute(h, 7);
			printboard(board, i);
		}
		else
		{
			system("cls");
			SetConsoleTextAttribute(h, 11);
			cout << "White Winner. Black ran Short\n";
			SetConsoleTextAttribute(h, 7);
			printboard(board, i);
		}
	}
	Beep(600, 1000);
	fout.close();
	return 0;
}

//Basic Function//

void movepoint(char board[8][8])
{
	string choicing1;

	bool condition = false;
	cout << endl;
	do
	{
		Beep(500, 100);
		cout << "Enter the choosen block and moved block(Press P to puase the Game, H to Handshake, R to Resign): ";
		getline(cin, choicing1);
		if (choicing1[0] >= 'a' && choicing1[0] <= 'h' && choicing1[1] >= '1' && choicing1[1] <= '8'
			&& choicing1[3] >= 'a' && choicing1[3] <= 'h' && choicing1[4] >= '1' && choicing1[4] <= '8'
			&& !(choicing1[0] == choicing1[3] && choicing1[1] == choicing1[4]))
		{
			Beep(500, 100);

			condition = true;
			break;
		}
		else
		{
			if (choicing1 == "p" || choicing1 == "P")
			{
				Beep(500, 100);
				good_to_go = false;
				condition = true;
				fout.close();
				return;
			}
			else
			{
				if (choicing1 == "h" || choicing1 == "H")
				{
					Beep(500, 100);

					cout << "\nPlayer ";
					if (i % 2 == 0) { cout << "Black. "; }
					else { cout << "White. "; }
					cout << "Would you like to HandShake(y/n)?";
					char choice;
					cin >> choice;
					if (choice == 'Y' || choice == 'y')
					{
						rsnmt = true;
						system("cls");
						cout << "Handshake Accepted";
						return;
					}
					else
					{
						system("cls");
						SetConsoleTextAttribute(h, 4);
						cout << "HandShake Rejected\n";
						SetConsoleTextAttribute(h, 7);
						return;
					}
				}
				else
				{
					if (choicing1 == "r" || choicing1 == "R")
					{
						rznmt = true;
						system("cls");
						if (i % 2 == 0)
							cout << "White has resigned. Black is the Winner.\n";
						else
							cout << "Black has resigned. White is the Winner.\n";
						return;
					}
					else
					{
						if (i == 0)
						{
							SetConsoleTextAttribute(h, 11);
							cout << "Good to Go\n";
							SetConsoleTextAttribute(h, 7);
							i += 2;
							condition = false;
						}
						else
						{
							SetConsoleTextAttribute(h, 12);
							cout << "Invalid Option Selection\n";
							SetConsoleTextAttribute(h, 7);
							condition = false;
						}
					}
				}
			}
		}
	} while (condition == false);
	int e2 = choicing1[0] - 97;
	int e1 = choicing1[1] - 49;
	int e4 = choicing1[3] - 97;
	int e3 = choicing1[4] - 49;

	point_sender(board, e1, e2, e3, e4);
}
void previousgame(char board[8][8])
{
	char selection;

	do {
		cout << "\nLoad Instantly (L)\nLoad with Replay (R)\n";
		cout << "Select one: ";
		cin >> selection;
	} while (selection != 'L' && selection != 'R' && selection != 'l' && selection != 'r');
	cout << "Press Any Key to Start Game Play";
	GetKey();


	static int last_move1, last_move2;
	char move[6];
	while (fout.getline(move, 6))
	{
		if (move[0] >= 65)
		{
			board[last_move1][last_move2] = move[0];
			system("cls");
		}
		else
		{
			int e1 = move[1] - 48;
			int e2 = move[2] - 48;
			int e3 = move[3] - 48;
			int e4 = move[4] - 48;
			last_move1 = e3;
			last_move2 = e4;
			system("cls");
			point_sender(board, e1, e2, e3, e4);

		}
		if (selection == 'R' || selection == 'r')
		{
			printboard(board, i);
			Sleep(1000);
			Beep(500, 100);
		}
	}
	fout.ignore();
	system("cls");
}
void printboard(char board[8][8], int turn)
{
	int color = 112;
	cout << "      ";
	int n = 10;
	int m = 177;
	cout << setw(40);
	for (char i = 97; i <= 'h'; i++)
	{
		if (i == 'h')
		{
			cout << i;
		}
		else
		{
			cout << i << setw(n);
		}
	}

	cout << endl << " ";
	cout << setw(40);
	for (int k = 0; k <= 80; k++)
	{
		cout << char(m);
	}
	cout << setw(53) << "Resignation Status: ";
	{
		if (rznmt == false)
		{
			SetConsoleTextAttribute(h, 11);
			cout << "Not Found";
			SetConsoleTextAttribute(h, 7);
		}
		else
		{
			SetConsoleTextAttribute(h, 4);
			cout << "(Winner: ";
			if (i % 2 == 0)
			{
				cout << "Black)";
			}
			else
			{
				cout << "White)";
			}
			SetConsoleTextAttribute(h, 7);
		}
	}
	cout << endl;

	for (int l = 7; l >= 0; l--)
	{

		cout << setw(41);
		for (int k = 0; k <= 8; k++)
		{
			cout << char(m);
			if (k != 8)
			{
				if ((l % 2 == 1 && k % 2 == 0) || (l % 2 == 0 && k % 2 == 1))
				{
					SetConsoleTextAttribute(h, color);
					cout << "         ";
					SetConsoleTextAttribute(h, 7);
				}
				else
				{
					cout << "         ";
				}
			}
		}


		if (l == 2)
		{
			SetConsoleTextAttribute(h, 6);
			if (i == 0)
			{
				cout << setw(58) << "Turns Left(Unless Draw): " << 75;
			}
			else
			{
				cout << setw(58) << "Turns Left(Unless Draw): " << 77 - i;
			}
			SetConsoleTextAttribute(h, 7);
		}
		if (l == 7)
		{
			cout << setw(51) << "Handshake Status: ";
			if (rsnmt == 0)
			{
				SetConsoleTextAttribute(h, 11);
				cout << "No";
				SetConsoleTextAttribute(h, 7);
			}
			else
			{
				SetConsoleTextAttribute(h, 12);
				if (i % 2 == 0)
				{
					cout << "Found(By White)";
				}
				else cout << "Found(By Black)";
				SetConsoleTextAttribute(h, 7);
			}
		}
		if (l == 3)
		{
			cout << setw(43) << "N-->KNIGHT";
		}
		if (l == 4)
		{
			cout << setw(41) << "P-->PAWN";
		}
		if (l == 6 && stlmt == false)
		{
			cout << setw(56) << "Black-->Small Alphabets";
		}
		if (l == 1)
		{
			SetConsoleTextAttribute(h, 11);
			cout << setw(47) << "Time(White): " << timeW << "s";//
			SetConsoleTextAttribute(h, 7);
		}
		cout << setw(40);
		cout << endl << l + 1;
		for (int k = 0; k <= 8; k++)
		{
			cout << char(m);
			if (k != 8)
			{
				if ((l % 2 == 0 && k % 2 == 1) || (l % 2 == 1 && k % 2 == 0))
				{
					SetConsoleTextAttribute(h, color);
					cout << "    ";
					{
						cout << board[l][k];
					}
					cout << "    ";
					SetConsoleTextAttribute(h, 7);
				}
				else
				{
					cout << "    ";
					cout << board[l][k];
					cout << "    ";
				}
			}
		}
		cout << l + 1;


		if (l == 1)
		{
			SetConsoleTextAttribute(h, 11);
			cout << setw(46) << "Time(Black): " << timeB << "s";////
			SetConsoleTextAttribute(h, 7);
		}


		if (l == 4)
		{
			cout << setw(42) << "B-->BISHOP";
		}
		if (l == 6 && stlmt == false)
		{
			cout << setw(57) << "White-->Capital Alphabets";
		}
		if (l == 7)
		{
			cout << setw(50) << "Checkmate Status: ";
			if (chkmt == 0)
			{
				SetConsoleTextAttribute(h, 11);
				cout << "Not Found";
				SetConsoleTextAttribute(h, 7);
			}
			else
			{
				SetConsoleTextAttribute(h, 12);
				cout << "Winner (Found)";

				SetConsoleTextAttribute(h, 7);
			}
		}
		cout << endl << " ";
		cout << setw(40);
		for (int k = 0; k <= 8; k++)
		{
			cout << char(m);
			if (k != 8)
			{
				if ((l % 2 == 1 && k % 2 == 0) || (l % 2 == 0 && k % 2 == 1))
				{
					SetConsoleTextAttribute(h, color);
					cout << "         ";
					SetConsoleTextAttribute(h, 7);
				}
				else
				{
					cout << "         ";
				}
			}
		}

		if (l == 7)
		{
			cout << setw(51) << "Stalemate Status: ";
			if (stlmt == 0)
			{
				SetConsoleTextAttribute(h, 11);
				cout << "Not Found";
				SetConsoleTextAttribute(h, 7);
			}
			else
			{
				SetConsoleTextAttribute(h, 12);
				if (i % 2 == 0)
				{
					cout << "Found(White)";
				}
				else cout << "Found(Black)";
				SetConsoleTextAttribute(h, 7);
			}
		}
		if (l == 4)
		{
			cout << setw(41) << "K-->KING";
		}
		if (l == 3)
		{
			SetConsoleTextAttribute(h, 14);
			if (turn % 2 == 1 && stlmt == false)
			{
				cout << setw(45) << "TURN-->BLACK";
			}
			else if (turn % 2 == 0 && stlmt == false)
			{
				cout << setw(45) << "TURN-->WHITE";
			}
			SetConsoleTextAttribute(h, 7);
		}
		cout << endl << " ";

		cout << setw(40);
		for (int k = 0; k <= 80; k++)
		{
			cout << char(m);
		}

		if (l == 4)
		{
			cout << setw(42) << "Q-->QUEEN";
		}
		cout << endl;
	}

	cout << "      ";
	cout << setw(40);
	for (char i = 97; i <= 'h'; i++)
	{
		if (i == 'h')
		{
			cout << i;
		}
		else
		{
			cout << i << setw(n);
		}
	}
	cout << endl;
}

//Moving Functions//

void moveking(char board[8][8], int e1, int e2, int e3, int e4)
{
	int diff1 = e3 - e1;
	int diff2 = e4 - e2;

	if (diff1<2 && diff2<2 && diff2>-2 && diff1>-2)
	{
		if (board[e1][e2] <= 'Z' && board[e1][e2] >= 'A' && board[e3][e4] <= 'Z' && board[e3][e4] >= 'A')
		{
			system("cls");
			SetConsoleTextAttribute(h, 12);
			cout << setw(90) << "YOU CANNOT KILL YOUR OWN PIECE\n" << endl;
			SetConsoleTextAttribute(h, 7);
			return;
		}
		else if (board[e1][e2] <= 'z' && board[e1][e2] >= 'a' && board[e3][e4] <= 'z' && board[e3][e4] >= 'a')
		{
			system("cls");
			SetConsoleTextAttribute(h, 12);
			cout << setw(90) << "YOU CANNOT KILL YOUR OWN PIECE\n" << endl;
			SetConsoleTextAttribute(h, 7);
			return;
		}
		else
		{
			if (board[e1][e2] == 'K' && board[e3][e4] != 'B' && board[e3][e4] != 'P' && board[e3][e4] != 'N' && board[e3][e4] != 'R' && board[e3][e4] != 'Q')
			{
				if (validmove(board, e3, e4) == false)
				{
					swapnreplace(board, e1, e2, e3, e4);
				}
				else
				{
					system("cls");
					SetConsoleTextAttribute(h, 12);
					cout << "The Selected Position is on Check" << endl;
					SetConsoleTextAttribute(h, 7);
				}
			}
			else if (board[e1][e2] == 'k' && board[e3][e4] != 'b' && board[e3][e4] != 'p' && board[e3][e4] != 'n' && board[e3][e4] != 'r' && board[e3][e4] != 'q')
			{
				if (validmove(board, e3, e4) == false)
				{
					swapnreplace(board, e1, e2, e3, e4);
				}
				else
				{
					system("cls");
					SetConsoleTextAttribute(h, 12);
					cout << "The Selected Position is on Check" << endl;
					SetConsoleTextAttribute(h, 7);
				}
			}
		}
	}
	//Castling Check//
	else
	{
		if (fabs(diff2) >= 2 && diff1 == 0)
		{
			if (board[e1][e2] == 'K' && counter_white == 0)
			{
				castling(board, e1, e2, e3, e4);
			}
			else if (board[e1][e2] == 'k' && counter_black == 0)
			{
				castling(board, e1, e2, e3, e4);
			}
			else
			{
				system("cls");

				SetConsoleTextAttribute(h, 12);
				cout << setw(90) << "KING/ROOK HAS(HAVE) ALREADY MOVED, CASTLING IS NOT POSSIBLE\n" << endl;
				SetConsoleTextAttribute(h, 7);
				return;
			}
		}
		else
		{
			system("cls");

			SetConsoleTextAttribute(h, 12);
			cout << setw(90) << "OUT OF RANGE OF KING\n" << endl;
			SetConsoleTextAttribute(h, 7);
			return;
		}
	}
}
void moverook(char board[8][8], int e1, int e2, int e3, int e4)
{
	int diff1 = (e3 - e1);
	int diff2 = (e4 - e2);

	if ((diff1 != 0 && diff2 == 0) || ((diff1 == 0 && diff2 != 0)))
	{
		if (board[e1][e2] <= 'Z' && board[e1][e2] >= 'A' && board[e3][e4] <= 'Z' && board[e3][e4] >= 'A')
		{
			system("cls");

			SetConsoleTextAttribute(h, 12);
			cout << setw(90) << "YOU CANNOT KILL YOUR OWN PIECE\n" << endl;

			SetConsoleTextAttribute(h, 7);
			return;
		}
		if (board[e1][e2] <= 'z' && board[e1][e2] >= 'a' && board[e3][e4] <= 'z' && board[e3][e4] >= 'a')
		{
			system("cls");

			SetConsoleTextAttribute(h, 12);
			cout << setw(90) << "YOU CANNOT KILL YOUR OWN PIECE\n" << endl;

			SetConsoleTextAttribute(h, 7);
			return;
		}
		bool is_present = true;

		if (diff1 != 0)
		{
			diff1 = diff1 / fabs(diff1);
		}
		if (diff2 != 0)
		{
			diff2 = diff2 / fabs(diff2);
		}

		int j = e1, k = e2;


		if (diff1 != 0)
		{
			j += diff1;
			while (j != e3)
			{
				if (board[j][e4] != ' ')
				{
					is_present = false;
				}
				j += diff1;
			}
		}
		else
		{
			if (diff2 != 0)
			{
				k += diff2;
				while (k != e4)
				{
					if (board[e3][k] != ' ')
					{
						is_present = false;
					}
					k += diff2;
				}
			}
		}

		if (is_present == true)
		{
			swapnreplace(board, e1, e2, e3, e4);
		}
		else
		{
			system("cls");

			SetConsoleTextAttribute(h, 12);
			cout << setw(90) << "ROOK CANNOT HOVER OVER PIECES\n" << endl;

			SetConsoleTextAttribute(h, 7);
			return;
		}
	}
	else
	{
		system("cls");
		SetConsoleTextAttribute(h, 12);
		cout << setw(90) << "OUT OF RANGE OF ROOK\n" << endl;
		SetConsoleTextAttribute(h, 7);
		return;
	}
}
void movebishop(char board[8][8], int e1, int e2, int e3, int e4)
{
	int diff1 = (e3 - e1);
	int diff2 = (e4 - e2);

	if (diff1 != 0 && diff2 != 0 && fabs(diff1) == fabs(diff2))
	{
		if ((board[e1][e2] >= 'A' && board[e1][e2] <= 'Z') && (board[e3][e4] >= 'A' && board[e3][e4] <= 'Z'))
		{
			system("cls");

			SetConsoleTextAttribute(h, 12);
			cout << setw(90) << "YOU CANNOT KILL YOUR OWN PIECE\n" << endl;
			SetConsoleTextAttribute(h, 7);
			return;
		}
		if ((board[e1][e2] >= 'a' && board[e1][e2] <= 'z') && (board[e3][e4] >= 'a' && board[e3][e4] <= 'z'))
		{
			system("cls");
			SetConsoleTextAttribute(h, 12);
			cout << setw(90) << "YOU CANNOT KILL YOUR OWN PIECE\n" << endl;
			SetConsoleTextAttribute(h, 7);
			return;
		}

		bool is_present = true;
		int j = e1;
		int k = e2;

		if (diff1 != 0)
			diff1 = (diff1 / (fabs(diff1)));
		if (diff2 != 0)
			diff2 = (diff2 / (fabs(diff2)));


		if (diff1 != diff2)
		{
			j -= diff2;
			k -= diff1;
			while (j != e3 || k != e4)
			{
				if (board[j][k] != ' ')
				{
					is_present = false;
					break;
				}
				j -= diff2;
				k -= diff1;
			}
		}
		else if (diff1 == diff2)
		{
			j += diff2;
			k += diff1;
			while (j != e3 || k != e4)
			{
				if (board[j][k] != ' ')
				{
					is_present = false;
					break;
				}
				j += diff2;
				k += diff1;
			}
		}

		if (is_present == true)
		{
			swapnreplace(board, e1, e2, e3, e4);
		}
		else
		{
			system("cls");

			SetConsoleTextAttribute(h, 12);
			cout << setw(90) << "BISHOP CANNOT HOVER OVER PIECES\n" << endl;

			SetConsoleTextAttribute(h, 7);
			return;
		}
	}
	else
	{
		system("cls");

		SetConsoleTextAttribute(h, 12);
		cout << setw(90) << "OUT OF RANGE OF BISHOP\n" << endl;

		SetConsoleTextAttribute(h, 12);
		return;
	}


}
void moveknight(char board[8][8], int e1, int e2, int e3, int e4)
{
	int diff1 = (e1 - e3);
	int diff2 = (e2 - e4);
	int l = fabs(diff1);
	int j = fabs(diff2);

	if ((fabs(diff1) == 2 && fabs(diff2) == 1 || fabs(diff1) == 1 && fabs(diff2) == 2))
	{
		if ((board[e1][e2] >= 'A' && board[e1][e2] <= 'Z') && (board[e3][e4] >= 'A' && board[e3][e4] <= 'Z'))
		{
			system("cls");

			SetConsoleTextAttribute(h, 12);
			cout << setw(90) << "YOU CANNOT KILL YOUR OWN PIECE\n" << endl;

			SetConsoleTextAttribute(h, 7);
			return;
		}
		else
			if ((board[e1][e2] >= 'a' && board[e1][e2] <= 'z') && (board[e3][e4] >= 'a' && board[e3][e4] <= 'z'))
			{
				system("cls");

				SetConsoleTextAttribute(h, 12);
				cout << setw(90) << "YOU CANNOT KILL YOUR OWN PIECE\n" << endl;

				SetConsoleTextAttribute(h, 7);
				return;
			}
			else
				swapnreplace(board, e1, e2, e3, e4);
	}
	else
	{
		system("cls");

		SetConsoleTextAttribute(h, 12);
		cout << setw(90) << "OUT OF THE RANGE OF KNIGHT\n" << endl;

		SetConsoleTextAttribute(h, 7);
		return;
	}
}
void movequeen(char board[8][8], int e1, int e2, int e3, int e4)
{
	int diff1 = (e3 - e1);
	int diff2 = (e4 - e2);
	int l = fabs(diff1);
	int j = fabs(diff2);

	if (l == j || (diff1 != 0 && diff2 == 0) || (diff1 == 0 && diff2 != 0))
	{
		if ((board[e1][e2] >= 'A' && board[e1][e2] <= 'Z') && (board[e3][e4] >= 'A' && board[e3][e4] <= 'Z'))
		{
			system("cls");
			SetConsoleTextAttribute(h, 12);
			cout << setw(90) << "YOU CANNOT KILL YOUR OWN PIECE\n" << endl;
			SetConsoleTextAttribute(h, 7);
			return;
		}
		if ((board[e1][e2] >= 'a' && board[e1][e2] <= 'z') && (board[e3][e4] >= 'a' && board[e3][e4] <= 'z'))
		{
			system("cls");
			SetConsoleTextAttribute(h, 12);
			cout << setw(90) << "YOU CANNOT KILL YOUR OWN PIECE\n" << endl;
			SetConsoleTextAttribute(h, 7);
			return;
		}
		bool is_present = true;
		int j = e1;
		int k = e2;

		if (diff1 != 0)
			diff1 = diff1 / (fabs(diff1));
		if (diff2 != 0)
			diff2 = diff2 / (fabs(diff2));

		{//QUEEN CHECKS//
			if (diff1 != diff2 && !(diff1 != 0 && diff2 == 0) && !(diff2 != 0 && diff1 == 0))
			{
				j -= diff2;
				k -= diff1;
				while (j != e3 || k != e4)
				{
					if (board[j][k] != ' ')
					{
						is_present = false;
						break;
					}
					j -= diff2;
					k -= diff1;
				}
			}
			else
				if (diff1 == diff2)
				{
					j += diff2;
					k += diff1;
					while (j != e3 || k != e4)
					{
						if (board[j][k] != ' ')
						{
							is_present = false;
							break;
						}
						j += diff2;
						k += diff1;
					}
				}
				else
					if (diff1 != 0 && diff2 == 0)
					{
						j += diff1;
						while (j != e3)
						{
							if (board[j][e4] != ' ')
							{
								is_present = false;
							}
							j += diff1;
						}
					}
					else
						if (diff2 != 0 && diff1 == 0)
						{
							k += diff2;
							while (k != e4)
							{
								if (board[e3][k] != ' ')
								{
									is_present = false;
								}
								k += diff2;
							}
						}
		}

		if (is_present == true)
		{
			swapnreplace(board, e1, e2, e3, e4);
		}
		else
		{
			system("cls");

			SetConsoleTextAttribute(h, 12);
			cout << setw(90) << "QUEEN CANNOT COVER OVER PIECES\n" << endl;
			SetConsoleTextAttribute(h, 7);
			return;
		}
	}
	else
	{
		system("cls");

		SetConsoleTextAttribute(h, 12);
		cout << setw(90) << "OUT OF THE RANGE OF QUEEN\n" << endl;

		SetConsoleTextAttribute(h, 7);
		return;
	}

}
void movepawn(char board[8][8], int e1, int e2, int e3, int e4)
{
	int diff1 = e3 - e1;
	int diff2 = e4 - e2;

	bool firstpawn = false;


	if ((board[e1][e2] >= 'A' && board[e1][e2] <= 'Z') && (board[e3][e4] >= 'A' && board[e3][e4] <= 'Z'))
	{
		system("cls");
		SetConsoleTextAttribute(h, 12);
		cout << setw(90) << "YOU CANNOT KILL YOUR OWN PIECE\n" << endl;
		SetConsoleTextAttribute(h, 7);
		return;
	}
	else if ((board[e1][e2] >= 'a' && board[e1][e2] <= 'z') && (board[e3][e4] >= 'a' && board[e3][e4] <= 'z'))
	{
		system("cls");
		SetConsoleTextAttribute(h, 12);
		cout << setw(90) << "YOU CANNOT KILL YOUR OWN PIECE\n" << endl;
		SetConsoleTextAttribute(h, 7);
		return;
	}
	else
	{

		//pawn promotion//
		if ((e3 == 0 && board[e1][e2] == 'p') || (e3 == 7 && board[e1][e2] == 'P'))
		{
			if ((board[e3][e4] == ' ') || (board[e3][e4] != ' ' && fabs(diff1) == 1))
			{
				char choice = 'k';
				bool yes = false;
				do
				{
					if (retrieving == false)
					{
						cout << "\nQ-->Queen\nB-->Bishop\nK-->Knight\nR-->Rook\n(Your Pawn has been Promoted, Small for White, Capital for Black)Enter the first alphabet: ";
						cin >> choice;
					}
					else choice = '.';
					if (board[e1][e2] == 'p' && (choice == 'q' || choice == 'r' || choice == 'b' || choice == 'n' || choice == '.'))
					{
						board[e1][e2] = choice;
						swap(board[e1][e2], board[e3][e4]);
						board[e1][e2] = ' ';
						yes = true;
						if (retrieving == false)
						{
							fout << " " << e1 << e2 << e3 << e4 << '\n';
							fout << choice << endl;
						}
						system("cls");
						if (rapidmode == true)
						{
							if (i % 2 == 1)
							{
								timeW -= 10;
							}
							else
							{
								if (i % 2 == 0)
								{
									timeB -= 10;
								}
							}
						}
						i++;
					}
					else
					{
						if (board[e1][e2] == 'P' && (choice == 'Q' || choice == 'R' || choice == 'B' || choice == 'N' || choice == '.'))
						{
							board[e1][e2] = choice;
							swap(board[e1][e2], board[e3][e4]);
							board[e1][e2] = ' ';
							yes = true;
							if (retrieving == false)
							{
								fout << " " << e1 << e2 << e3 << e4 << '\n';
								fout << choice << endl;

							}
							system("cls");
							if (rapidmode == true)
							{
								if (i % 2 == 1)
								{
									timeW -= 10;
								}
								else
								{
									if (i % 2 == 0)
									{
										timeB -= 10;
									}
								}
							}
							i++;
						}
					}
				} while (yes == false);
			}
		}

		else
		{
			if (board[e1][e2] == 'p')
			{
				//pawn move-->2 Steps//
				if (e1 == 6 && diff1 == -2 && diff2 == 0 && board[e3][e4] == ' ' && board[e1 - 1][e2] == ' ' && board[e3][e4] == ' ')
				{
					swapnreplace(board, e1, e2, e3, e4);
				}
				else
				{
					//pawn move-->1 Steps//
					if (diff1 == -1 && fabs(diff2) == 0 && board[e3][e4] == ' ')
					{
						swapnreplace(board, e1, e2, e3, e4);
					}
					//pawn capture//
					else if (diff1 == -1 && fabs(diff2) == 1 && board[e3][e4] != ' ')
					{
						swapnreplace(board, e1, e2, e3, e4);
					}
					//en passant//
					else if (diff1 == -1 && fabs(diff2) == 1 && board[e3][e4] == ' ' && e1 == 3)
					{
						enpassant(board, e1, e2, e3, e4);
					}

					else
					{
						system("cls");
						SetConsoleTextAttribute(h, 12);
						cout << setw(90) << "Not in Pawn's Range\n" << endl;
						SetConsoleTextAttribute(h, 7);
						return;

					}
				}
			}
			else
			{
				if (board[e1][e2] == 'P')
				{
					if (diff1 == 2 && e1 == 1 && diff2 == 0 && board[e1 + 1][e2] == ' ' && board[e3][e4] == ' ')
					{
						swapnreplace(board, e1, e2, e3, e4);
					}
					else
					{
						if (diff1 == 1 && diff2 == 0 && board[e3][e4] == ' ' && board[e1 + 1][e2] == ' ')
						{
							swapnreplace(board, e1, e2, e3, e4);
						}
						//pawn capture//
						else if (diff1 == 1 && fabs(diff2) == 1 && board[e3][e4] != ' ')
						{
							swapnreplace(board, e1, e2, e3, e4);
						}
						//en passant//
						else if (diff1 == 1 && (diff2 == 1 || diff2 == -1) && board[e3][e4] == ' ' && e1 == 4)
						{

							enpassant(board, e1, e2, e3, e4);
						}
						//
						else
						{
							system("cls");
							SetConsoleTextAttribute(h, 12);
							cout << setw(90) << "Not in Pawn's Range\n" << endl;
							SetConsoleTextAttribute(h, 7);
							return;
						}
					}
				}
				else
				{
					system("cls");
					SetConsoleTextAttribute(h, 12);
					cout << setw(90) << "Invalid move\n" << endl;
					SetConsoleTextAttribute(h, 7);
					return;
				}
			}
		}
	}
}

//Special Functions//

void swapnreplace(char board[8][8], int e1, int e2, int e3, int e4)
{
	if (board[e3][e4] == 'k' || board[e3][e4] == 'K')
	{
		chkmt = true;
		character = board[e3][e4];
		system("cls");
	}
	else {

		swap(board[e1][e2], board[e3][e4]);
		board[e1][e2] = ' ';
		system("cls");
		if (rapidmode == true)
		{
			if (i % 2 == 1)
			{
				timeW -= 10;
			}
			else
			{
				if (i % 2 == 0)
				{
					timeB -= 10;
				}
			}
		}
		i++;
		SetConsoleTextAttribute(h, 11);
		if (retrieving == false)
		{
			fout << " " << e1 << e2 << e3 << e4 << endl;
		}
		//Chess Remarks-->1st Class Artificial Intelligence//
		if (i % 5 == 0)
		{
			cout << setw(90) << "Excellent Move\n";
		}
		if (i % 5 == 1)
		{
			cout << setw(90) << "Outstanding Move\n";
		}
		if (i % 5 == 2)
		{
			cout << setw(90) << "Nice Move\n";
		}
		if (i % 5 == 3)
		{
			cout << setw(90) << "Critical Move\n";
		}
		if (i % 5 == 4)
		{
			cout << setw(90) << "Incredible Move\n";
		}
		cout << endl;
	}
	SetConsoleTextAttribute(h, 7);
}
void castling(char board[8][8], int e1, int e2, int e3, int e4)
{
	int diff1 = e3 - e1;
	int diff2 = e4 - e2;

	diff2 = (diff2 / fabs(diff2));
	int j = e2;
	bool present = true;

	if (board[e1][e2] == 'K' && (board[e3][e4] == ' ' || board[e3][e4] == 'R') && counter_white == 0 && (board[0][0] == 'R' || board[0][7] == 'R'))
	{
		j += diff2;
		while (j != e4)
		{
			if (board[e1][j] != ' ')
			{
				present = false;
			}
			j += diff2;
		}

		if (present == true)
		{
			if (validmove(board, e1, e2 + diff2 + diff2) == false)
			{
				swap(board[e1][e2], board[e1][e2 + diff2 + diff2]);
				board[e1][e2 + diff2] = 'R';
				system("cls");
				if (retrieving == false)
				{
					fout << " " << e1 << e2 << e3 << e4 << '\n';
				}
				i++;
				if (diff2 == -1)
				{
					board[0][0] = ' ';
				}
				else
				{
					board[0][7] = ' ';
				}
				SetConsoleTextAttribute(h, 7);
				cout << setw(90) << "CASTLING BY WHITE KING\n";
				SetConsoleTextAttribute(h, 7);
				return;
			}
			else
			{
				system("Cls");
				SetConsoleTextAttribute(h, 12);
				cout << "White King is in Check" << endl;
				SetConsoleTextAttribute(h, 7);
				return;
			}
		}
		else
		{
			system("cls");
			SetConsoleTextAttribute(h, 12);
			cout << setw(90) << "Invalid move\n" << endl;
			SetConsoleTextAttribute(h, 7);
			return;
		}
	}
	else
		if (board[e1][e2] == 'k' && (board[e3][e4] == ' ' || board[e3][e4] == 'r') && counter_black == 0 && (board[7][7] == 'r' || board[7][0] == 'r'))
		{
			j += diff2;
			while (j != e4)
			{
				if (board[e1][j] != ' ')
				{
					present = false;
				}
				j += diff2;
			}

			if (present == true)
			{
				if (validmove(board, e1, e2 + diff2 + diff2) == false)
				{
					swap(board[e1][e2], board[e1][e2 + diff2 + diff2]);
					board[e1][e2 + diff2] = 'r';
					system("cls");
					if (retrieving == false)
					{
						fout << " " << e1 << e2 << e3 << e4 << '\n';
					}

					i++;
					if (diff2 == -1)
					{
						board[7][0] = ' ';
					}
					else
					{
						board[7][7] = ' ';
					}
					SetConsoleTextAttribute(h, 7);
					cout << setw(90) << "CASTLING BY BLACK KING\n";
					SetConsoleTextAttribute(h, 7);
					return;
				}
				else
				{
					system("Cls");
					SetConsoleTextAttribute(h, 12);
					cout << "Black King is in Check" << endl;
					SetConsoleTextAttribute(h, 7);
					return;
				}
			}
			else
			{
				system("cls");
				SetConsoleTextAttribute(h, 12);
				cout << setw(90) << "Invalid move\n" << endl;
				SetConsoleTextAttribute(h, 7);
				return;
			}

		}
		else
		{
			system("cls");
			SetConsoleTextAttribute(h, 12);
			cout << setw(90) << "Invalid move \n" << endl;
			SetConsoleTextAttribute(h, 7);
			return;

		}
}
void enpassant(char board[8][8], int e1, int e2, int e3, int e4)
{

	int diff1 = e3 - e1;
	int diff2 = e4 - e2;

	if (board[e1][e2 + diff2] == 'p')
	{
		board[e1][e2 + diff2] = ' ';
		swap(board[e1][e2], board[e3][e4]);
		system("cls");
		if (rapidmode == true)
		{
			if (i % 2 == 1)
			{
				timeW -= 10;
			}
			else
			{
				if (i % 2 == 0)
				{
					timeB -= 10;
				}
			}
		}
		i++;
		if (retrieving == false)
		{
			fout << " " << e1 << e2 << e3 << e4 << '\n';
		}
		cout << setw(90) << "EN PASSANT BY BLACK PAWN\n";
	}
	else
		if (board[e1][e2 + diff2] == 'P')
		{
			board[e1][e2 + diff2] = ' ';
			swap(board[e1][e2], board[e3][e4]);
			system("cls");
			if (rapidmode == true)
			{
				if (i % 2 == 1)
				{
					timeW -= 10;
				}
				else
				{
					if (i % 2 == 0)
					{
						timeB -= 10;
					}
				}
			}
			i++;
			if (retrieving == false)
			{
				fout << " " << e1 << e2 << e3 << e4 << '\n';
			}
			cout << setw(90) << "EN PASSANT BY WHITE PAWN\n";
		}
		else
		{
			system("cls");
			SetConsoleTextAttribute(h, 12);
			cout << setw(90) << "Invalid move\n" << endl;
			SetConsoleTextAttribute(h, 7);
			return;
		}

}
bool checkmate(char board[8][8])
{
	bool checksW[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	bool checksB[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

	int l = 0;
	for (int j = 0; j < 8; j++)
	{
		for (int k = 0; k < 8; k++)
		{
			if (board[j][k] == 'K')
			{
				checksW[0] = safe(board, j, k);
				checksW[1] = validmove(board, j + 1, k + 1);
				checksW[2] = validmove(board, j + 1, k - 1);
				checksW[3] = validmove(board, j - 1, k + 1);
				checksW[4] = validmove(board, j - 1, k - 1);
				checksW[5] = validmove(board, j + 1, k);
				checksW[6] = validmove(board, j - 1, k);
				checksW[7] = validmove(board, j, k + 1);
				checksW[8] = validmove(board, j, k - 1);

				continue;
			}
			if (board[j][k] == 'k')
			{
				checksB[0] = safe(board, j, k);
				checksB[1] = validmove(board, j + 1, k + 1);
				checksB[2] = validmove(board, j + 1, k - 1);
				checksB[3] = validmove(board, j - 1, k + 1);
				checksB[4] = validmove(board, j - 1, k - 1);
				checksB[5] = validmove(board, j + 1, k);
				checksB[6] = validmove(board, j - 1, k);
				checksB[7] = validmove(board, j, k + 1);
				checksB[8] = validmove(board, j, k - 1);
				continue;
			}
			if (board[j][k] != ' ')
			{
				l++;
			}
		}
	}
	{//CheckMate//

		if (checksB[0] == true && i % 2 == 0)
		{
			SetConsoleTextAttribute(h, 116);
			cout << "Black King Under Check\n";
			SetConsoleTextAttribute(h, 7);
			GetKey();
			chkmt = true;
			character = 'k';
		}
		if (checksW[0] == true && i % 2 == 1)
		{
			SetConsoleTextAttribute(h, 116);
			cout << "White King Under Check\n";
			SetConsoleTextAttribute(h, 7);
			GetKey();
			chkmt = true;
			character = 'K';
		}
		if (checksW[0] == true && checksW[1] == true && checksW[2] == true &&
			checksW[3] == true && checksW[4] == true && checksW[5] == true &&
			checksW[6] == true && checksW[7] == true && checksW[8] == true)
		{
			chkmt = true;
			character = 'K';
		}
		else if (checksB[0] == true && checksB[1] == true && checksB[2] == true &&
			checksB[3] == true && checksB[4] == true && checksB[5] == true &&
			checksB[6] == true && checksB[7] == true && checksB[8] == true)
		{
			chkmt = true;
			character = 'k';
		}
		else if (checksW[0] == false && checksW[1] == true && checksW[2] == true &&
			checksW[3] == true && checksW[4] == true && checksW[5] == true &&
			checksW[6] == true && checksW[7] == true && checksW[8] == true)
		{
			stlmt = true;
		}
		else if (checksB[0] == false && checksB[1] == true && checksB[2] == true &&
			checksB[3] == true && checksB[4] == true && checksB[5] == true &&
			checksB[6] == true && checksB[7] == true && checksB[8] == true)
		{
			stlmt = true;
		}
	}
	return true;
}


bool stalemate(char board[8][8])
{
	bool chk = true;
	for (int p = 0; p < 8; p++)
	{
		for (int q = 0; q < 8; q++)
		{
			if (board[p][q] >= 65 && board[p][q] <= 120)
			{
				legalcall(board, p, q);
			}
			else
			{
				continue;
			}
		}
	}
	if (whtmv == false)
	{
		stlmt = true;
	}
	else if (blkmv == false)
	{
		stlmt = true;
	}
	else
	{
		stlmt = false;
	}

	return stlmt;
}
void point_sender(char board[8][8], int e1, int e2, int e3, int e4)
{
	if (i % 2 == 1 && board[e1][e2] >= 'a' && board[e1][e2] <= 'z')
	{
		if (board[e1][e2] == 'k')
		{
			moveking(board, e1, e2, e3, e4);
		}
		else
		{
			if (board[e1][e2] == 'q')
			{
				movequeen(board, e1, e2, e3, e4);
				counter_black++;
			}
			else
			{
				if (board[e1][e2] == 'n')
				{
					moveknight(board, e1, e2, e3, e4);
				}
				else
				{
					if (board[e1][e2] == 'b')
					{
						movebishop(board, e1, e2, e3, e4);
					}
					else
					{
						if (board[e1][e2] == 'r')
						{
							moverook(board, e1, e2, e3, e4);
							counter_black++;
						}
						else
						{
							if (board[e1][e2] == 'p')
							{
								movepawn(board, e1, e2, e3, e4);
							}
							else
							{
								system("cls");
								cout << setw(90) << "Invalid Turn" << endl;
							}
						}
					}
				}
			}
		}
	}
	else
	{
		if (i % 2 == 0 && board[e1][e2] >= 'A' && board[e1][e2] <= 'Z')
		{


			if (board[e1][e2] == 'K')
			{
				moveking(board, e1, e2, e3, e4);
			}
			else
			{
				if (board[e1][e2] == 'Q')
				{
					movequeen(board, e1, e2, e3, e4);
					counter_white++;
				}
				else
				{
					if (board[e1][e2] == 'N')
					{
						moveknight(board, e1, e2, e3, e4);
					}
					else
					{
						if (board[e1][e2] == 'B')
						{
							movebishop(board, e1, e2, e3, e4);
						}
						else
						{
							if (board[e1][e2] == 'R')
							{
								moverook(board, e1, e2, e3, e4);
								counter_white++;
							}
							else
							{
								if (board[e1][e2] == 'P')
								{
									movepawn(board, e1, e2, e3, e4);
								}
								else
								{
									system("cls");
									cout << setw(90) << "Invalid Move" << endl;
								}
							}
						}
					}
				}
			}
		}
		else
		{
			system("cls");
			if (i % 2 == 1)
			{
				SetConsoleTextAttribute(h, 12);
				cout << setw(90) << "Black's Turn\n";
				SetConsoleTextAttribute(h, 7);
			}
			else
			{
				SetConsoleTextAttribute(h, 12);
				cout << setw(90) << "White's Turn\n";
				SetConsoleTextAttribute(h, 7);
			}
		}
	}
}
bool safe(char board[8][8], int m, int k)
{
	bool chks[6] = { 0, 0, 0, 0, 0, 0 };

	bool chk = false;
	SetConsoleTextAttribute(h, 4);
	if ((board[m][k] == 'K'))//White King Check//
	{
		//Knight//
		{
			//all possible directions//
			if (board[m + 1][k + 2] == 'n' ||
				board[m + 1][k - 2] == 'n' ||
				board[m - 1][k + 2] == 'n' ||
				board[m - 1][k - 2] == 'n' ||
				board[m + 2][k + 1] == 'n' ||
				board[m + 2][k - 1] == 'n' ||
				board[m - 2][k + 1] == 'n' ||
				board[m - 2][k - 1] == 'n')
			{
				chks[0] = true;
				SetConsoleTextAttribute(h, 7);
				chk = true;

			}
		}
		//Rook//
		{
			int hold = m;
			hold--;
			for (; hold >= 0; hold--)//row check left//
			{
				if ((board[hold][k] >= 'A' && board[hold][k] <= 'Z') ||
					board[hold][k] == 'p' || board[hold][k] == 'b'
					|| board[hold][k] == 'n' || board[hold][k] == 'k')
				{
					break;
				}
				if (board[hold][k] == 'r' || board[hold][k] == 'q')
				{
					chks[1] = true;
					SetConsoleTextAttribute(h, 7);
					chk = true;
				}
			}
			hold = m;
			hold++;
			for (; hold <= 7; hold++)//row check right//
			{
				if ((board[hold][k] >= 'A' && board[hold][k] <= 'Z') ||
					board[hold][k] == 'p' || board[hold][k] == 'b'
					|| board[hold][k] == 'n' || board[hold][k] == 'k')
				{
					break;
				}
				if (board[hold][k] == 'r' || board[hold][k] == 'q')
				{

					chks[1] = true;
					SetConsoleTextAttribute(h, 7);
					chk = true;
				}
			}
			hold = k;
			hold--;
			for (; hold >= 0; hold--)//column check downward//
			{
				if ((board[m][hold] >= 'A' && board[m][hold] <= 'Z') ||
					board[m][hold] == 'p' || board[m][hold] == 'b'
					|| board[m][hold] == 'n' || board[m][hold] == 'k')
				{
					break;
				}
				if (board[m][hold] == 'r' || board[m][hold] == 'q')
				{
					chks[2] = true;
					SetConsoleTextAttribute(h, 7);
					chk = true;
				}
			}
			hold = k;
			hold++;
			for (; hold < 8; hold++)//column check upward//
			{
				if ((board[m][hold] >= 'A' && board[m][hold] <= 'Z') ||
					board[m][hold] == 'p' || board[m][hold] == 'b'
					|| board[m][hold] == 'n' || board[m][hold] == 'k')
				{
					break;
				}
				if (board[m][hold] == 'r' || board[m][hold] == 'q')
				{
					chks[2] = true;
					SetConsoleTextAttribute(h, 7);
					chk = true;
				}
			}
		}
		//Pawn//
		{
			if (board[m - 1][k - 1] == 'p' || board[m - 1][k + 1] == 'p' || board[m - 1][k - 1] == 'q' || board[m - 1][k + 1] == 'q')
			{
				chks[3] = true;
				SetConsoleTextAttribute(h, 7);
				chk = true;
			}
		}
		//Bishop//
		{
			int hold1 = m;
			int hold2 = k;
			hold1++;
			hold2++;
			for (; hold1 < 8 && hold2 < 8; hold1++, hold2++)//top right direction//
			{
				if (board[hold1][hold2] >= 'A' && board[hold1][hold2] <= 'Z' ||
					board[hold1][hold2] == 'p' || board[hold1][hold2] == 'r'
					|| board[hold1][hold2] == 'n' || board[hold1][hold2] == 'k')
				{
					break;
				}
				if (board[hold1][hold2] == 'b' || board[hold1][hold2] == 'q')
				{
					chks[4] = true;
					SetConsoleTextAttribute(h, 7);
					chk = true;
				}
			}
			hold1 = m;
			hold2 = k;
			hold1--;
			hold2--;
			for (; hold1 >= 0 && hold2 >= 0; hold1--, hold2--)//bottom left direction//
			{
				if (board[hold1][hold2] >= 'A' && board[hold1][hold2] <= 'Z' ||
					board[hold1][hold2] == 'p' || board[hold1][hold2] == 'r'
					|| board[hold1][hold2] == 'n' || board[hold1][hold2] == 'k')
				{
					break;
				}
				if (board[hold1][hold2] == 'b' || board[hold1][hold2] == 'q')
				{
					chks[4] = true;
					SetConsoleTextAttribute(h, 7);
					chk = true;
				}
			}
			hold1 = m;
			hold2 = k;
			hold1--;
			hold2++;
			for (; hold1 >= 0 && hold2 <= 7; hold1--, hold2++)//top right direction//
			{
				if (board[hold1][hold2] >= 'A' && board[hold1][hold2] <= 'Z' ||
					board[hold1][hold2] == 'p' || board[hold1][hold2] == 'r'
					|| board[hold1][hold2] == 'n' || board[hold1][hold2] == 'k')
				{
					break;
				}
				if (board[hold1][hold2] == 'b' || board[hold1][hold2] == 'q')
				{
					chks[5] = true;
					SetConsoleTextAttribute(h, 7);
					chk = true;
				}
			}
			hold1 = m;
			hold2 = k;
			hold1++;
			hold2--;
			for (; hold1 <= 7 && hold2 >= 0; hold1++, hold2--)//bottom left direction//
			{
				if (board[hold1][hold2] >= 'A' && board[hold1][hold2] <= 'Z' ||
					board[hold1][hold2] == 'p' || board[hold1][hold2] == 'r'
					|| board[hold1][hold2] == 'n' || board[hold1][hold2] == 'k')
				{
					break;
				}
				if (board[hold1][hold2] == 'b' || board[hold1][hold2] == 'q')
				{
					chks[5] = true;
					SetConsoleTextAttribute(h, 7);
					chk = true;
				}
			}
		}
	}
	else if ((board[m][k] == 'k'))//Black King Check//
	{
		//Knight//
		{
			//all possible directions//
			if (board[m + 1][k + 2] == 'N' ||
				board[m + 1][k - 2] == 'N' ||
				board[m - 1][k + 2] == 'N' ||
				board[m - 1][k - 2] == 'N' ||
				board[m + 2][k + 1] == 'N' ||
				board[m + 2][k - 1] == 'N' ||
				board[m - 2][k + 1] == 'N' ||
				board[m - 2][k - 1] == 'N')
			{
				chks[0] = true;
				SetConsoleTextAttribute(h, 7);
				chk = true;
			}
		}
		//Rook//
		{
			int hold = m;
			hold--;
			for (; hold >= 0; hold--)//row check left//
			{
				if (board[hold][k] >= 'a' && board[hold][k] <= 'z' ||
					board[hold][k] == 'P' || board[hold][k] == 'B'
					|| board[hold][k] == 'N' || board[hold][k] == 'K')
				{
					break;
				}

				if (board[hold][k] == 'R' || board[hold][k] == 'Q')
				{
					chks[1] = true;
					SetConsoleTextAttribute(h, 7);
					chk = true;
				}
			}
			hold = m;
			hold++;
			for (; hold <= 7; hold++)//row check right//
			{
				if (board[hold][k] >= 'a' && board[hold][k] <= 'z' ||
					board[hold][k] == 'P' || board[hold][k] == 'B'
					|| board[hold][k] == 'N' || board[hold][k] == 'K')
				{
					break;
				}

				if (board[hold][k] == 'R' || board[hold][k] == 'Q')
				{
					chks[1] = true;
					SetConsoleTextAttribute(h, 7);
					chk = true;
				}
			}
			hold = k;
			hold--;
			for (; hold >= 0; hold--)//column check downward//
			{
				if (board[m][hold] >= 'a' && board[m][hold] <= 'z' ||
					board[m][hold] == 'P' || board[m][hold] == 'B'
					|| board[m][hold] == 'N' || board[m][hold] == 'K')
				{
					break;
				}
				if (board[m][hold] == 'R' || board[m][hold] == 'Q')
				{
					chks[2] = true;
					SetConsoleTextAttribute(h, 7);
					chk = true;
				}
			}
			hold = k;
			hold++;
			for (; hold <= 7; hold++)//column check upward//
			{
				if (board[m][hold] >= 'a' && board[m][hold] <= 'z' ||
					board[m][hold] == 'P' || board[m][hold] == 'B'
					|| board[m][hold] == 'N' || board[m][hold] == 'K')
				{
					break;
				}
				if (board[m][hold] == 'R' || board[m][hold] == 'Q')
				{
					chks[2] = true;
					SetConsoleTextAttribute(h, 7);
					chk = true;
				}
			}
		}
		//Pawn//
		{
			if (board[m + 1][k - 1] == 'P' || board[m + 1][k + 1] == 'P' || board[m + 1][k - 1] == 'Q' || board[m + -1][k + 1] == 'Q')
			{
				chks[3] = true;
				SetConsoleTextAttribute(h, 7);
				chk = true;
			}
		}
		//Bishop//
		{
			int hold1 = m;
			int hold2 = k;
			hold1++;
			hold2++;
			for (; hold1 <= 7 && hold2 <= 7; hold1++, hold2++)//top right direction//
			{
				if (board[hold1][hold2] >= 'a' && board[hold1][hold2] <= 'z' ||
					board[hold1][hold2] == 'P' || board[hold1][hold2] == 'R'
					|| board[hold1][hold2] == 'N' || board[hold1][hold2] == 'K')
				{
					break;
				}
				if (board[hold1][hold2] == 'B' || board[hold1][hold2] == 'Q')
				{
					chks[4] = true;
					SetConsoleTextAttribute(h, 7);
					chk = true;
				}
			}
			hold1 = m;
			hold2 = k;
			hold1--;
			hold2--;
			for (; hold1 >= 0 && hold2 >= 0; hold1--, hold2--)//bottom left direction//
			{
				if (board[hold1][hold2] >= 'a' && board[hold1][hold2] <= 'z' ||
					board[hold1][hold2] == 'P' || board[hold1][hold2] == 'R'
					|| board[hold1][hold2] == 'N' || board[hold1][hold2] == 'K')
				{
					break;
				}
				if (board[hold1][hold2] == 'B' || board[hold1][hold2] == 'Q')
				{
					chks[4] = true;
					SetConsoleTextAttribute(h, 7);
					chk = true;
				}
			}
			hold1 = m;
			hold2 = k;
			hold1--;
			hold2++;
			for (; hold1 >= 0 && hold2 <= 7; hold1--, hold2++)
			{
				if (board[hold1][hold2] >= 'a' && board[hold1][hold2] <= 'z' ||
					board[hold1][hold2] == 'P' || board[hold1][hold2] == 'R'
					|| board[hold1][hold2] == 'N' || board[hold1][hold2] == 'K')
				{
					break;
				}

				if (board[hold1][hold2] == 'B' || board[hold1][hold2] == 'Q')
				{
					chks[5] = true;
					SetConsoleTextAttribute(h, 7);
					chk = true;
				}
			}
			hold1 = m;
			hold2 = k;
			hold1++;
			hold2--;
			for (; hold1 <= 7 && hold2 >= 0; hold1++, hold2--)//bottom left direction//
			{
				if (board[hold1][hold2] >= 'a' && board[hold1][hold2] <= 'z' ||
					board[hold1][hold2] == 'P' || board[hold1][hold2] == 'R'
					|| board[hold1][hold2] == 'N' || board[hold1][hold2] == 'K')
				{
					break;
				}
				if (board[hold1][hold2] == 'B' || board[hold1][hold2] == 'Q')
				{
					chks[5] = true;
					SetConsoleTextAttribute(h, 7);
					chk = true;
				}
			}
		}
	}


	if (board[m][k] == 'K')
	{
		SetConsoleTextAttribute(h, 8);
		cout << "White King Threat(s): \n";
		SetConsoleTextAttribute(h, 4);
		int counter = 0;
		if (chks[0] == true)
		{
			cout << "Knight's Angle Block\n";
			counter++;
		}
		if (chks[1] == true)
		{
			cout << "Angle Block(Rows)\n";
			counter++;
		}
		if (chks[2] == true)
		{
			cout << "Angle Block(Coloumns)\n";
			counter++;
		}
		if (chks[3] == true)
		{
			cout << "Pawn Block\n";
			counter++;
		}
		if (chks[4] == true)
		{
			cout << "Diagonal Block\n";
			counter++;
		}
		if (chks[5] == true)
		{
			cout << "Anti-Diagonal Block\n";
			counter++;
		}
		SetConsoleTextAttribute(h, 7);
		{
			if (counter == 0)
			{
				SetConsoleTextAttribute(h, 10);
				cout << "No Threats\n\n";
				SetConsoleTextAttribute(h, 7);
			}
			else
				cout << "End of List\n\n";

		}

	}

	else if (board[m][k] == 'k')
	{
		SetConsoleTextAttribute(h, 8);
		cout << "Black King Threat(s): \n";
		SetConsoleTextAttribute(h, 4);
		int counter = 0;
		if (chks[0] == true)
		{
			cout << "Knight's Angle Block\n";
			counter++;
		}
		if (chks[1] == true)
		{
			cout << "Angle Block(Rows)\n";
			counter++;
		}
		if (chks[2] == true)
		{
			cout << "Angle Block(Coloumns)\n";
			counter++;
		}
		if (chks[3] == true)
		{
			cout << "Pawn Block\n";
			counter++;
		}
		if (chks[4] == true)
		{
			cout << "Diagonal Block\n";
			counter++;
		}
		if (chks[5] == true)
		{
			cout << "Anti-Diagonal Block\n";
			counter++;
		}
		SetConsoleTextAttribute(h, 7);
		if (counter == 0)
		{
			SetConsoleTextAttribute(h, 10);
			cout << "No Threats\n\n";
			SetConsoleTextAttribute(h, 7);
		}
		else
			cout << "End of List\n\n";
	}
	if (chk == true)
	{
		SetConsoleTextAttribute(h, 7);
		return true;
	}
	else
	{
		SetConsoleTextAttribute(h, 7);
		return false;
	}
}
void legalcall(char board[8][8], int p, int q)
{

	if (board[p][q] >= 'A' && board[p][q] <= 'Z')
	{
		if (board[p][q] == 'P')
		{
			if (board[p + 1][q] == ' ')
			{
				whtmv = true;
				return;
			}
			if (board[p + 1][q + 1] == 'q' || board[p + 1][q + 1] == 'r' || board[p + 1][q + 1] == 'n' || board[p + 1][q + 1] == 'b' || board[p + 1][q + 1] == 'p')
			{
				whtmv = true;
				return;
			}
			if (board[p + 1][q - 1] == 'q' || board[p + 1][q - 1] == 'r' || board[p + 1][q - 1] == 'n' || board[p + 1][q - 1] == 'b' || board[p + 1][q - 1] == 'r')
			{
				whtmv = true;
				return;
			}
		}
		else if (board[p][q] == 'Q')
		{
			if ((board[p + 1][q + 1] >= 'a' && board[p + 1][q + 1] <= 'z') || board[p + 1][q + 1] == ' ')
			{
				whtmv = true;
				return;
			}
			if ((board[p - 1][q + 1] >= 'a' && board[p - 1][q + 1] <= 'z') || board[p - 1][q + 1] == ' ')
			{
				whtmv = true;
				return;
			}
			if ((board[p + 1][q - 1] >= 'a' && board[p + 1][q - 1] <= 'z') || board[p + 1][q - 1] == ' ')
			{
				whtmv = true;
				return;
			}
			if ((board[p - 1][q - 1] >= 'a' && board[p - 1][q - 1] <= 'z') || board[p - 1][q - 1] == ' ')
			{
				whtmv = true;
				return;
			}
			if ((board[p][q + 1] >= 'a' && board[p][q + 1] <= 'z') || board[p][q + 1] == ' ')
			{
				whtmv = true;
				return;
			}
			if ((board[p + 1][q] >= 'a' && board[p + 1][q] <= 'z') || board[p + 1][q] == ' ')
			{
				whtmv = true;
				return;
			}
			if ((board[p][q - 1] >= 'a' && board[p][q - 1] <= 'z') || board[p][q - 1] == ' ')
			{
				whtmv = true;
				return;
			}
			if ((board[p - 1][q] >= 'a' && board[p - 1][q] <= 'z') || board[p - 1][q] == ' ')
			{
				whtmv = true;
				return;
			}






		}
		else if (board[p][q] == 'K')
		{
			if ((validmove(board, p, q) == true))
			{
				if (validmove(board, p + 1, q + 1) == false)
				{
					whtmv = true;
					return;
				}
				if (validmove(board, p - 1, q + 1) == false)
				{
					whtmv = true;
					return;
				}
				if (validmove(board, p + 1, q - 1) == false)
				{
					whtmv = true;
					return;
				}
				if (validmove(board, p - 1, q - 1) == false)
				{
					whtmv = true;
					return;
				}
				if (validmove(board, p, q + 1) == false)
				{
					whtmv = true;
					return;
				}
				if (validmove(board, p + 1, q) == false)
				{
					whtmv = true;
					return;
				}
				if (validmove(board, p - 1, q) == false)
				{
					whtmv = true;
					return;
				}
				if (validmove(board, p, q - 1) == false)
				{
					whtmv = true;
					return;
				}
			}
		}
		else if (board[p][q] == 'R')
		{
			if ((board[p][q + 1] >= 'a' && board[p][q + 1] <= 'z') || board[p][q + 1] == ' ')
			{
				whtmv = true;
				return;
			}
			if ((board[p + 1][q] >= 'a' && board[p + 1][q] <= 'z') || board[p + 1][q] == ' ')
			{
				whtmv = true;
				return;
			}
			if ((board[p][q - 1] >= 'a' && board[p][q - 1] <= 'z') || board[p][q - 1] == ' ')
			{
				whtmv = true;
				return;
			}
			if ((board[p - 1][q] >= 'a' && board[p - 1][q] <= 'z') || board[p - 1][q] == ' ')
			{
				whtmv = true;
				return;
			}

		}
		else if (board[p][q] == 'N')
		{
			if ((board[p + 1][q + 2] >= 'a' && board[p + 1][q + 2] <= 'z') || board[p + 1][q + 2] == ' ')
			{
				whtmv = true;
				return;
			}
			if ((board[p + 1][q - 2] >= 'a' && board[p + 1][q - 2] <= 'z') || board[p + 1][q - 2] == ' ')
			{
				whtmv = true;
				return;
			}
			if ((board[p - 1][q - 2] >= 'a' && board[p - 1][q - 2] <= 'z') || board[p - 1][q - 2] == ' ')
			{
				whtmv = true;
				return;
			}
			if ((board[p - 1][q + 2] >= 'a' && board[p - 1][q + 2] <= 'z') || board[p - 1][q + 2] == ' ')
			{
				whtmv = true;
				return;
			}
			if ((board[p - 2][q - 1] >= 'a' && board[p - 2][q - 1] <= 'z') || board[p - 2][q - 1] == ' ')
			{
				whtmv = true;
				return;
			}
			if ((board[p - 2][q + 1] >= 'a' && board[p - 2][q + 1] <= 'z') || board[p - 2][q + 1] == ' ')
			{
				whtmv = true;
				return;
			}
			if ((board[p + 2][q + 1] >= 'a' && board[p + 2][q + 1] <= 'z') || board[p + 2][q + 1] == ' ')
			{
				whtmv = true;
				return;
			}
			if ((board[p + 2][q - 1] >= 'a' && board[p + 2][q - 1] <= 'z') || board[p + 2][q - 1] == ' ')
			{
				whtmv = true;
				return;
			}
		}
		else if (board[p][q] == 'B')
		{
			if ((board[p + 1][q + 1] >= 'a' && board[p + 1][q + 1] <= 'z') || board[p + 1][q + 1] == ' ')
			{
				whtmv = true;
				return;
			}
			if ((board[p - 1][q + 1] >= 'a' && board[p - 1][q + 1] <= 'z') || board[p - 1][q + 1] == ' ')
			{
				whtmv = true;
				return;
			}
			if ((board[p + 1][q - 1] >= 'a' && board[p + 1][q - 1] <= 'z') || board[p + 1][q - 1] == ' ')
			{
				whtmv = true;
				return;
			}
			if ((board[p - 1][q - 1] >= 'a' && board[p - 1][q - 1] <= 'z') || board[p - 1][q - 1] == ' ')
			{
				whtmv = true;
				return;
			}
		}
	}

	///////
	else if ((board[p][q] >= 'a' && board[p][q] <= 'z'))
	{
		if (board[p][q] == 'p')
		{
			if (board[p - 1][q] == ' ')
			{
				blkmv = true;
				return;
			}
			if (board[p - 1][q + 1] == 'Q' || board[p - 1][q + 1] == 'R' || board[p - 1][q + 1] == 'N' || board[p - 1][q + 1] == 'B' || board[p - 1][q + 1] == 'P')
			{
				blkmv = true;
				return;
			}
			if (board[p - 1][q - 1] == 'Q' || board[p - 1][q - 1] == 'R' || board[p - 1][q - 1] == 'N' || board[p - 1][q - 1] == 'B' || board[p - 1][q - 1] == 'R')
			{
				blkmv = true;
				return;
			}
		}
		else if (board[p][q] == 'q')
		{
			if ((board[p + 1][q + 1] >= 'A' && board[p + 1][q + 1] <= 'Z') || board[p + 1][q + 1] == ' ')
			{
				blkmv = true;
				return;
			}
			if ((board[p - 1][q + 1] >= 'A' && board[p - 1][q + 1] <= 'Z') || board[p - 1][q + 1] == ' ')
			{
				blkmv = true;
				return;
			}
			if ((board[p + 1][q - 1] >= 'A' && board[p + 1][q - 1] <= 'Z') || board[p + 1][q - 1] == ' ')
			{
				blkmv = true;
				return;
			}
			if ((board[p - 1][q - 1] >= 'A' && board[p - 1][q - 1] <= 'Z') || board[p - 1][q - 1] == ' ')
			{
				blkmv = true;
				return;
			}
			if ((board[p][q + 1] >= 'A' && board[p][q + 1] <= 'Z') || board[p][q + 1] == ' ')
			{
				blkmv = true;
				return;
			}
			if ((board[p + 1][q] >= 'A' && board[p + 1][q] <= 'Z') || board[p + 1][q] == ' ')
			{
				blkmv = true;
				return;
			}
			if ((board[p][q - 1] >= 'A' && board[p][q - 1] <= 'Z') || board[p][q - 1] == ' ')
			{
				blkmv = true;
				return;
			}
			if ((board[p - 1][q] >= 'A' && board[p - 1][q] <= 'Z') || board[p - 1][q] == ' ')
			{
				blkmv = true;
				return;
			}
		}
		else if (board[p][q] == 'r')
		{
			if ((board[p][q + 1] >= 'A' && board[p][q + 1] <= 'Z') || board[p][q + 1] == ' ')
			{
				blkmv = true;
				return;
			}
			if ((board[p + 1][q] >= 'A' && board[p + 1][q] <= 'Z') || board[p + 1][q] == ' ')
			{
				blkmv = true;
				return;
			}
			if ((board[p][q - 1] >= 'A' && board[p][q - 1] <= 'Z') || board[p][q - 1] == ' ')
			{
				blkmv = true;
				return;
			}
			if ((board[p - 1][q] >= 'A' && board[p - 1][q] <= 'Z') || board[p - 1][q] == ' ')
			{
				blkmv = true;
				return;
			}

		}
		else if (board[p][q] == 'k')
		{
			if ((validmove(board, p, q) == true))
			{
				if (validmove(board, p + 1, q + 1) == false)
				{
					cout << "Found at 1";
					GetKey();
					blkmv = true;
					return;
				}
				if (validmove(board, p - 1, q + 1) == false)
				{
					cout << "Found at 2";
					GetKey();
					blkmv = true;
					return;
				}
				if (validmove(board, p + 1, q - 1) == false)
				{
					cout << "Found at 3";
					GetKey();
					blkmv = true;
					return;
				}
				if (validmove(board, p - 1, q - 1) == false)
				{
					cout << "Found at 4";
					GetKey();
					blkmv = true;
					return;
				}
				if (validmove(board, p, q + 1) == false)
				{
					cout << "Found at 5";
					GetKey();
					blkmv = true;
					return;
				}
				if (validmove(board, p + 1, q) == false)
				{
					cout << "Found at 6";
					GetKey();
					blkmv = true;
					return;
				}
				if (validmove(board, p - 1, q) == false)
				{
					cout << "Found at 7";
					GetKey();
					blkmv = true;
					return;
				}
				if (validmove(board, p, q - 1) == false)
				{
					cout << "Found at 8";
					GetKey();
					blkmv = true;
					return;
				}
			}
		}
		else if (board[p][q] == 'n')
		{
			if ((board[p + 1][q + 2] >= 'A' && board[p + 1][q + 2] <= 'Z') || board[p + 1][q + 2] == ' ')
			{
				blkmv = true;
				return;
			}
			if ((board[p + 1][q - 2] >= 'A' && board[p + 1][q - 2] <= 'Z') || board[p + 1][q - 2] == ' ')
			{
				blkmv = true;
				return;
			}
			if ((board[p - 1][q - 2] >= 'A' && board[p - 1][q - 2] <= 'Z') || board[p - 1][q - 2] == ' ')
			{
				blkmv = true;
				return;
			}
			if ((board[p - 1][q + 2] >= 'A' && board[p - 1][q + 2] <= 'Z') || board[p - 1][q + 2] == ' ')
			{
				blkmv = true;
				return;
			}
			if ((board[p - 2][q - 1] >= 'A' && board[p - 2][q - 1] <= 'Z') || board[p - 2][q - 1] == ' ')
			{
				blkmv = true;
				return;
			}
			if ((board[p - 2][q + 1] >= 'A' && board[p - 2][q + 1] <= 'Z') || board[p - 2][q + 1] == ' ')
			{
				blkmv = true;
				return;
			}
			if ((board[p + 2][q + 1] >= 'A' && board[p + 2][q + 1] <= 'Z') || board[p + 2][q + 1] == ' ')
			{
				blkmv = true;
				return;
			}
			if ((board[p + 2][q - 1] >= 'A' && board[p + 2][q - 1] <= 'Z') || board[p + 2][q - 1] == ' ')
			{
				blkmv = true;
				return;
			}
		}
		else if (board[p][q] == 'b')
		{
			if ((board[p + 1][q + 1] >= 'A' && board[p + 1][q + 1] <= 'Z') || board[p + 1][q + 1] == ' ')
			{
				blkmv = true;
				return;
			}
			if ((board[p - 1][q + 1] >= 'A' && board[p - 1][q + 1] <= 'Z') || board[p - 1][q + 1] == ' ')
			{
				blkmv = true;
				return;
			}
			if ((board[p + 1][q - 1] >= 'A' && board[p + 1][q - 1] <= 'Z') || board[p + 1][q - 1] == ' ')
			{
				blkmv = true;
				return;
			}
			if ((board[p - 1][q - 1] >= 'A' && board[p - 1][q - 1] <= 'Z') || board[p - 1][q - 1] == ' ')
			{
				blkmv = true;
				return;
			}
		}
	}


}

bool validmove(char board[8][8], int m, int k)
{
	bool chks[6] = { 0, 0, 0, 0, 0, 0 };

	bool chk = false;
	SetConsoleTextAttribute(h, 4);
	if ((board[m][k] == ' ' || board[m][k] == 'K' || board[m][k] == 'r' || board[m][k] == 'b'
		|| board[m][k] == 'q' || board[m][k] == 'p' || board[m][k] == 'n'))//White King Check//
	{
		//Knight//
		{
			//all possible directions//
			if (board[m + 1][k + 2] == 'n' ||
				board[m + 1][k - 2] == 'n' ||
				board[m - 1][k + 2] == 'n' ||
				board[m - 1][k - 2] == 'n' ||
				board[m + 2][k + 1] == 'n' ||
				board[m + 2][k - 1] == 'n' ||
				board[m - 2][k + 1] == 'n' ||
				board[m - 2][k - 1] == 'n')
			{
				chks[0] = true;
				SetConsoleTextAttribute(h, 7);
				chk = true;

			}
		}
		//Rook//
		{
			int hold = m;
			hold--;
			for (; hold >= 0; hold--)//row check left//
			{
				if ((board[hold][k] >= 'A' && board[hold][k] <= 'Z') ||
					board[hold][k] == 'p' || board[hold][k] == 'b'
					|| board[hold][k] == 'n' || board[hold][k] == 'k')
				{
					break;
				}
				if (board[hold][k] == 'r' || board[hold][k] == 'q')
				{
					chks[1] = true;
					SetConsoleTextAttribute(h, 7);
					chk = true;
				}
			}
			hold = m;
			hold++;
			for (; hold < 8; hold++)//row check right//
			{
				if ((board[hold][k] >= 'A' && board[hold][k] <= 'Z') ||
					board[hold][k] == 'p' || board[hold][k] == 'b'
					|| board[hold][k] == 'n' || board[hold][k] == 'k')
				{
					break;
				}
				if (board[hold][k] == 'r' || board[hold][k] == 'q')
				{

					chks[1] = true;
					SetConsoleTextAttribute(h, 7);
					chk = true;
				}
			}
			hold = k;
			hold--;
			for (; hold >= 0; hold--)//column check downward//
			{
				if ((board[m][hold] >= 'A' && board[m][hold] <= 'Z') ||
					board[m][hold] == 'p' || board[m][hold] == 'b'
					|| board[m][hold] == 'n' || board[m][hold] == 'k')
				{
					break;
				}
				if (board[m][hold] == 'r' || board[m][hold] == 'q')
				{
					chks[2] = true;
					SetConsoleTextAttribute(h, 7);
					chk = true;
				}
			}
			hold = k;
			hold++;
			for (; hold < 8; hold++)//column check upward//
			{
				if ((board[m][hold] >= 'A' && board[m][hold] <= 'Z') ||
					board[m][hold] == 'p' || board[m][hold] == 'b'
					|| board[m][hold] == 'n' || board[m][hold] == 'k')
				{
					break;
				}
				if (board[m][hold] == 'r' || board[m][hold] == 'q')
				{
					chks[2] = true;
					SetConsoleTextAttribute(h, 7);
					chk = true;
				}
			}
		}
		//Pawn//
		{
			if (board[m - 1][k - 1] == 'p' || board[m - 1][k + 1] == 'p' || board[m - 1][k - 1] == 'q' || board[m - 1][k + 1] == 'q')
			{
				chks[3] = true;
				SetConsoleTextAttribute(h, 7);
				chk = true;
			}
		}
		//Bishop//
		{
			int hold1 = m;
			int hold2 = k;
			hold1++;
			hold2++;
			for (; hold1 < 8 && hold2 < 8; hold1++, hold2++)//top right direction//
			{
				if (board[hold1][hold2] >= 'A' && board[hold1][hold2] <= 'Z' ||
					board[hold1][hold2] == 'p' || board[hold1][hold2] == 'r'
					|| board[hold1][hold2] == 'n' || board[hold1][hold2] == 'k')
				{
					break;
				}
				if (board[hold1][hold2] == 'b' || board[hold1][hold2] == 'q')
				{
					chks[4] = true;
					SetConsoleTextAttribute(h, 7);
					chk = true;
				}
			}
			hold1 = m;
			hold2 = k;
			hold1--;
			hold2--;
			for (; hold1 >= 0 && hold2 >= 0; hold1--, hold2--)//bottom left direction//
			{
				if (board[hold1][hold2] >= 'A' && board[hold1][hold2] <= 'Z' ||
					board[hold1][hold2] == 'p' || board[hold1][hold2] == 'r'
					|| board[hold1][hold2] == 'n' || board[hold1][hold2] == 'k')
				{
					break;
				}
				if (board[hold1][hold2] == 'b' || board[hold1][hold2] == 'q')
				{
					chks[4] = true;
					SetConsoleTextAttribute(h, 7);
					chk = true;
				}
			}
			hold1 = m;
			hold2 = k;
			hold1--;
			hold2++;
			for (; hold1 >= 0 && hold2 <= 7; hold1--, hold2++)//top right direction//
			{
				if (board[hold1][hold2] >= 'A' && board[hold1][hold2] <= 'Z' ||
					board[hold1][hold2] == 'p' || board[hold1][hold2] == 'r'
					|| board[hold1][hold2] == 'n' || board[hold1][hold2] == 'k')
				{
					break;
				}
				if (board[hold1][hold2] == 'b' || board[hold1][hold2] == 'q')
				{
					chks[5] = true;
					SetConsoleTextAttribute(h, 7);
					chk = true;
				}
			}
			hold1 = m;
			hold2 = k;
			hold1++;
			hold2--;
			for (; hold1 <= 7 && hold2 >= 0; hold1++, hold2--)//bottom left direction//
			{
				if (board[hold1][hold2] >= 'A' && board[hold1][hold2] <= 'Z' ||
					board[hold1][hold2] == 'p' || board[hold1][hold2] == 'r'
					|| board[hold1][hold2] == 'n' || board[hold1][hold2] == 'k')
				{
					break;
				}
				if (board[hold1][hold2] == 'b' || board[hold1][hold2] == 'q')
				{
					chks[5] = true;
					SetConsoleTextAttribute(h, 7);
					chk = true;
				}
			}
		}
	}
	else if ((board[m][k] == ' ' || board[m][k] == 'k' || board[m][k] == 'R' || board[m][k] == 'B'
		|| board[m][k] == 'Q' || board[m][k] == 'P' || board[m][k] == 'N'))//Black King Check//
	{
		//Knight//
		{
			//all possible directions//
			if (board[m + 1][k + 2] == 'N' ||
				board[m + 1][k - 2] == 'N' ||
				board[m - 1][k + 2] == 'N' ||
				board[m - 1][k - 2] == 'N' ||
				board[m + 2][k + 1] == 'N' ||
				board[m + 2][k - 1] == 'N' ||
				board[m - 2][k + 1] == 'N' ||
				board[m - 2][k - 1] == 'N')
			{
				chks[0] = true;
				SetConsoleTextAttribute(h, 7);
				chk = true;
			}
		}
		//Rook//
		{
			int hold = m;
			hold--;
			for (; hold >= 0; hold--)//row check left//
			{
				if (board[hold][k] >= 'a' && board[hold][k] <= 'z' ||
					board[hold][k] == 'P' || board[hold][k] == 'B'
					|| board[hold][k] == 'N' || board[hold][k] == 'K')
				{
					break;
				}

				if (board[hold][k] == 'R' || board[hold][k] == 'Q')
				{
					chks[1] = true;
					SetConsoleTextAttribute(h, 7);
					chk = true;
				}
			}
			hold = m;
			hold++;
			for (; hold <= 7; hold++)//row check right//
			{
				if (board[hold][k] >= 'a' && board[hold][k] <= 'z' ||
					board[hold][k] == 'P' || board[hold][k] == 'B'
					|| board[hold][k] == 'N' || board[hold][k] == 'K')
				{
					break;
				}

				if (board[hold][k] == 'R' || board[hold][k] == 'Q')
				{
					chks[1] = true;
					SetConsoleTextAttribute(h, 7);
					chk = true;
				}
			}
			hold = k;
			hold--;
			for (; hold >= 0; hold--)//column check downward//
			{
				if (board[m][hold] >= 'a' && board[m][hold] <= 'z' ||
					board[m][hold] == 'P' || board[m][hold] == 'B'
					|| board[m][hold] == 'N' || board[m][hold] == 'K')
				{
					break;
				}
				if (board[m][hold] == 'R' || board[m][hold] == 'Q')
				{
					chks[2] = true;
					SetConsoleTextAttribute(h, 7);
					chk = true;
				}
			}
			hold = k;
			hold++;
			for (; hold <= 7; hold++)//column check upward//
			{
				if (board[m][hold] >= 'a' && board[m][hold] <= 'z' ||
					board[m][hold] == 'P' || board[m][hold] == 'B'
					|| board[m][hold] == 'N' || board[m][hold] == 'K')
				{
					break;
				}
				if (board[m][hold] == 'R' || board[m][hold] == 'Q')
				{
					chks[2] = true;
					SetConsoleTextAttribute(h, 7);
					chk = true;
				}
			}
		}
		//Pawn//
		{
			if (board[m + 1][k - 1] == 'P' || board[m + 1][k + 1] == 'P' || board[m + 1][k - 1] == 'Q' || board[m + -1][k + 1] == 'Q')
			{
				chks[3] = true;
				SetConsoleTextAttribute(h, 7);
				chk = true;
			}
		}
		//Bishop//
		{
			int hold1 = m;
			int hold2 = k;
			hold1++;
			hold2++;
			for (; hold1 <= 7 && hold2 <= 7; hold1++, hold2++)//top right direction//
			{
				if (board[hold1][hold2] >= 'a' && board[hold1][hold2] <= 'z' ||
					board[hold1][hold2] == 'P' || board[hold1][hold2] == 'R'
					|| board[hold1][hold2] == 'N' || board[hold1][hold2] == 'K')
				{
					break;
				}
				if (board[hold1][hold2] == 'B' || board[hold1][hold2] == 'Q')
				{
					chks[4] = true;
					SetConsoleTextAttribute(h, 7);
					chk = true;
				}
			}
			hold1 = m;
			hold2 = k;
			hold1--;
			hold2--;
			for (; hold1 >= 0 && hold2 >= 0; hold1--, hold2--)//bottom left direction//
			{
				if (board[hold1][hold2] >= 'a' && board[hold1][hold2] <= 'z' ||
					board[hold1][hold2] == 'P' || board[hold1][hold2] == 'R'
					|| board[hold1][hold2] == 'N' || board[hold1][hold2] == 'K')
				{
					break;
				}
				if (board[hold1][hold2] == 'B' || board[hold1][hold2] == 'Q')
				{
					chks[4] = true;
					SetConsoleTextAttribute(h, 7);
					chk = true;
				}
			}
			hold1 = m;
			hold2 = k;
			hold1--;
			hold2++;
			for (; hold1 >= 0 && hold2 <= 7; hold1--, hold2++)
			{
				if (board[hold1][hold2] >= 'a' && board[hold1][hold2] <= 'z' ||
					board[hold1][hold2] == 'P' || board[hold1][hold2] == 'R'
					|| board[hold1][hold2] == 'N' || board[hold1][hold2] == 'K')
				{
					break;
				}

				if (board[hold1][hold2] == 'B' || board[hold1][hold2] == 'Q')
				{
					chks[5] = true;
					SetConsoleTextAttribute(h, 7);
					chk = true;
				}
			}
			hold1 = m;
			hold2 = k;
			hold1++;
			hold2--;
			for (; hold1 <= 7 && hold2 >= 0; hold1++, hold2--)//bottom left direction//
			{
				if (board[hold1][hold2] >= 'a' && board[hold1][hold2] <= 'z' ||
					board[hold1][hold2] == 'P' || board[hold1][hold2] == 'R'
					|| board[hold1][hold2] == 'N' || board[hold1][hold2] == 'K')
				{
					break;
				}
				if (board[hold1][hold2] == 'B' || board[hold1][hold2] == 'Q')
				{
					chks[5] = true;
					SetConsoleTextAttribute(h, 7);
					chk = true;
				}
			}
		}
	}

	SetConsoleTextAttribute(h, 7);
	if (chk == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void frontpage()
{
	SetConsoleTextAttribute(h, 14);
	int n = 70;
	cout << setw(n);
	int m = 177;
	for (int i = 1; i <= 34; i++)
		cout << char(m);
	cout << endl;
	cout << setw(n) << char(m) << "  .___  .  .  .__.  .__.  .__.  " << char(m) << endl;
	cout << setw(n) << char(m) << "  |     |  |  |     |__.  |__.  " << char(m) << endl;
	cout << setw(n) << char(m) << "  |     |--|  |--      |     |  " << char(m) << endl;
	cout << setw(n) << char(m) << "  .___  |  |  |__.  |__|  |__|  " << char(m) << endl << setw(n);
	for (int i = 1; i <= 34; i++)
		cout << char(m);
	char choice;

	cout << "\n\n\nLoad a Previous Game (L)\n";
	cout << "New Classic Game (N)\n";
	cout << "Timed Modes (T)\n";


	bool is_true = true;
	do
	{
		cout << "\n\nSelect One: "; cin >> choice;
		Beep(500, 100);
		if (choice == 'L' || choice == 'l')
		{
			do
			{
				cout << "\nSelect File Number: \nGame1 (1)\nGame2 (2)\nGame3 (3)\n";
				cin >> choice;
				Beep(500, 100);

				if (choice == '1')
				{
					fout.open("game1.txt", ios::in);
					retrieving = true;
					system("cls");
				}
				else if (choice == '2')
				{
					fout.open("game2.txt", ios::in);
					retrieving = true;
					system("cls");
				}
				else if (choice == '3')
				{
					fout.open("game3.txt", ios::in);
					retrieving = true;
					system("cls");
				}
				else
				{
					cout << "\nInvalid Option Selection\n\n";
					Beep(500, 100);
				}
			} while (choice != '1' && choice != '2' && choice != '3');
			is_true = true;
		}
		else if (choice == 'n' || choice == 'N')
		{
			do
			{
				cout << "\nSelect File Number to Save the Game: \nGame1 (1)\nGame2 (2)\nGame3 (3)\n";
				cin >> choice;
				Beep(500, 100);

				if (choice == '1')
				{
					fout.open("game1.txt", ios::out);
					cout << endl;

					cout << "\nPress Any Key to Start the Gameplay: ";
					GetKey();
					Beep(500, 100);
					start_of_prog = time(NULL);
					system("cls");
				}
				else if (choice == '2')
				{
					fout.open("game2.txt", ios::out);
					cout << endl;
					system("cls");
					cout << "\n\nPress Any Key to Start the Gameplay: ";
					GetKey();
					Beep(500, 100);
					start_of_prog = time(NULL);
					system("cls");
				}
				else if (choice == '3')
				{
					fout.open("game3.txt", ios::out);
					cout << endl;
					system("cls");
					cout << "\n\nPress Any Key to Start the Gameplay: ";
					GetKey();
					Beep(500, 100);
					start_of_prog = time(NULL);
					system("cls");
				}
				else
				{
					cout << "\nInvalid Option Selection\n";
				}
			} while (choice != '1' && choice != '2' && choice != '3');
			is_true = true;
		}
		else if (choice == 't' || choice == 'T')
		{
			do
			{
				cout << "\nSelect Mode: \nBlitz (B)\nLightening (L)\nRapid (R)\n";
				Beep(500, 200);


				cin >> choice;
				if (choice == 'B')
				{
					blitzmode = true;
					system("cls");
					cout << "Blitz Mode Started\n";
					settimer = 300;
					start_of_prog = time(NULL);
					return;
				}
				else if (choice == 'L')
				{
					lightenmode = true;
					system("cls");
					cout << "Lightening Mode Started\n";
					start_of_prog = time(NULL);
					return;
				}
				else if (choice == 'R')
				{
					rapidmode = true;
					system("cls");
					cout << "Rapid Mode Started\n";
					settimer = 600;
					start_of_prog = time(NULL);
					return;
				}
				else
				{
					cout << "\nInvalid Option Selection\n";
				}
			} while (choice != 'L' && choice != 'B' && choice != 'R');
			is_true = true;
		}
		else
		{
			cout << "Invalid Option Selection\n";
			is_true = false;
		}
	} while (is_true == false);

}


//ended on 6/12/2022 at 11:36PM//
