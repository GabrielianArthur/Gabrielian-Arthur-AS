#include <iostream>
#include <fstream>
#include <string>
//#include <vector>
using namespace std;

struct CS
{
	int id;
	string Name;
	int amount_workshops;
	int amount_running_workshops;
	float effect;
};
struct Pipe
{
	int id;
	int diametr;
	int length;
	string is_broken;
};
int proverka1(float m, int max, int min, string s)
{
	while (cin.fail() || (m - floor(m)) || (m > max) || (m < min))
	{
		cout << s;
		cin.clear();
		cin.ignore(256, '\n');
		cin >> m;

	}
	return m;
}

float proverka2(float m, int max, int min, string s)
{
	while ((m > max) || (m < min))
	{
		cout << s;
		cin.clear();
		cin.ignore(256, '\n');
		cin >> m;
	}
	return m;
}

/*int proves(float k, int k1, int k2, string s) {
	while (cin.fail() || (k - floor(k)) || (k > k1) || (k < k2))
	{
		cout << s;
		cin.clear();
		cin.ignore(256, '\n');
		cin >> k;
	}
	return k;
};*/
Pipe CreatePipe()
{
	Pipe p;
	float length1;
	float diametr1;
	p.id = {};
	cout << "Type pipe length" << endl;
	cin >> length1;
	p.length = proverka1(length1, 100000, 0, "The length must be a positive integer between 0 and 100000\n");
	cout << "Type pipe diametr" << endl;
	cin >> diametr1;
	p.diametr = proverka1(diametr1, 100000, 0, "The diametr must be a positive integer between 0 and 100000\n");
	cout << "The pipe is broken or not (0-if it is broken, 1-if it is in a working order)" << endl;
	float k;
	cin >> k;
	k = proverka1(k, 1, 0, "Type 0 or 1!\n");
	if (k == 0)
	{
		p.is_broken = "Yes";
	}
	else if (k == 1)
	{
		p.is_broken = "No";
	}
	return p;
}
CS CreateCS()
{
	CS cs;
	float amount_workshops1;
	float amount_running_workshops1;
	float effect1;
	cs.id = {};
	cout << "Type name " << endl;
	cin >> cs.Name;
	cout << "Type the amount of workshops " << endl;
	cin >> amount_workshops1;
	cs.amount_workshops = proverka1(amount_workshops1, 100000, 0, "The amount of workshops must be positive integer between 0 and 100000\n");
	cout << "Type the amount of running workshops " << endl;
	cin >> amount_running_workshops1;
	cs.amount_running_workshops = proverka1(amount_running_workshops1, amount_workshops1, 0, "Incorrect number of running workshops\n");
	cout << "Type the efficiency " << endl;
	cin >> effect1;
	cs.effect = proverka2(effect1, 100, 0, "Incorrect efficiency(between 0 and 100)\n");
	return cs;
}
void printInformPipe(Pipe p1)
{
	cout << "ID: " << p1.id << "\n";
	cout << "The length: " << p1.length << "\n";
	cout << "The diametr: " << p1.diametr << "\n";
	cout << "Is broken: " << p1.is_broken << "\n";
}
void printInformCS(CS cs1)
{
	cout << "ID: " << cs1.id << "\n";
	cout << "Name: " << cs1.Name << "\n";
	cout << "Amount of workshops: " << cs1.amount_workshops << "\n";
	cout << "Amount of working workshops: " << cs1.amount_running_workshops << "\n";
	cout << "Efficiency: " << round(cs1.effect * 100) / 100 << " %" << "\n";
}
void print_menu() {
	system("cls"); 
	cout << "Menu\n";
	cout << "1. Add a pipe\n";
	cout << "2. Add a CS\n";
	cout << "3. View all objects\n";
	cout << "4. Edit a pipe\n";
	cout << "5. Edit a CS\n";
	cout << "6. Save\n";
	cout << "7. Load\n";
	cout << "0. Exit\n";
}
Pipe loadingPipe(ifstream& myfile)
{
	Pipe p;
	p.id = {};
	myfile >> p.length >> p.diametr >> p.is_broken;
	return p;
}
CS loadingCS(ifstream& myfile)
{
	CS cs;
	cs.id = {};
	myfile >> cs.Name >> cs.amount_workshops >> cs.amount_running_workshops >> cs.effect;
	return cs;
}
void saveinformPipetxt(Pipe p1, ofstream& fout)
{
	fout << p1.length << " " << p1.diametr << " " << p1.is_broken << " ";
}
void saveinformCStxt(CS cs1, ofstream& fout)
{
	fout << cs1.Name << " " << cs1.amount_workshops << " " << cs1.amount_running_workshops << " " << cs1.effect << " ";
}


int main()
{
	//setlocale(LC_ALL, "Russian");
	int choice;
	float vv;
	CS cs2;
	int i = 0, j = 0;
	Pipe p2;
	do {
		print_menu();
		cin >> vv;
		choice = proverka1(vv, 7, 0, "Wrong action, please type (0-7)\n");
		switch (choice) {
		case 1:
		{
			p2 = CreatePipe();
			p2.id = i + 1;
			printInformPipe(p2);
			i++;
			break;
		}
		case 2:
		{
			cs2 = CreateCS();
			cs2.id = j + 1;
			printInformCS(cs2);
			j++;
			break;
		}
		case 3:
		{
			if (i == 0) { cout << "You haven't added any pipes yet\n"; }
			else {
				cout << "Pipes\n";
				printInformPipe(p2);
				cout << "\n";
			}
			if (j == 0) { cout << "You haven't added any compressor stations yet\n"; }
			else {
				cout << "Compressor Stations\n";
				printInformCS(cs2);
				cout << "\n";
			}
			break;
		}
		case 4:
		{
			if (i == 0) { cout << "You haven't added any pipes yet\n"; }
			else {
				if (p2.is_broken == "Yes") { p2.is_broken = "No"; }
				else { p2.is_broken = "Yes"; }
				cout << "The status of the pipe changed\n";
			}
			break;
		}
		case 5:
		{
			int vyb;
			if (j == 0) { cout << "You haven't added any compressor stations yet\n"; }
			else {
				cout << "1. Run workstation\n2. Stop workstation\n";
				cin >> vyb;
				vyb = proverka1(vyb, 2, 1, "1 or 2!");
				if (vyb == 1) {
					if (cs2.amount_running_workshops = cs2.amount_workshops) { cout << "All workshops are in working order"; }
					else {
						cs2.amount_running_workshops = cs2.amount_running_workshops + 1;
					}
				}
				else {
					if (cs2.amount_running_workshops == 0) { cout << "There are no running workshops"; }
					else {
						cs2.amount_running_workshops = cs2.amount_running_workshops - 1;
					}
				}
			}
		}
		case 6:
		{
			ofstream fout;
			fout.open("information.txt");
			if (i == 0) { fout << "You haven't added any pipes yet\n"; }
			else {
				saveinformPipetxt(p2, fout);
			}
			if (j == 0) {
				fout << "\nYou haven't added any compressor stations yet\n";
			}
			else {
				fout << "\n";
				saveinformCStxt(cs2, fout);
			}
			fout.close();
			break;
		}
		case 7:
		{
			i = 0; j = 0;
			string filename;
			cout << "Type file name: ";
			cin >> filename;
			ifstream myfile(filename);
			if (myfile.is_open())
			{
				p2 = loadingPipe(myfile);
				p2.id = i + 1;
				printInformPipe(p2);
				cout << "\n";
				i++;
				myfile.ignore(256, '\n');
				cs2 = loadingCS(myfile);
				cs2.id = j + 1;
				printInformCS(cs2);
				cout << "\n";
				j++;
			}
			myfile.close();
			break;
		}
		case 0:
		{
			cout << "Bye!!!";
		}
		return 0;
		}
	if (choice != 0)
			system("pause");
	} while (choice != 0);
	return 0;
}