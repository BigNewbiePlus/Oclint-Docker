#include<cstddef>
#include<stdint.h>

typedef unsigned int uint_t;
int main()
{
    int nBytes = 10;
    char* pBytes = new char[ nBytes ];
    if ( nBytes > 3 &&
       pBytes[0] == 0xEF &&
       pBytes[1] == 0xBB &&
       pBytes[2] == 0xBF ){}
    
    size_t nNumChars;
    if (nNumChars > 0){}
    
    char* s;
    if (*s > 127) *s = '~';

    char* cursor_;
    if (static_cast<unsigned char>(*cursor_) != 0xef){}
    
    uint_t a;
    if(a>0xffffffffu){}

    uint32_t immValue;
    if(immValue <= 0xFFFFFFFFU){}
    if(immValue >= 0xFFFFFFFFU){}
    if(immValue>-10){}
    return 0;
}
