class person{
public:
    int age;
};
int main()
{
    int a,b;
    a=1;
    a=2;    

    person lily;
    lily.age=1;
    lily.age=1;
    
    int* ptr, *ptr2;
    *ptr=a;
    ptr = ptr2;
    ptr = &a;

    int array[10];
    array[0]=1;
    array[0]=2;
    return 0;
}
