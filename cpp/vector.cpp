#include<iostream>
#include<vector>
#include<algorithm>

int main(){
    std::vector<int> vec = {7,5,1,3,};
    std::cout<<"size="<<vec.size()<<std::endl;
    sort(vec.begin(),vec.end());

    for(int num:vec){
        std::cout<<num<<std::endl;
    }
    reverse(vec.begin(),vec.end());
    
    std::cout<<"After reverse"<<std::endl;

    for(int num:vec){
        std::cout<<num<<std::endl;
    }

}
