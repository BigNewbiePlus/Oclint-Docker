#include "TestRuleOnCode.h"
#include "rules/custom/ConstantValueWithZeroPrefixRule.cpp"

TEST(ConstantValueWithZeroPrefixRuleTest, PropertyTest)
{
    ConstantValueWithZeroPrefixRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("constant value with zero prefix", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(ConstantValueWithZeroPrefixRuleTest, NoViolationInstance)    
{
    
    testRuleOnCode(new ConstantValueWithZeroPrefixRule(), "void m(){int a=0;}");
}

TEST(ConstantValueWithZeroPrefixRuleTest, Test1)
{         
    testRuleOnCode(new ConstantValueWithZeroPrefixRule(),                     
                      "void foo(){for(int i=\n0123;i<10;i++){}}",
            0, 2, 1, 2, 1, "Be advised that the utilized constant value is represented by an octal form.");
}
TEST(ConstantValueWithZeroPrefixRuleTest, Test2)
{         
    testRuleOnCode(new ConstantValueWithZeroPrefixRule(),                     
                      "void foo(){int a=\n0123;}",
            0, 2, 1, 2, 1, "Be advised that the utilized constant value is represented by an octal form.");
}
TEST(ConstantValueWithZeroPrefixRuleTest, Test3)
{         
    testRuleOnCode(new ConstantValueWithZeroPrefixRule(),                     
                      "void foo(){int a; int b=a*\n0706+a;}",
            0, 2, 1, 2, 1, "Be advised that the utilized constant value is represented by an octal form.");
}
