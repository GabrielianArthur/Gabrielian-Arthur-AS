#include "Pipe.h"
#include <iostream>
#include <fstream>
#include "utils.h"


std::string Name;
int diametr;
int length;
bool is_broken;
int startid;
int endid;
int Pipe::pMaxId = 0;
int Pipe::Maxid = 0;


int Pipe::Getid() const
{
	return id;
}

std::
string Pipe::GetName() const
{
	return Name;
}

int Pipe::GetMaxid()
{
	return Maxid;
}

int Pipe::GetDiametr() const
{
	return diametr;
}

int Pipe::GetLength() const
{
	return length;
}


bool Pipe::GetStatus() const
{
	return is_broken;
}

int Pipe::GetProductivity() const
{
	return length;
}



Pipe::Pipe(std::ifstream& fin)
{
	fin.ignore();
	std::getline(fin, Name);
	fin 
		>> length
		>> diametr
		>> is_broken
		>> startid
		>> endid;
}


void Pipe::edit_Pipe()
{
   is_broken = !is_broken;
}

//void Pipe::editChange()
//{
//	used = !used;
//}

void Pipe::SaveToFile(std::ofstream& fout)
{
	fout << Name << '\n'
		<< length << '\n'
		<< diametr << '\n'
		<< is_broken << '\n'
		<< startid << '\n'
		<< endid << '\n';
}

std::ostream& operator << (std::ostream& out, const Pipe& p) 
{
		out << "\t PIPE info: " << std::endl;
		out << "Name: " << p.Name << std::endl;
		out << "Diameter: " << p.diametr << std::endl;
		out << "Productivity: " << p.GetProductivity() << std::endl;
		out << "Length: " << p.length << std::endl;
		out << (p.is_broken ? "Under repair" : "Not in repair") << std::endl;
	return out;
}

std::istream& operator >> (std::istream& in, Pipe& p) {
	std::cout << "Type name:" << std::endl;
	std::cin.ignore(256, '\n');
	getline(in, p.Name, '\n');
	std::cout << "Type pipe length" << std::endl;
	p.length = proverka(0, 100000);
	std::cout << "Type pipe diametr" << std::endl;
	p.diametr = proverka(0, 100000);
	p.is_broken = false;	
	p.startid = -1;
	p.endid = -1;
	return in;
}



void Pipe::Edit()
{
	if (is_broken)
		std::cout << "\nThe pipe does not need to be repaired.\n";
	else
		std::cout << "\nThe pipe is broken!\n";
	std::cout << "Whta do you want to do with pipe?\n"
		<< "1 - To fix/To break\n"
		<< "0 and etc. - Exit\n";
	int input;
	proverka2(input, "Enter: ");
	switch (input)
	{
	case 1:
	{
		is_broken = !is_broken;
		std::cout << "Pipe repair completed successfully!\n";
	}
	default:
	{
		std::cout << "You are out of editing mode.\n";
		break;
	}
	}
}
void Pipe::IsBroken()
{
	is_broken = false;
}
Pipe::Pipe()
{}
