#include "Compressor.h"
#include <iostream>
#include <string>
#include <fstream>
#include "utils.h"

int CS::Getid() const
{
	return id;
}

void CS::Setid(int new_id)
{
	id = new_id;
}

std::string CS::GetName() const
{
	return Name;
}

void CS::SetName(std::string new_name)
{
	Name = new_name;
}

int CS::GetWorking() const
{
	return amount_running_workshops;
}

void CS::SetWorking(int new_amount)
{
	amount_running_workshops = new_amount;
}

int CS::GetWorkshops() const
{
	return amount_workshops;
}

void CS::SetWorkshops(int amount)
{
	amount_workshops = amount;
}

double CS::GetEfficiency() const
{
	return efficiency;
}

void CS::SetEfficiency(double new_efficienty)
{
	efficiency = new_efficienty;
}

void CS::edit_CS(CS& cs)
{
	int k = proverka(0, cs.amount_workshops, "Type the amount of running workshops\n", "Incorrect number of running workshops\n");
	cs.amount_running_workshops = k;
	std::cout << "The number of running workshops at the compressor station " << cs.id
		<< "\nwas changed to " << cs.amount_running_workshops << std::endl;
}



std::istream& operator >> (std::istream& in, CS& c) {
	std::cout << "Type name:" << std::endl;
	std::cin.ignore(256, '\n');
	getline(in, c.Name, '\n');
	c.amount_workshops = proverka(0, 100000, "Type the amount of workshops\n", "The amount of workshops must be positive integer between 0 and 100000\n");
	c.amount_running_workshops = proverka(0, c.amount_workshops, "Type the amount of running workshops\n", "Incorrect number of running workshops\n");
	c.efficiency = proverka(0, 100, "Type the efficiency\n", "Incorrect efficiency(between 0 and 100)\n");
	return in;
}

std::ostream& operator << (std::ostream& out, const CS& c) {
	if (c.id >= 0) {
		out << "\t COMPRESSOR info: " << std::endl;
		out << "Name: " << c.Name << std::endl;
		out << "id: " << c.id << std::endl;
		out << "Number of workshops: " << c.amount_workshops << std::endl;
		out << "Number of working workshops: " << c.amount_running_workshops << std::endl;
		out << "Efficienty: " << c.efficiency << std::endl;
	}
	else {
		out << "Compressor doesnt exist" << std::endl;
	}
	return out;
}


std::ofstream& operator<<(std::ofstream& out, const CS& c)
{
	out << c.GetName() << std::endl << c.GetWorkshops() << std::endl << c.GetWorking() << std::endl << c.GetEfficiency() << std::endl;
	return out;
}

std::ifstream& operator>>(std::ifstream& in, CS& c)
{
	in.ignore(256, '\n');
	std::getline(in, c.Name);
	in >> c.amount_workshops >> c.amount_running_workshops >> c.efficiency;
	return in;
}
CS::CS()
{
	id = Maxid++;
	Name = "Unknown";
	amount_running_workshops = 0;
	amount_workshops = 0;
	efficiency = 0.0;
}