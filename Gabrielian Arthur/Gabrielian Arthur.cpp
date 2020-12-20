#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct CS
{
	int id;
	string Name;
	int amount_workshops;
	int amount_running_workshops;
	float efficiency;
};
struct Pipe
{
	int id;
	int diametr;
	int length;
	bool is_broken;
};

template <typename T>
T proverka(T min, T max, string text1, string text2)
{
	T value;
	
	cout << text1;
	while ((cin >> value).fail() || value > max || value < min)
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << text2 << "Choose between (" << min << " - " << max << ")" << endl;
	}
	return value;
}


void edit_Pipe(Pipe& pipe) 
{
	pipe.is_broken = !pipe.is_broken;
	cout << "Pipe status was changed to: " << pipe.is_broken << endl;
}

void edit_CS(CS& cs) 
{
	int k = proverka(0, cs.amount_workshops, "Type the amount of running workshops\n", "Incorrect number of running workshops\n");
	cs.amount_running_workshops = k;
	cout << "The number of running workshops at the compressor station " << cs.id
		<< "\nwas changed to " << cs.amount_running_workshops << endl;
}


ostream& operator << (ostream& out, const CS& c) {
	if (c.id == -1) {
		out << "\t COMPRESSOR info: " << endl;
		out << "Name: " << c.Name << endl;
		out << "id: " << c.id << endl;
		out << "Number of workshops: " << c.amount_workshops << endl;
		out << "Number of working workshops: " << c.amount_running_workshops << endl;
		out << "Efficienty: " << c.efficiency << endl;
	}
	else {
		out << "Compressor doesnt exist" << endl;
	}
	return out;
}

ostream& operator << (ostream& out, const Pipe& p) {
	if (p.id == -1) {
		out << "\t PIPE info: " << endl;
		out << "Diameter: " << p.diametr << endl;
		out << "Length: " << p.length << endl;
		out << "id: " << p.id << endl;
		out << (p.is_broken ? "Under repair" : "Not in repair") << endl;
	}
	else {
		cout << "Pipe doesnt exist" << endl;
	}
	return out;
}
istream& operator >> (istream& in, CS& c) {
	cout << "Type name:" << endl;
	cin.ignore(256, '\n');
	getline(in, c.Name, '\n');
	c.amount_workshops = proverka(0, 100000, "Type the amount of workshops\n", "The amount of workshops must be positive integer between 0 and 100000\n");
	c.amount_running_workshops = proverka(0, c.amount_workshops, "Type the amount of running workshops\n", "Incorrect number of running workshops\n");
	c.efficiency = proverka(0,100, "Type the efficiency\n", "Incorrect efficiency(between 0 and 100)\n");
	c.id = 1;
	return in;
}

istream& operator >> (istream& in, Pipe& p) {
	p.length = proverka(0, 100000, "Type pipe length\n", "The length must be a positive integer between 0 and 100000\n");
	p.diametr = proverka(0, 100000, "Type pipe diametr\n", "The diametr must be a positive integer between 0 and 100000\n");
	p.is_broken = false;
	p.id = 1;
	return in;
}


void save_to_filePipe(const Pipe& p, ofstream& fout)
{
	fout << p.id << endl << p.length << endl << p.diametr << endl << p.is_broken << endl;

}


void save_to_fileCS(const CS& cs, ofstream& fout)
{
	fout << cs.id << endl << cs.Name << endl << cs.amount_workshops << endl << cs.amount_running_workshops << endl << cs.efficiency << endl;
}

void save_to_file(const vector<Pipe>& p, const vector<CS>& c) {
	ofstream fout;
	fout.open("Data.txt", ios::out);
	if (fout.is_open()) {
		fout << p.size() << endl << c.size() << endl; 
		for (Pipe it : p)
		{
			save_to_filePipe(it, fout);
		}
		for (CS it : c)
		{
			save_to_fileCS(it, fout);
		}
		fout.close();
	}
}


Pipe loadingPipe(ifstream& fin)
{
	Pipe p;
	fin >> p.id;
	fin >> p.length >> p.diametr >> p.is_broken;
	return p;
}
CS loadingCS(ifstream& fin)
{
	CS cs;
	fin >> cs.id;
	fin.ignore(256, '\n');
	getline(fin, cs.Name);
	fin >> cs.amount_workshops >> cs.amount_running_workshops >> cs.efficiency;
	return cs;
}

void load_from_file(vector <Pipe>& p, vector <CS>& c) {
	ifstream fin;
	int countP, countC;
	fin.open("Data.txt", ios::in);
	if (fin.is_open()) 
	{
		fin >> countP >> countC;
		for (int i = 0; i < countP; i++)
		{
			p.push_back(loadingPipe(fin));
		}
		for (int i = 0; i < countC; i++)
		{
			c.push_back(loadingCS(fin));
		}
		fin.close();
	}
}

template <typename T>
T& SelecetObject(vector<T>& vec) {
	unsigned int index=proverka(1u, vec.size(), "Type index of:\n", "Incorrect selection. Select an existing object\n");
	return vec[index - 1];
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


int main()
{
	//setlocale(LC_ALL, "Russian");
	vector<Pipe> pipes;
	vector<CS> CSs;

	int i;
	while (1)
	{
		cout << "Select action:" << endl;
		print_menu();
		i = proverka(0, 7, "Choose the action\n", "Wrong action, please type (0-7)\n");
		switch (i)
		{
		case 1:
		{
			Pipe pipe;
			cin >> pipe;
			pipes.push_back(pipe);

			break;
		}
		case 2:
		{
			CS cs;
			cin >> cs;
			CSs.push_back(cs);
			break;
		}
		case 3:
		{
			if (pipes.size() == 0) { cout << "You haven't added any pipes yet\n"; }
			else {
				cout << SelecetObject(pipes);

			}
			if (CSs.size() == 0) { cout << "You haven't added any compressor stations yet\n"; }
			else {

				cout << SelecetObject(CSs);

			}
			break;
		}
		case 4:
		{
			if (pipes.size() != 0) {
				edit_Pipe(SelecetObject(pipes));
			}
			else {
				cout << "You haven't added any pipes yet" << endl;
			}
			break;
		}
		case 5:
		{
			if (CSs.size() != 0) 
			{
				edit_CS(SelecetObject(CSs));
			}
			else 
			{
				cout << "You haven't added any compressor stations yet" << endl;
			}
			break;
		}
		case 6:
		{
			save_to_file(pipes, CSs);
			break;
		}
		case 7:
		{
			load_from_file(pipes, CSs);
			break;
		}
		case 0:
		{
			cout << "Bye!!!";
			return(0);
			break;
		}
		}
		if (i != 0)
			system("pause");

	}

	return(0);

}