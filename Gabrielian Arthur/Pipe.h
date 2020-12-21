#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "utils.h"


class Pipe
{
	
	int id;
	std::string Name;
	int diametr;
	int length;
	double Weight;
	bool is_broken;
	static int Maxid;
	int start;
	int end;
	bool used;

public:
	static int GetMaxid();

	int Getid() const;

	std::string GetName() const;

	int GetDiametr() const;

	double GetWeight() const;

	int GetLength() const;

	bool GetStatus() const;

	void SetStart(int);
	void SetEnd(int);

	int GetStart() const;
	int GetEnd() const;

	void editChange();

	void edit_Pipe();

	friend std::ostream& operator << (std::ostream& out, const Pipe& p);
	friend std::istream& operator >> (std::istream& in, Pipe& p);
	friend std::ofstream& operator << (std::ofstream& out, const Pipe& p);
	friend std::ifstream& operator >> (std::ifstream& in, Pipe& p);

	Pipe();
};

