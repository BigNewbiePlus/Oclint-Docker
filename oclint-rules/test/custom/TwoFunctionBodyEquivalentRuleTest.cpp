#include "TestRuleOnCode.h"
#include "rules/custom/TwoFunctionBodyEquivalentRule.cpp"

TEST(TwoFunctionBodyEquivalentRuleTest, PropertyTest)
{
    TwoFunctionBodyEquivalentRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("two function body equivalent", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(TwoFunctionBodyEquivalentRuleTest, NoViolationInstance)    
{
    
    testRuleOnCode(new TwoFunctionBodyEquivalentRule(), 
                   "\nvoid m(){\nfor(int i=0;i<10;i++){}\n}\n"
                   "\nvoid m1(){\nfor(int j=0;j<10;j++){}\n}\n\n\n"
                   "\nvoid m2(){\nfor(int k=0;k<10;k++){}\n}");
}

TEST(TwoFunctionBodyEquivalentRuleTest, Test1)
{
         
    testRuleOnCode(new TwoFunctionBodyEquivalentRule(),                                           
                   "void foo(){for(int i=0;i<10;i++){}}"
                   "\nvoid test(){for(int i=0;i<10;i++){}}",
            0, 2, 1, 2, 36, "It is odd that the body of 'foo' function is fully equivalent to the body of 'test' function.");
}
