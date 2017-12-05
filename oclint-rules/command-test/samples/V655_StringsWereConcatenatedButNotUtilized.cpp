#include<string>
int main()
{
    std::string a;
    if(a.size()){
        a+"(";
    }
    a+"(";
    a+"("+a+")";
    return 0;
}
