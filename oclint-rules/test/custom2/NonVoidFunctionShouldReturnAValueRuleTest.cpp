#include "TestRuleOnCode.h"
#include "rules/custom2/NonVoidFunctionShouldReturnAValueRule.cpp"

TEST(NonVoidFunctionShouldReturnAValueRuleTest, PropertyTest)
{
    NonVoidFunctionShouldReturnAValueRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("non void function should return a value", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(NonVoidFunctionShouldReturnAValueRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new NonVoidFunctionShouldReturnAValueRule(),
            "void m(){}");
    testRuleOnCXXCode(new NonVoidFunctionShouldReturnAValueRule(), 
            "char m(){char a; return a;}");
    testRuleOnCXXCode(new NonVoidFunctionShouldReturnAValueRule(), 
            "int m(){int a; if(a)return a; else if(a<2){return 3;}else return 5;}");
}

TEST(NonVoidFunctionShouldReturnAValueRuleTest, Test1)
{ 
    testRuleOnCXXCode(new NonVoidFunctionShouldReturnAValueRule(), 
            "int m(){int a,b,c;a=b;\nif(a==10&&a!=5){};\n}"
           ,0, 1, 1, 3, 1, "Non-void function should return a value.");
}


TEST(NonVoidFunctionShouldReturnAValueRuleTest, Test2)
{ 
    testRuleOnCXXCode(new NonVoidFunctionShouldReturnAValueRule(), 
            "int m(){int a;\nif(a>0){return 1;}else if(a<2)return 3;else{a=5;}}"
           ,0, 1, 1, 2, 50, "Non-void function should return a value.");
}
TEST(NonVoidFunctionShouldReturnAValueRuleTest, Test3)
{ 
    testRuleOnCXXCode(new NonVoidFunctionShouldReturnAValueRule(), 
            "int m();int m(){int a;\nif(a>0){return 1;}else if(a<2)return 3;else{a=5;}}"
           ,0, 1, 9, 2, 50, "Non-void function should return a value.");
}
