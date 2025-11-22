#include <iostream>

using namespace std;

template<class T>
class A{
    T num1;
    T num2;

    public:
    A(T n1,T n2):num1(n1),num2(n2){}

    T add(){
        return num1+num2;
    }
    T sub(){
        return num1-num2;
    }
    T mul (){
        return num1*num2;
    }

};


int main()
{
    A<int> a1(10,20);
    A<float> a2(10.1,20.3);
    A<int> a3(2,3);
    cout<<a1.add()<<endl;
    cout<<a2.add()<<endl;
    cout<<a3.mul()<<endl;


}
