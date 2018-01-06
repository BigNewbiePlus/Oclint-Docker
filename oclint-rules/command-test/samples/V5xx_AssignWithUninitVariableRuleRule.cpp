void foo(int a)
{
    a=0;
}
void foo2(int& a)
{
    a=0;
}
int main(){
    int a;
    int b;
    foo(a);
    foo2(b);         
    int c = a;
    int d = b;         
    return 0;
}
