#include<string>
#include<iostream>
#include<string.h>
using namespace std;

void strTest(string a, string b){}
void test(char* a, char* b)
{}

class Person{
    public:
        string name;
};
int main()
{   
    char* a;
    test(a,a);
    string str;
    strTest(str,str);
    Person* lily;

    strcmp(lily->name.c_str(), lily->name.c_str());
    return 0;
}
