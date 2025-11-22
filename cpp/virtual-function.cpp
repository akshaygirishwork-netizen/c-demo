#include<iostream>

class Base{
    protected:
    int x;
    int y;
    public:

    Base(){
        std::cout<<"Default constructor Base"<<std::endl;
        x=10;
        y=20;
    }
   virtual void show(){
        std::cout<<"x="<<x<<std::endl;
        std::cout<<"y="<<y<<std::endl;
    }
};

class Derived :public Base{
    int z;
    public:
    Derived(){
        std::cout<<"Default constructor Derived"<<std::endl;
        z=30;
    }
    void show(){
        std::cout<<"z="<<z<<std::endl;
        std::cout<<"x="<<x<<std::endl;
        std::cout<<"y="<<y<<std::endl;

    }
};


int main(){
    Base *ptr;
    Derived d1;
    ptr=&d1;
    
    ptr->show();
}