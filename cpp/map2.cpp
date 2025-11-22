#include <iostream>
#include <map>
using namespace std;

struct Person {
    string name;
    int age;

    // Define how to compare (for sorting)
    bool operator<(const Person &other) const {
        return name < other.name; // sorted by age
    }
};

int main() {
    map<Person, string> people;

    people[{ "Akshay", 25 }] = "Engineer";
    people[{ "Neha", 23 }] = "Doctor";
    people[{ "Rahul", 28 }] = "Teacher";

    for (auto &p : people)
        cout << p.first.name << " (" << p.first.age << ") -> " << p.second << endl;
}

