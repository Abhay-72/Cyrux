#include <iostream>
using namespace std;

int main(){
    int n,a=0,b;
    cout<<"Enter a no.: ";
    cin>>n;
    
    while(n>0){
        b = n%10;
        a += b;
        n = n/10;
    }
    cout<<"Result of no.: "<<b<<endl;
    return 0;
}