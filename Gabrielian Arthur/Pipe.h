#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "utils.h"


class Pipe
{
	static int Maxid;
	int id;
	std::string Name;
	int diametr;
	int length;
	bool is_broken;

public:

	int Getid() const;
	void Setid(int);

	std::string GetName() const;
	void SetName(std::string);

	int GetDiametr() const;
	void SetDiametr(int);

	int GetLength() const;
	void SetLength(int);

	bool GetStatus() const;
	void SetStatus(bool);

	void edit_Pipe(Pipe& pipe);

	friend std::ostream& operator << (std::ostream& out, const Pipe& p);
	friend std::istream& operator >> (std::istream& in, Pipe& p);


	friend std::ofstream& operator << (std::ofstream& out, const Pipe& p);
	friend std::ifstream& operator >> (std::ifstream& in, Pipe& p);

	Pipe();
};

