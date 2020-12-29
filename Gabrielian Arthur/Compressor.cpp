#include "Compressor.h"
#include <iostream>
#include <string>
#include <fstream>
#include "utils.h"

int CS::csMaxid = 0;
int CS::Maxid = 0;

CS::CS(std::ifstream& fin)
{
	fin.ignore();
	std::getline(fin, Name);
	fin
		>> amount_workshops
		>> amount_running_workshops
		>> efficiency;
}

int CS::Getid() const
{
	return id;
}

int CS::GetMaxid()
{
	return Maxid;
}

std::string CS::GetName() const
{
	return Name;
}


int CS::GetWorking() const
{
	return amount_running_workshops;
}


int CS::GetWorkshops() const
{
	return amount_workshops;
}


double CS::GetEfficiency() const
{
	return efficiency;
}

double CS::GetPercentWorkingWorkshops() const
{
	return  100.0 * (amount_workshops - amount_running_workshops) / amount_workshops;
}
//void CS::edit_CS()
//{
//	std::cout << "Type amount workshops" << std::endl;
//	int k = proverka(0, amount_workshops);
//	amount_running_workshops = k;
//	std::cout << "The number of running workshops at the compressor station " << id
//		<< "\nwas changed to " << amount_running_workshops << std::endl;
//}

void CS::SaveToFile(std::ofstream& fout)
{
	fout << Name << '\n'
		<< amount_workshops << '\n'
		<< amount_running_workshops << '\n'
		<< efficiency << '\n';
}

std::istream& operator >> (std::istream& in, CS& c) {
	std::cout << "Type name:" << std::endl;
	std::cin.ignore(256, '\n');
	getline(in, c.Name, '\n');
	std::cout << "Type the amount of workshops" << std::endl;
	c.amount_workshops = proverka(0, 100000);
	std::cout << "Type the amount of running workshops" << std::endl;
	c.amount_running_workshops = proverka(0, c.amount_workshops);
	std::cout << "Type the the efficiency" << std::endl;
	c.efficiency = proverka(0, 100);
	return in;
}

std::ostream& operator << (std::ostream& out, const CS& c) {
		out << "\t COMPRESSOR info: " << std::endl;
		out << "Name: " << c.Name << std::endl;
		out << "Number of workshops: " << c.amount_workshops << std::endl;
		out << "Number of working workshops: " << c.amount_running_workshops << std::endl;
		out << "Efficienty: " << c.efficiency << std::endl;
	return out;
}


void CS::Edit_CS()
{
	std::cout << "Now is working " << amount_running_workshops << "/" << amount_workshops<< " workshops\n";
	int workingShopsCount;
	proverka2(workingShopsCount, "Enter new amount of working workshops: ");
	while (workingShopsCount > amount_workshops)
	{
		std::cout << "Error! The number of working workshops cannot be greater than the total number of workshops\n";
		proverka2(workingShopsCount, "Enter new amount of working workshops: ");
	}
	amount_running_workshops = workingShopsCount;
}
CS::CS()
{
	id = Maxid++;
	Name = "Unknown";
	amount_running_workshops = 0;
	amount_workshops = 0;
	efficiency = 0.0;
}