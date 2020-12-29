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
	return sqrt(pow(diametr, 5 / length)) * 10;
}

//double Pipe::GetWeight() const
//{
//	return length;
//}


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

void Pipe::editChange()
{
	used = !used;
}

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
	/*if (p.id >= 0) {*/
		out << "\t PIPE info: " << std::endl;
		out << "Name: " << p.Name << std::endl;
		out << "Diameter: " << p.diametr << std::endl;
		out << "Производительность: " << p.GetProductivity() << std::endl;
		out << "Length: " << p.length << std::endl;
		//out << "id: " << p.id << std::endl;
		out << (p.is_broken ? "Under repair" : "Not in repair") << std::endl;
	//	out << "startid: " << p.startid << std::endl;
		//out << "endid: " << p.endid << std::endl;
	//}
	//else {
	//	std::cout << "Pipe doesnt exist" << std::endl;
	//}
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

//std::ofstream& operator << (std::ofstream& out, const Pipe& p)
//{
//	out << p.Name << std::endl << p.diametr << std::endl << p.length << std::endl << p.is_broken << std::endl;
//	return out;
//}
//
//
//std::ifstream& operator >> (std::ifstream& in, Pipe& p)
//{
//	in.ignore(256, '\n');
//	std::getline(in, p.Name);
//	in >> p.diametr >> p.length >> p.is_broken;
//	return in;
//}

void Pipe::Edit()
{
	if (is_broken)
		std::cout << "\nТруба не нуждается в ремонте.\n";
	else
		std::cout << "\nТруба сломана!\n";
	std::cout << "Что Вы хотите сделать с трубой?\n"
		<< "1 - Починить/Сломать\n"
		<< "0 и пр. - Выйти\n";
	int input;
	proverka2(input, "Введите: ");
	switch (input)
	{
	case 1:
	{
		is_broken = !is_broken;
		std::cout << "Ремонт трубы успешно завершён!\n";
	}
	default:
	{
		std::cout << "Вы вышли из режима редактирования.\n";
		break;
	}
	}
}
void Pipe::IsBroken()
{
	is_broken = false;
}
Pipe::Pipe()
{
	//id = Maxid++;
	//Name = "Unknown";
	//used = false;
	//length = 0;
	//diametr = 0;
	//is_broken = false;
	//start = -1;
	//end = -1;
}
