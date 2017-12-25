#include<string>
using namespace std;

int main()
{
    static char* tokens[]={"KW_IF", "KW_INCLUDE" "KW_JUMP", "KW_BREAK"};
    char* tokens2[4]={"KW_IF", "KW_INCLUDE" "KW_JUMP", "KW_BREAK"};
    char*tokens4[4]={"KW_IF", "KW_INCLUDE\"\"KW_JUMP", "KW_BREAK"};
    return 0;
}
