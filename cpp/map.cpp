#include<iostream>
#include<map>

int main()
{
    std::map<int, std::string> m;
    m[1] = "Akshay";
    m[2] = "abhinav";
    m[3] = "arun";
    m[4] = "Ameen";
    m[5] = "Abhi";

    std::cout << m.size()<<std::endl;

    m.erase(2);

    for (auto i : m)
    {
        std::cout << i.first << i.second << std::endl;
    }

    // for (auto i : m)
    // {
    //     std::cout << i.first << i.second << std::endl;
    // }
}