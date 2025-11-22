#include<iostream>
#include<optional>

using namespace std;

optional<int> checkEven(int num){
    if(num%2){
        return {}; 
    }
    else{
        return num;
    }
}

int main(){
    
    int num=7;

    //optional<int> result;
    auto result=checkEven(8);

    if(result){
        cout<<"Even no found:"<<*result<<endl;
    }
    else{
        cout<<"Even no not found"<<endl;
    }
}
