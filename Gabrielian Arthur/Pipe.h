#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "utils.h"
#include <cmath>


class Pipe
{
	
	int id;
	std::string Name;
	int diametr;
	int length;
	//double Weight;
	bool is_broken;
	static int Maxid;
	//int start;
	//int end;
	bool used;

public:
	static int pMaxId;
	int startid;
	int endid;
	static int GetMaxid();

	int Getid() const;

	std::string GetName() const;
	//double GetWeight() const;

	void editChange();

	void edit_Pipe();

	friend std::ostream& operator << (std::ostream& out, const Pipe& p);
	friend std::istream& operator >> (std::istream& in, Pipe& p);
	//friend std::ofstream& operator << (std::ofstream& out, const Pipe& p);
	//friend std::ifstream& operator >> (std::ifstream& in, Pipe& p);

	Pipe();

	Pipe(std::ifstream& fin);
	int GetProductivity() const;
	int GetDiametr() const;
	int GetLength() const;
	bool GetStatus() const;
	void Edit();
	void SaveToFile(std::ofstream& fout);
	void IsBroken();

};

