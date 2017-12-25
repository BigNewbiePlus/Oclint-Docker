#include<cstddef>
int main()
{
    int nBytes = 10;
    char* pBytes = new char[ nBytes ];
    if ( nBytes > 3 &&
       pBytes[0] == 0xEF &&
       pBytes[1] == 0xBB &&
       pBytes[2] == 0xBF )
    {
    }
    
    size_t nNumChars;
    if (nNumChars > 0){
    }
    char* s;
    if (*s > 127) *s = '~';

    char* cursor_;
    if (static_cast<unsigned char>(*cursor_) != 0xef){
    }
    return 0;
}
