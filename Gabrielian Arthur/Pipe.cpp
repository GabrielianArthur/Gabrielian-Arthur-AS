#include "Pipe.h"
#include <iostream>
#include "utils.h"

//int Pipe::Maxid = 0;

int Pipe::Getid() const
{
	return id;
}

void Pipe::Setid(int new_id)
{
	id = new_id;
}
std::
string Pipe::GetName() const
{
	return Name;
}

void Pipe::SetName(std::string new_name)
{
	Name = new_name;
}
int Pipe::GetDiametr() const
{
	return diametr;
}

void Pipe::SetDiametr(int new_diametr)
{
	diametr =new_diametr;
}

int Pipe::GetLength() const
{
	return length;
}

void Pipe::SetLength(int new_length)
{
	length = new_length;
}

bool Pipe::GetStatus() const
{
	return is_broken;
}

void Pipe::SetStatus(bool status)
{
	is_broken = status;
}

void Pipe::edit_Pipe(Pipe& pipe)
{
   pipe.is_broken = !pipe.is_broken;
   std::cout << "Pipe status was changed to: " << pipe.is_broken << std::endl;
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
	p.length = proverka(0, 100000, "Type pipe length\n", "The length must be a positive integer between 0 and 100000\n");
	p.diametr = proverka(0, 100000, "Type pipe diametr\n", "The diametr must be a positive integer between 0 and 100000\n");
	p.is_broken = false;
	return in;
}

std::ofstream& operator << (std::ofstream& out, const Pipe& p)
{
	out << p.GetName() << std::endl << p.GetDiametr() << std::endl << p.GetLength() << std::endl << p.GetStatus() << std::endl;
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
	length = 0;
	diametr = 0;
	is_broken = false;
}
