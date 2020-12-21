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
	bool is_broken;

public:
    static int Maxid;

	int Getid() const;

	std::string GetName() const;

	int GetDiametr() const;

	int GetLength() const;

	bool GetStatus() const;

	void edit_Pipe();

	friend std::ostream& operator << (std::ostream& out, const Pipe& p);
	friend std::istream& operator >> (std::istream& in, Pipe& p);
	friend std::ofstream& operator << (std::ofstream& out, const Pipe& p);
	friend std::ifstream& operator >> (std::ifstream& in, Pipe& p);

	Pipe();
};

