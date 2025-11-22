#include<iostream>
#include<memory>

using namespace std;

class A {
    int a;
    int b;
    public:
    A(){
        cout<<"constructor called"<<endl;
    }
    ~A(){
        cout<<"destructor called"<<endl;
    }

    void display(){
        cout<<"called display"<<endl;
    }


};

int main(){
    unique_ptr<A> ptr = make_unique<A>();
    ptr->display();
}