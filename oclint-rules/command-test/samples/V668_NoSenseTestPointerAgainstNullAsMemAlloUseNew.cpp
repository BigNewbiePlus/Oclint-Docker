#include<iostream>
using namespace std;
class person{
    int age;
};
int main()
{
    int* ptr = new int[10];
    ptr=new int[10];
    if(ptr){ }
    if(ptr!=NULL){}

    person* lily = new person();
    lily = new person[10];
    if(lily==NULL){}
    return 0;
}
