#pragma once
#include <iostream>
#include <string>
#include "utils.h"

class CS
{
	
	int id;
	std::string Name;
	int amount_workshops;
	int amount_running_workshops;
	float efficiency;

public:
	static int Maxid;

	int Getid() const;

	std::string GetName() const;

	int GetWorking() const;

	int GetWorkshops() const;

	double GetEfficiency() const;

	void edit_CS();

	friend std::ostream& operator << (std::ostream& out, const CS& c);
	friend std::istream& operator >> (std::istream& in, CS& c);
	friend std::ofstream& operator << (std::ofstream& out, const CS& c);
	friend std::ifstream& operator >> (std::ifstream& in, CS& c);

	CS();

};

