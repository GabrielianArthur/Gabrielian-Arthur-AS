#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "Pipe.h"
#include "Compressor.h"
#include "GTS.h"
#include "utils.h"


using namespace std;


void save_to_file(const unordered_map<int, Pipe>& p, const unordered_map<int, CS>& c) {
	ofstream fout;
	string filename;
	cout << "Type filename:" << std::endl;
	cin.ignore(256, '\n');
	getline(cin, filename, '\n');
	fout.open(filename, ios::out);
	if (fout.is_open()) {
		fout << p.size() << endl << c.size() << endl; 
		for (const auto& it : p)
		{
			fout << it.second;
		}
		for (const auto& it : c)
		{
			fout << it.second;
		}
		fout.close();
	}
}

void load_from_file(unordered_map <int, Pipe>& p, unordered_map <int, CS>& c) {
	ifstream fin;
	int countP, countC;
	string filename;
	cout << "Vvedite filename:" << std::endl;
	cin.ignore(256, '\n');
	getline(cin, filename, '\n');
	fin.open(filename, ios::in);
	if (fin.is_open()) {
		fin >> countP >> countC;
		p.reserve(countP);
		c.reserve(countC);
		for (int i = 0; i < countP; i++)
		{
			Pipe LoadedPipe;
			fin >> LoadedPipe;
			p.insert({ LoadedPipe.Getid(),LoadedPipe });
		}
		for (int i = 0; i < countC; i++)
		{
			CS LoadedCS;
			fin >> LoadedCS;
			c.insert({ LoadedCS.Getid(), LoadedCS});
		}
		fin.close();
	}
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
	cout << "8. Find pipes by Name" << endl;
	cout << "9. Find pipes by Status" << endl;
	cout << "10. Find compressors by Name" << endl;
	cout << "11. Find compressors by percent" << endl;
	cout << "12. Batch editing of pipes" << endl;
	cout << "13. Delete Pipe" << endl;
	cout << "14. Delete CS" << endl;
	cout << "15. Add CS to GTS" << endl;
	cout << "16. Add Pipe to GTS" << endl;
	cout << "17. Connect CSs" << endl;
	cout << "18. Topologycal sort" << endl;
	cout << "0. Exit\n";
}

template<typename T>
using FilterP = bool(*)(const Pipe& p, T param);

bool CheckByName(const Pipe& p, string param) {
	return p.GetName() == param;
}
bool CheckByStatus(const Pipe& p, bool param) {
	return p.GetStatus() == param;
}

template <typename T>
vector<int> FindPipeByFilter(const unordered_map<int, Pipe>& map, FilterP<T> f, T param) {
	vector<int> res;
	for (const auto& it : map) {
		if (f(it.second, param)) {
			res.push_back(it.first);
		}
	}
	return res;
}

template<typename T>
using FilterC = bool(*)(const CS& c, T param);

bool CheckByName(const CS& c, string param) {
	return c.GetName() == param;
}
bool CheckByPercent(const CS& c, double param) {
	return (c.GetPercentWorkingWorkshops() >= param);
}

template <typename T>
vector<int> FindCompressorByFilter(const unordered_map<int, CS>& map, FilterC<T> f, T param) {
	vector<int> res;
	for (const auto& it : map) {
		if (f(it.second, param)) {
			res.push_back(it.first);
		}
	}
	return res;
}


void PacketRedactTrub(unordered_map<int, Pipe>& map) {
	cout << "\tSelect thу pipe in order to edit: " << endl;
	cout << "\t1. Po statusu v remonte" << endl;
	cout << "\t2. Po statusu ne v remonte" << endl;
	cout << "\t3. Po viboru polzovatelya" << endl;
	cout << "\t0. Back" << endl;
	switch (proverka(0, 3))
	{
	case 1:
	{
		for (int i : FindPipeByFilter(map, CheckByStatus, true))
			map.find(i)->second.edit_Pipe();
		break;
	}
	case 2:
	{
		for (int i : FindPipeByFilter(map, CheckByStatus, false))
			map.find(i)->second.edit_Pipe();
		break;
	}
	case 3: {
		vector<int> vec;
		while (1) {
			cout << "Type ID" << endl;
			vec.push_back(proverka(0, Pipe::GetMaxid()));
			cout << "Add another one?" << endl << "\t 0. No" << endl << "\t 1. Yes" << endl;
			if (proverka(0, 1) == 0)
				break;
		}
		for (auto i : vec) {
			if (map.find(i) != map.end())
				map.find(i)->second.edit_Pipe();
		}
		break;
	}
	case 0: {
		return;
	}
	}
}

template<typename T>
bool del(unordered_map<int, T>& map, int id) {
	return map.erase(id);
}


int main()
{
	//setlocale(LC_ALL, "Russian");
	GTS GTS;
	unordered_map <int, Pipe> pipes;
	unordered_map <int, CS> CSs;

	int i;
	while (1)
	{
		cout << "Select action:" << endl;
		print_menu();
		i = proverka(0, 18);
		switch (i)
		{
		case 1:
		{
			while (1) {
				Pipe pipe;
				cin >> pipe;
				pipes.insert({ pipe.Getid(), pipe });
				cout << "Add another one??" << endl << "\t 0. No" << endl << "\t 1. Yes" << endl;
				if (proverka(0, 1) == 0)
					break;
			}

			break;
		}
		case 2:
		{
			while (1) {
				CS comp;
				cin >> comp;
				CSs.insert({ comp.Getid(), comp });
				cout << "Add another one??" << endl << "\t 0. No" << endl << "\t 1. yes" << endl;
				if (proverka(0, 1) == 0)
					break;
			}
			break;
		}
		case 3:
		{
			for (const auto& it : pipes) {
				cout << it.second;
			}
			for (const auto& it : CSs) {
				cout << it.second;
			}
			break;
		}
		case 4:
		{
			//Pipe p = SelecetObject(pipes);
			//if (pipes.size() != 0) {
			//	p.edit_Pipe();
			//}
			//else {
			//	cout << "You haven't added any pipes yet" << endl;
			//}

			cout << "Pipe id: " << endl;
			unordered_map<int, Pipe>::iterator iter = pipes.find(proverka(0, Pipe::GetMaxid()));
			if (iter == pipes.end())
				cout << "Pipe  doesn't exist" << endl;
			else
				iter->second.edit_Pipe();
			break;
		}
		case 5:
		{
			//CS cs = SelecetObject(CSs);
			//if (CSs.size() != 0) 
			//{
			//	cs.edit_CS();
			//}
			//else 
			//{
			//	cout << "You haven't added any compressor stations yet" << endl;
			//}
			cout << "Compressor id: " << endl;
			unordered_map<int, CS>::iterator iter = CSs.find(proverka(0, CS::GetMaxid()));
			if (iter == CSs.end()) {
				cout << "Compressor doesnt exist" << endl;
			}
			else {
				iter->second.edit_CS();	
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
		case 8: {
			cout << "Type name " << endl;
			string name;
			cin.ignore(256, '\n');
			getline(cin, name, '\n');
			for (int i : FindPipeByFilter<string>(pipes, CheckByName, name)) {
				cout << pipes.find(i)->second << endl;
			}
			break;
		}
		case 9: {
			for (int i : FindPipeByFilter(pipes, CheckByStatus, true)) {
				cout << pipes.find(i)->second << endl;
			}
			break;
		}
		case 10: {
			cout << "Type name " << endl;
			string name;
			cin.ignore(256, '\n');
			getline(cin, name, '\n');
			for (int i : FindCompressorByFilter<string>(CSs, CheckByName, name)) {
				cout << CSs.find(i)->second << endl;
			}
			break;
		}
		case 11: {
			cout << "Type percent of not working compressor stations:  " << endl;
			for (int i : FindCompressorByFilter(CSs, CheckByPercent, proverka(0.0, 100.0))) {
				cout << CSs[i] << endl;
			}
			break;
		}
		case 12: {
			PacketRedactTrub(pipes);
			break;
		}
		case 13: {
			while (1) {
				cout << "Enter the id " << endl;
				if (del(pipes, proverka(0, Pipe::GetMaxid())))
					cout << "Pipe is deleted" << endl;
				else
					cout << "Pype doesn't exist" << endl;
				cout << "Delete another one?" << endl << "\t 0. No" << endl << "\t 1. yes" << endl;
				if (proverka(0, 1) == 0)
					break;
			}
			break;
		}
		case 15: {
			cout << "Enter CS id" << endl;
			GTS.AddCS(CSs, proverka(0, CS::GetMaxid()));
			break;
		}
		case 16: {
			cout << "Enter Pipe id" << endl;
			GTS.AddPipe(pipes, proverka(0, Pipe::GetMaxid()));
			break;
		}
		case 17: {
			GTS.ConnectEdges(CSs, pipes);
			break;
		}
		case 18: {
			GTS.CreateAdjacencyMatrix(CSs, pipes);
			GTS.TopSort();
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