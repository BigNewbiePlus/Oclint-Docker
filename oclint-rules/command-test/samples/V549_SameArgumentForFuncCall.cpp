#include<string>
#include<iostream>
#include<string.h>
using namespace std;

void strTest(string a, string b){}
void test(char* a, char* b){}

void trueTest(int a, int b){}

class Person{
    public:
        string name;
};
int main()
{   
    char* a;
    Person* lily;
    
    test(a,a);
    string str;
    strTest(str,str);
    strcmp(lily->name.c_str(), lily->name.c_str());
    
    trueTest(1, 1);
    trueTest('a', 'a');
    return 0;
}
