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
	fin >> id
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
void CS::edit_CS()
{
	std::cout << "Type amount workshops" << std::endl;
	int k = proverka(0, amount_workshops);
	amount_running_workshops = k;
	std::cout << "The number of running workshops at the compressor station " << id
		<< "\nwas changed to " << amount_running_workshops << std::endl;
	/*std::cout << "The number of running workshops at the compressor station was changed to " << amount_running_workshops << std::endl;*/
}

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


/*std::ofstream& operator<<(std::ofstream& out, const CS& c)
{
	out << c.Name << std::endl << c.amount_workshops << std::endl << c.amount_running_workshops << std::endl << c.efficiency << std::endl;
	return out;
}
std::ifstream& operator>>(std::ifstream& in, CS& c)
{
	in.ignore(256, '\n');
	std::getline(in, c.Name);
	in >> c.amount_workshops >> c.amount_running_workshops >> c.efficiency;
	*//*return in;
}*/
CS::CS()
{
	//id = Maxid++;
	Name = "Unknown";
	//amount_running_workshops = 0;
	//amount_workshops = 0;
	//efficiency = 0.0;
}