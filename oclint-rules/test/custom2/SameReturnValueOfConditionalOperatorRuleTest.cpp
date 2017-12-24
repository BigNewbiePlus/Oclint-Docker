#include "TestRuleOnCode.h"
#include "rules/custom2/SameReturnValueOfConditionalOperatorRule.cpp"

TEST(SameReturnValueOfConditionalOperatorRuleTest, PropertyTest)
{
    SameReturnValueOfConditionalOperatorRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("same return value of conditional operator", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(SameReturnValueOfConditionalOperatorRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new SameReturnValueOfConditionalOperatorRule(),
            "void m(){int a;a=a>0?a:-a;}");
    testRuleOnCXXCode(new SameReturnValueOfConditionalOperatorRule(), 
            "void m(){int a;a=a>0&&a!=10?a:a-10;}");
}

TEST(SameReturnValueOfConditionalOperatorRuleTest, Test1)
{
         
    testRuleOnCXXCode(new SameReturnValueOfConditionalOperatorRule(), 
            "void m(){int a;\n"
            "a=a>0?a:a;}",0, 2, 3, 2, 9, "the conditional operation 'a>0?a:a' always returns the same value 'a'.");
}

TEST(SameReturnValueOfConditionalOperatorRuleTest, Test2)
{
         
    testRuleOnCXXCode(new SameReturnValueOfConditionalOperatorRule(), 
            "void m(){int a;\n"
            "a=a>0?a-10:a-10;}",0, 2, 3, 2, 14, "the conditional operation 'a>0?a-10:a-10' always returns the same value 'a-10'.");
}
