#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

using namespace std;

void copy(int array1[52][102], int array2[52][102])
{
	for (int j = 0; j < 52; j++)
	{
		for (int i = 0; i < 102; i++)
			array2[j][i] = array1[j][i];
	}
}

void Leben(int array[52][102], char auswahl)
{
	int temp[52][102];
	copy(array, temp);
	for (int j = 1; j < 51; j++)
	{
		for (int i = 1; i < 101; i++)
		{
			if (auswahl == 'm')
			{
				int zaehlen = 0;

				if (array[j - 1][i] == 1)           //West
					zaehlen++;
				if (array[j - 1][i - 1] == 1)       //Süd West
					zaehlen++;
				if (array[j][i - 1] == 1)           //Süd
					zaehlen++;
				if (array[j + 1][i - 1] == 1)       //Süd Ost
					zaehlen++;
				if (array[j + 1][i] == 1)           //Ost
					zaehlen++;
				if (array[j + 1][i + 1] == 1)       //Nord Ost
					zaehlen++;
				if (array[j][i + 1] == 1)           //Nord
					zaehlen++;
				if (array[j - 1][i + 1] == 1)       //Nord West
					zaehlen++;


				if (zaehlen < 2 || zaehlen > 3)
					temp[j][i] = 0;
				if (zaehlen == 2)
					temp[j][i] = array[j][i];
				if (zaehlen == 3)
					temp[j][i] = 1;
			}

			else if (auswahl == 'v')
			{
				int zaehlen = 0;
				zaehlen = array[j - 1][i] +			//W
					array[j][i - 1] +			//S
					array[j + 1][i] +			//O
					array[j][i + 1];			//N
				if (zaehlen < 2 || zaehlen > 3)
					temp[j][i] = 0;
				if (zaehlen == 2)
					temp[j][i] = array[j][i];
				if (zaehlen == 3)
					temp[j][i] = 1;
			}
		}
	}
	copy(temp, array);
}

bool vergleichen(int array1[52][102], int array2[52][102])
{
	int zaehlen = 0;
	for (int j = 0; j < 52; j++)
	{
		for (int i = 0; i < 102; i++)
		{
			if (array1[j][i] == array2[j][i])
				zaehlen++;
		}
	}
	if (zaehlen == 52 * 102)
		return true;
	else
		return false;
}

void ausgeben(int array[52][102])
{
	for (int j = 1; j < 51; j++)
	{
		for (int i = 1; i < 101; i++)
		{
			if (array[j][i] == 1)
				cout << '#';
			else
				cout << ' ';
		}
		cout << endl;
	}
}

int main()
{
	int gen0[52][102];
	int todo[52][102];
	int backup[52][102];
	char neighborhood;
	char nochmal;
	char cont;
	bool comparison;
	string decoration;

	cout << endl << "Dieses Programm ist eine C++-Implementierung von John Conway's Game of Life."
		<< endl << "Damit kann man simulieren, wie \"Zellen\" miteinander interagieren." << endl
		<< endl << "Es gibt zwei Arten von Nachbarschaften, die Sie waehlen koennen, die"
		<< endl << "Moore- und die Von-Neumann-Nachbarschaft.  Die Moore-Nachbarschaft prueft"
		<< endl << "alle 8 umgebenden Zellen, waehrend die Von-Neumann-Nachbarschaft"
		<< endl << "nur die 4 Himmelsrichtungen: (Norden, Osten, Sueden, und Westen) prueft." << endl
		<< endl << "Die Regeln des \"Game of Life\" lauten wie folgt:" << endl
		<< endl << "1. Jede lebende Zelle mit weniger als zwei lebenden Nachbarn stirbt, wie bei einer Unterbevoelkerung."
		<< endl << "2. Jede lebende Zelle mit zwei oder drei lebenden Nachbarn lebt in der naechsten Generation weiter."
		<< endl << "3. Jede lebende Zelle mit mehr als drei lebenden Nachbarn stirbt, wie durch Ueberbevoelkerung."
		<< endl << "4. Jede tote Zelle mit genau drei lebenden Nachbarn wird zu einer lebenden Zelle, wie durch Reproduktion." << endl
		<< endl << "Die Anfangskonfiguration (Generation 0) des Brettes wird zufaellig bestimmt."
		<< endl << "Alle hundert Generationen erhalten Sie die Moeglichkeit, die Simulation zu beenden oder fortzusetzen."
		<< endl << "Wenn ein System \"stabil\" wird (das heisst, das System aendert sich nicht von einer"
		<< endl << "Generation zur naechsten), wird die Simulation automatisch beendet." << endl << endl;

	do
	{
		do
		{
			cout << "Welche Simulation moechten Sie nutzen (m oder v): ";
			cin >> neighborhood;
		} while (neighborhood != 'm' && neighborhood != 'v');
		system("clear");
		int i = 0;
		do
		{
			srand(time(NULL));
			for (int j = 1; j < 51; j++)
			{
				for (int i = 1; i < 101; i++)
					gen0[j][i] = rand() % 2;
			}

			if (i < 10)
				decoration = "#############";
			else if (i >= 10 && i < 100)
				decoration = "##############";
			else if (i >= 100 && i < 1000)
				decoration = "###############";
			else if (i >= 1000 && i < 10000)
				decoration = "################";
			else
				decoration = "#################";
			cout << decoration << endl << "Generation " << i
				<< ":" << endl << decoration << endl << endl;


			if (i == 0)
				copy(gen0, todo);
			copy(todo, backup);
			ausgeben(todo);
			Leben(todo, neighborhood);
			i++;
			Sleep(2);
			if (i % 100 == 1 && i != 1)
			{
				cout << endl;
				do
				{
					cout << "Would you like to continue this simulation? (y/n): ";
					cin >> cont;
				} while (cont != 'y' && cont != 'n');
				if (cont == 'n')
					break;
			}
			comparison = vergleichen(todo, backup);
			if (comparison == false)
				system("CLS");
			if (comparison == true)
				cout << endl;
		} while (comparison == false);
		do
		{
			cout << "Moechten Sie eine weitere Simulation durchfuehren? (y/n): ";
			cin >> nochmal;
		} while (nochmal != 'y' && nochmal != 'n');
	} while (nochmal == 'y');
	return 0;
}