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
    static int Maxid;

public:
	static int csMaxid;

	double GetPercentWorkingWorkshops() const;

	static int GetMaxid();

	

	int Getid() const;

	CS(std::ifstream& fin);
	void SaveToFile(std::ofstream& fout);

	std::string GetName() const;

	int GetWorking() const;

	int GetWorkshops() const;

	double GetEfficiency() const;

	void edit_CS();

	friend std::ostream& operator << (std::ostream& out, const CS& c);
	friend std::istream& operator >> (std::istream& in, CS& c);
	//friend std::ofstream& operator << (std::ofstream& out, const CS& c);
	//friend std::ifstream& operator >> (std::ifstream& in, CS& c);

	CS();

};

