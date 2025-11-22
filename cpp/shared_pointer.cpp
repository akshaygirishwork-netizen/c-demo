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
    shared_ptr<A> p1 = make_shared<A>();

    {
        shared_ptr<A> p2=p1;
        cout<<"use count:"<<p1.use_count()<<endl;
        p2->display();
    }
    cout<<"use count:"<<p1.use_count()<<endl;
}