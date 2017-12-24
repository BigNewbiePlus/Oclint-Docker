bool isTrue()
{
    return true;
}
int main()
{
    int a, b, c, d;
    a=a-(b>0)?c:d;
    a=a*(b<c)?c:d;
    
    a=a|(a>b)?a:b;
    bool flag;
    a = a + flag?a:b;
    a = a + isTrue()?a:b;
    a=flag?a:b;

    return 0;
}
