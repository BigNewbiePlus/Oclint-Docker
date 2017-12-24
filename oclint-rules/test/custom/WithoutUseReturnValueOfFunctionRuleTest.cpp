#include "TestRuleOnCode.h"
#include "rules/custom/WithoutUseReturnValueOfFunctionRule.cpp"

TEST(WithoutUseReturnValueOfFunctionRuleTest, PropertyTest)
{
    WithoutUseReturnValueOfFunctionRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("without use return value of function", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(WithoutUseReturnValueOfFunctionRuleTest, NoViolationInstance)    
{
    
    testRuleOnCXXCode(new WithoutUseReturnValueOfFunctionRule(), "void m(){} void foo(){m();}");
    testRuleOnCXXCode(new WithoutUseReturnValueOfFunctionRule(), 
            "#include<vector>\n"
            "using namespace std;"
            "void foo(){vector<int> a;a.push_back(10);}");
}
TEST(WithoutUseReturnValueOfFunctionRuleTest, Test1)
{
         
    testRuleOnCXXCode(new WithoutUseReturnValueOfFunctionRule(),
                   "#include<vector>\n"
                   "using namespace std;\n"
                      "void foo(){vector<int> a;\na.back();}",
            0, 4, 1, 4, 8, "The return value of function 'back' is required to be utilized.");
}


TEST(WithoutUseReturnValueOfFunctionRuleTest, Test2)
{
         
    testRuleOnCXXCode(new WithoutUseReturnValueOfFunctionRule(),
                   "#include<string>\n"
                   "using namespace std;\n"
                      "void foo(){string str;\nstr.empty();}",
            0, 4, 1, 4, 11, "The return value of function 'empty' is required to be utilized.");
}

