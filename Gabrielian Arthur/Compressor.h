#pragma once
#include <iostream>
#include <string>
#include "utils.h"

class CS
{
	static int Maxid;
	int id;
	std::string Name;
	int amount_workshops;
	int amount_running_workshops;
	float efficiency;

public:
	int Getid() const;
	void Setid(int);

	std::string GetName() const;
	void SetName(std::string);

	int GetWorking() const;
	void SetWorking(int);

	int GetWorkshops() const;
	void SetWorkshops(int);

	double GetEfficiency() const;
	void SetEfficiency(double);

	void edit_CS(CS& cs);

	friend std::ostream& operator << (std::ostream& out, const CS& c);
	friend std::istream& operator >> (std::istream& in, CS& c);


	friend std::ofstream& operator << (std::ofstream& out, const CS& c);
	friend std::ifstream& operator >> (std::ifstream& in, CS& c);

	CS();

};

