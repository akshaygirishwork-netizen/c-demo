#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    unordered_map<int, string> um;

    um[1] = "Akshay";
    um[5] = "Rahul";
    um[2] = "Neha";
    um[10] = "Kiran";
    um[20] = "Vijay";
    um[25] = "Arun";
    um[3] = "Manoj";

    for (auto &p : um)
        cout << p.first << " -> " << p.second << endl;
}
