#include<iostream>
#include<string.h>
using namespace std;

class Account{
    string Name;
    int Age;
    double Balance;

    public:
    Account(const string& name,int age,double initialBalance=0):Name(name),Age(age),Balance(initialBalance){}

    void showDetails () const{
        cout<<"Name:"<<Name<<endl;
        cout<<"Age:"<<Age<<endl;
    }

    void deposit(int deposit){
        Balance+=deposit;
        cout<<"Deposited:"<<deposit<<endl;
    }

    void Debit(int debit){

        if(debit>Balance){
            cout<<"insufficient money"<<endl;
        }
        else{
            cout<<"Debited:"<<debit<<endl;
            Balance-=debit;
        }
    }

    void checkBalance() const {
        cout<<"Balance:"<<Balance<<endl;
    }
};

int main(){
    Account p1("Akshay",26);
    p1.showDetails();
    p1.checkBalance();
    p1.deposit(100);
    p1.checkBalance();
    p1.Debit(50);
    p1.checkBalance();

}