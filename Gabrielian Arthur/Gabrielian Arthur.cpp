// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

#include <iostream>
#include <string>

using namespace std;

struct Pipe
{
    string id;
    int diametr;
    int dlina;
    bool need_to_repair = false;

};

struct KS
{
    string id;
    string Name;
    int cehi;
    int cehivrabote;
    int effektiv;

};

Pipe createPipe()
{
 Pipe m;

 m.id = " ";

 cout << "Enter the length" << endl;
 cin >> m.dlina;

 cout << "Enter the length" << endl;
 cin >> m.diametr;
 
 return m;
}

KS createKS()
{
    KS hj;

    hj.id = " ";

    cout << "Enter number of workshops" << endl;

    cin >> hj.cehi;

    cout << "Enter the number of working worksohps" << endl;
    cin >> hj.cehivrabote;

    return hj;
}

int main()

{
    Pipe m;
    m = createPipe();

    KS hj;
    hj = createKS();
    //cout << "Hello World" << endl;
    //int ch;
    //cin >> ch;
    return 0;
}

