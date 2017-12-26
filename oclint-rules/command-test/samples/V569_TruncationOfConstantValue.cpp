typedef unsigned char uint8_t;

struct A{
    uint8_t nf; 
};
int main()
{   
    struct A my;
    my.nf = -96;
    unsigned char a;
    a=256;
    unsigned char b=-123;
    uint8_t c = 1230;
    return 0;
}
