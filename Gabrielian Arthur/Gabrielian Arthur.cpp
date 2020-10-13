//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.


#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

int Input_integer(string text = "Type value: ", int min = 0, int max = 10000);
double Input_double(string text = "Type value: ", double min = 0, double max = 10000);

struct Pipe
{
    int id;
    double diameter;
    double length;
    bool need_to_repair;

};

struct CS
{
    int id;
    string Name;
    int count_workshops;
    int count_running_workshops;
    int efficiency;

};

//Everything with pipe
Pipe createPipe(int id)
{
 Pipe p;
 p.id = id;
 p.length = Input_double("Type pipe length: ");
 p.diameter = Input_double("Type pipe diameter: ");
 p.need_to_repair = false;

 return p;
}

void Pipe_info(const Pipe& pipe) {
    cout << "Output information about the pipe " << pipe.id << "\n"
        << "Pipe length: " << pipe.length << "\n"
        << "Pipe diameter: " << pipe.diameter << "\n"
        << "Pipe status: " << pipe.need_to_repair << endl;
}

void change_Pipe_status(Pipe& pipe) {
    pipe.need_to_repair = !pipe.need_to_repair;
    cout << "Pipe status was changed to: " << pipe.need_to_repair << endl;

}

bool pipe_read_from_file(Pipe& p) {
    ifstream fin;
    fin.open("pipe_info.txt", ios::in);
    if (fin.is_open())
    {
        Pipe p;
        fin >> p.id >> p.length >> p.diameter >> p.need_to_repair;
        fin.close();
        return true;
    }
    else {
        cout << "File pipe_info.txt wasnt open" << endl;
        return false;
    }
}

void pipe_write_to_file(const Pipe& pipe)
{
    ofstream fout;
    fout.open("data.txt", ios::out);
    if (fout.is_open())
    {
        fout << pipe.id << endl << pipe.length << endl << pipe.diameter << endl << pipe.need_to_repair << endl;
        fout.close();
        cout << "\nWriting to the file was successful" << endl;
    }
    else {
        cout << "File data.txt wasnt open" << endl;
    }
}



//Everything with CS
CS createCS(int id)
{
    CS cs;
    cs.id = id;

    cout << "Type CS name: " << endl;
    cs.count_workshops = Input_integer("Type number of workshops: ");
    cs.count_running_workshops = Input_integer("Type number of running workshops: ");
    cs.efficiency = Input_integer("Type СS efficiency: ");

    return cs;
}

void CS_info(const CS& cs) {
    cout << "Output information about the compressor station " << cs.id << "\n"
        << "CS name: " << cs.Name << "\n"
        << "Count of workshops: " << cs.count_workshops << "\n"
        << "Count of running workshops: " << cs.count_running_workshops << endl;
}

void edit_CS(CS& cs) {
    string input_text = "Type number of running workshops: ";
    int num = Input_integer(input_text);
    cs.count_running_workshops = num;
    cout << "The number of operating workshops at the compressor station " << cs.id
        << "\nwas changed to " << cs.count_running_workshops << endl;
}

bool cs_read_from_file(CS& cs)
{
    ifstream fin;
    fin.open("cs_info.txt", ios::in);
    if (fin.is_open())
    {
        CS cs;
        fin >> cs.id >> cs.Name >> cs.count_workshops
            >> cs.count_running_workshops >> cs.efficiency;
        fin.close();
        return true;
    }
    else {
        cout << "File data.txt wasn't open" << endl;
        return false;
    }
}

void cs_write_to_file(const CS& cs)
{
    ofstream fout;
    fout.open("data.txt", ios::out);
    if (fout.is_open())
    {
        fout << cs.id << cs.Name << cs.count_workshops
            << cs.count_running_workshops << cs.efficiency;
        fout.close();
        cout << "\nWriting to the file was successful" << endl;
    }
    else {
        cout << "File data.txt wasn't open" << endl;
    }
}





void PrintMenu()
{
    cout << "\n"
        << "1. Create pipe" << "\n"
        << "2. Create compressor" << "\n"
        << "3. View all info" << "\n"
        << "4. Edit Pipe" << "\n"
        << "5. Edit CS" << "\n"
        << "6. Save to file" << "\n"
        << "7. Load from file" << "\n"
        << "0. Exit" << endl;


}


int main()
{
    Pipe p;
    CS cs;
    int pipe_id = 0;
    int cs_id = 0;
    while (1) {

        PrintMenu();
        int i = 0;
        cout << "Your choice (0-7): ";
        cin >> i;
        cout << '\n';
        switch (i)
        {
        case 1: {
            p = createPipe();
            break;
        }
        case 2: {
            cs = createCS();
            break;
        }
        case 3: {           
                Pipe_info(p);     
                CS_info(cs);

            break;
        }
        case 4: {
                change_Pipe_status(p);
            break;
        }
        case 5: {
                edit_CS(cs);
            break;
        }
        case 6: {
            pipe_write_to_file(p);
            cs_write_to_file(p);
            break;
        }
        case 7: {
            p = pipe_read_from_file();
            cs = cs_read_from_file();
            break;
        }
        case 0: {
            cout << "Goodbye" << endl;
            return 0;
        }
        default: {
            cout << "Wrong action, please type (0-7)" << endl;
        }
        }
    }


    return 0;
}