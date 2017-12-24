#define MONKEY 0x0012
int main()
{
    int b;
    if(b&MONKEY || (MONKEY|b)){}
    if(b|MONKEY){}
    return 0;
}
