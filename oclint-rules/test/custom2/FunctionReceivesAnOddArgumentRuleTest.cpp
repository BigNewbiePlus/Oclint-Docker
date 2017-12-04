#include "TestRuleOnCode.h"
#include "rules/custom2/FunctionReceivesAnOddArgumentRule.cpp"

TEST(FunctionReceivesAnOddArgumentRuleTest, PropertyTest)
{
    FunctionReceivesAnOddArgumentRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("function receives an odd argument", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(FunctionReceivesAnOddArgumentRuleTest, NoViolationInstance)
{
    testRuleOnCode(new FunctionReceivesAnOddArgumentRule(),
            "#include<string.h>\n"
            "typedef struct person{}Person;"
            "void m(){Person peter; memset(&peter, 0, sizeof(peter));}");
    testRuleOnCode(new FunctionReceivesAnOddArgumentRule(), 
            "#include<string.h>\n"
            "void m(){int a;memset(&a, 0, sizeof(a));}");
}

TEST(FunctionReceivesAnOddArgumentRuleTest, Test1)
{
         
    testRuleOnCode(new FunctionReceivesAnOddArgumentRule(), 
            "#include<string.h>\n"
            "typedef struct person{}Person;\n"
            "void m(){Person peter;\n"
            "memset(&peter, sizeof(peter),0);}",0, 4, 1, 4, 31, "The 'memset' function processes '0' elements. Inspect the third argument.");
}

TEST(FunctionReceivesAnOddArgumentRuleTest, Test2)
{
         
    testRuleOnCode(new FunctionReceivesAnOddArgumentRule(), 
            "#include<string.h>\n"
            "void m(){unsigned char a;\n"
            "memset(&a,sizeof(a),0);"
            "}", 0, 3, 1, 3, 22, "The 'memset' function processes '0' elements. Inspect the third argument.");
}


TEST(FunctionReceivesAnOddArgumentRuleTest, Test3)
{
         
    testRuleOnCXXCode(new FunctionReceivesAnOddArgumentRule(), 
            "#include<cstring>\n"
            "class Person{};\n"
            "void m(){Person peter;\n"
            "memset(&peter, sizeof(peter),0);}",0, 4, 1, 4, 31, "The 'memset' function processes '0' elements. Inspect the third argument.");
}
