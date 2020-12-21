#include "Pipe.h"
#include <iostream>
#include <fstream>
#include "utils.h"

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

double Pipe::GetWeight() const
{
	return length;
}

void Pipe::SetStart(int new_start)
{
	start = new_start;
}

void Pipe::SetEnd(int new_end)
{
	end = new_end;
}

int Pipe::GetStart() const
{
	return start;
}

int Pipe::GetEnd() const
{
	return end;
}
void Pipe::edit_Pipe()
{
   is_broken = !is_broken;
}

void Pipe::editChange()
{
	used = !used;
}

std::ostream& operator << (std::ostream& out, const Pipe& p) 
{
	if (p.id >= 0) {
		out << "\t PIPE info: " << std::endl;
		out << "Name: " << p.Name << std::endl;
		out << "Diameter: " << p.diametr << std::endl;
		out << "Length: " << p.length << std::endl;
		out << "id: " << p.id << std::endl;
		out << (p.is_broken ? "Under repair" : "Not in repair") << std::endl;
	}
	else {
		std::cout << "Pipe doesnt exist" << std::endl;
	}
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
	return in;
}

std::ofstream& operator << (std::ofstream& out, const Pipe& p)
{
	out << p.Name() << std::endl << p.diametr() << std::endl << p.length() << std::endl << p.is_broken() << std::endl;
	return out;
}


std::ifstream& operator >> (std::ifstream& in, Pipe& p)
{
	in.ignore(256, '\n');
	std::getline(in, p.Name);
	in >> p.diametr >> p.length >> p.is_broken;
	return in;
}


Pipe::Pipe()
{
	id = Maxid++;
	Name = "Unknown";
	used = false;
	length = 0;
	diametr = 0;
	is_broken = false;
	start = -1;
	end = -1;
}
