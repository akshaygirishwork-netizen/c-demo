#include<iostream>

template<class type>
type area (type a){
    return (3.14*a*a);
}

template<class type>
type area(type a,type b){
    return a*b;
}

int main(){
    std::cout<<area(6)<<std::endl;
    std::cout<<area(6.5)<<std::endl;
    std::cout<<area(4,5)<<std::endl;
}