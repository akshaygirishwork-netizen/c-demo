#include <iostream>
#include <string>
using namespace std;

// Abstract base class
class Employe
{
protected:
    string name;
    int id;

public:
    Employe(const string &Name, int Id) : name(Name), id(Id) {}

    virtual void showDetails() const  // ← added const
    {
        cout << "Name: " << name << endl;
        cout << "Id: " << id << endl;
    }

    virtual double calculateSalary() const = 0;  // pure virtual

    virtual ~Employe() {}
};

class FullTimeEmploye : public Employe
{
    double monthelySalary;

public:
    FullTimeEmploye(const string &name, int empId, double monthSalary)
        : Employe(name, empId), monthelySalary(monthSalary) {}

    double calculateSalary() const override
    {
        return monthelySalary;
    }

    void showDetails() const override
    {
        Employe::showDetails();
        cout << "monthelySalary: " << monthelySalary << endl;
    }
};

class PartTimeEmploye : public Employe
{
    int hourseWorked;
    double hourelyRate;

public:
    PartTimeEmploye(const string &name, int id, int hourse, double hourRate)
        : Employe(name, id), hourseWorked(hourse), hourelyRate(hourRate) {}

    double calculateSalary() const override
    {
        return hourseWorked * hourelyRate;
    }

    void showDetails() const override
    {
        Employe::showDetails();
        cout << "hourseWorked: " << hourseWorked << endl;
        cout << "hourelyRate: " << hourelyRate << endl;
    }
};

int main()
{
    Employe *e1 = new FullTimeEmploye("Akshay", 1, 50000);
    Employe *e2 = new PartTimeEmploye("Abhi", 2, 2, 9000);

    cout << "--- Employee 1 Details ---" << endl;
    e1->showDetails();
    cout << "Salary: " << e1->calculateSalary() << endl;

    cout << "\n--- Employee 2 Details ---" << endl;
    e2->showDetails();
    cout << "Salary: " << e2->calculateSalary() << endl;

    delete e1;
    delete e2;
}
