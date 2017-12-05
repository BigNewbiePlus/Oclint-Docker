#include "TestRuleOnCode.h"
#include "rules/custom/DereferencingNullPointerRule.cpp"

TEST(DereferencingNullPointerRuleTest, PropertyTest)
{
    DereferencingNullPointerRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("dereferencing null pointer", rule.name());
    EXPECT_EQ("custom", rule.category());
}


TEST(DereferencingNullPointerRuleTest, NoViolationInstance)    
{
    
    testRuleOnCode(new DereferencingNullPointerRule(),
                   "typedef struct person{int m_a;}Person;"
                   "void m(){"
                   "Person* lily;if(lily != 0 && lily->m_a) {}"
                   "}");
    testRuleOnCXXCode(new DereferencingNullPointerRule(),
                   "#include<stdio.h>\n"
                   "#include<stdlib.h>\n"
                   "class Pointer{\n"
                   "public:"
                   "bool m_a;\n"
                   "bool x(){return true;}\n"
                   "};\n"
                   "void m(){\n"
                   "Pointer* pointer;\n"
                   "if (pointer == 0 || pointer->m_a) {}"
                   "}");
    testRuleOnCXXCode(new DereferencingNullPointerRule(),
                   "#include<stdio.h>\n"
                   "#include<stdlib.h>\n"
                   
                   "class Pointer{\n"
                   "public:"
                   "bool m_a;\n"
                   "bool x(){return true;}\n"
                   "};\n"
                   "void m(){\n"
                   "Pointer* pointer;\n"
                   "if (!pointer || pointer->m_a) {}"
                   "}");
    testRuleOnCXXCode(new DereferencingNullPointerRule(),
                   "#include<stdio.h>\n"
                   "#include<stdlib.h>\n"
                   
                   "class Pointer{\n"
                   "public:"
                   "bool m_a;\n"
                   "bool x(){return true;}\n"
                   "};\n"
                   "void m(){\n"
                   "int array[10];\n"
                   "if (array != 0 && array[3]) {}"
                   "}");
    testRuleOnCXXCode(new DereferencingNullPointerRule(),
                   "#include<stdio.h>\n"
                   "#include<stdlib.h>\n"
                   
                   "class Pointer{\n"
                   "public:"
                   "bool m_a;\n"
                   "bool x(){return true;}\n"
                   "};\n"
                   "void m(){\n"
                   "int* a;\n"
                   "if (a != 0 && *a) {}"
                   "}");
}

TEST(DereferencingNullPointerRuleTest, Test1)
{
         
    testRuleOnCXXCode(new DereferencingNullPointerRule(),                     
                      "#include<stdio.h>\n"
                   "#include<stdlib.h>\n"
                   
                   "class Pointer{\n"
                   "public:"
                   "bool m_a;\n"
                   "bool x(){return true;}\n"
                   "};\n"
                   "void m(){\n"
                   "struct Pointer* pointer;\n"
                   "if(pointer != 0 || pointer->m_a) {}"
                   "}",
            0, 9, 4, 9, 29, "Dereferencing of the null pointer 'pointer' might take place. Check the logical condition.");
}

TEST(DereferencingNullPointerRuleTest, Test2)
{
         
    testRuleOnCXXCode(new DereferencingNullPointerRule(),                     
                   "#include<stdio.h>\n"
                   "#include<stdlib.h>\n"
                   
                   "class Pointer{\n"
                   "public:"
                   "bool m_a;\n"
                   "bool x(){return true;}\n"
                   "};\n"
                   "void m(){\n"
                   "struct Pointer* pointer;\n"
                   "if(pointer == 0 && pointer->m_a) {}"
                   "}",
            0, 9, 4, 9, 29, "Dereferencing of the null pointer 'pointer' might take place. Check the logical condition.");
}

TEST(DereferencingNullPointerRuleTest, Test3)
{
         
    testRuleOnCXXCode(new DereferencingNullPointerRule(),                     
                   "#include<stdio.h>\n"
                   "#include<stdlib.h>\n"
                   
                   "class Pointer{\n"
                   "public:"
                   "bool m_a;\n"
                   "bool x(){return true;}\n"
                   "};\n"
                   "void m(){\n"
                   "struct Pointer* pointer;\n"
                   "if(!pointer && pointer->m_a) {}"
                   "}",
            0, 9, 4, 9, 25, "Dereferencing of the null pointer 'pointer' might take place. Check the logical condition.");
}

TEST(DereferencingNullPointerRuleTest, Test4)
{
         
    testRuleOnCXXCode(new DereferencingNullPointerRule(),                     
                   "#include<stdio.h>\n"
                   "#include<stdlib.h>\n"
                   
                   "class Pointer{\n"
                   "public:"
                   "bool m_a;\n"
                   "bool x(){return true;}\n"
                   "};\n"
                   "void m(){\n"
                   "int array[10];\n"
                   "if(array == 0 && array[3]) {}"
                   "}",
            0, 9, 4, 9, 25, "Dereferencing of the null pointer 'array' might take place. Check the logical condition.");
}

TEST(DereferencingNullPointerRuleTest, Test5)
{
         
    testRuleOnCXXCode(new DereferencingNullPointerRule(),                     
                   "#include<stdio.h>\n"
                   "#include<stdlib.h>\n"
                  
                   "class Pointer{\n"
                   "public:"
                   "bool m_a;\n"
                   "bool x(){return true;}\n"
                   "};\n"
                   "void m(){\n"
                   "int* a;\n"
                   "if(a == 0 && *a) {}"
                   "}",
            0, 9, 4, 9, 15, "Dereferencing of the null pointer 'a' might take place. Check the logical condition.");
}


