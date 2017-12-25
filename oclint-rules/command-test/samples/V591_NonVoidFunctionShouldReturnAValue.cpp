int foo(){}
int foo2(){
    int a, b;
    if(a)return a;
    if(a>0){
        return a;
    }else if(a<12){
        return b;
    }else
    {
        return c;
    }
}
int main()
{ 
    int a;
    a=foo();
    return 0;
}
