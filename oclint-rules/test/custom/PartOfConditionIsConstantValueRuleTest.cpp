#include "TestRuleOnCode.h"
#include "rules/custom/PartOfConditionIsConstantValueRule.cpp"

TEST(PartOfConditionIsConstantValueRuleTest, PropertyTest)
{
    PartOfConditionIsConstantValueRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("part of condition is constant value", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(PartOfConditionIsConstantValueRuleTest, NoViolationInstance)    
{
    
    testRuleOnCXXCode(new PartOfConditionIsConstantValueRule(), "void m(){int a;bool b; int c[10];if(!(a)&&b||(c[0])){}}");
}

TEST(PartOfConditionIsConstantValueRuleTest, Test1)
{
         
    testRuleOnCXXCode(new PartOfConditionIsConstantValueRule(),                     
                      "void m(){int a;if(\na&&0x04){}}",
            0, 2, 1, 2, 4, "A part of conditional expression is constant in 'a&&0x04'.");
}

TEST(PartOfConditionIsConstantValueRuleTest, Test2)
{
         
    testRuleOnCXXCode(new PartOfConditionIsConstantValueRule(),                     
                      "void m(){enum fruit{apple, banana, orange}myfruit;if(\napple||banana){}}",
            0, 2, 1, 2, 8, "A part of conditional expression is constant in 'apple||banana'.");
}
TEST(PartOfConditionIsConstantValueRuleTest, Test3)
{
         
    testRuleOnCXXCode(new PartOfConditionIsConstantValueRule(),                     
            "#define ORE_OPEN 0x00012\n"          
            "void m(){int a;if(\na&&ORE_OPEN){}}",
            0, 3, 1, 3, 4, "A part of conditional expression is constant in 'a&&ORE_OPEN'.");
}

TEST(PartOfConditionIsConstantValueRuleTest, Test4)
{
    testRuleOnCXXCode(new PartOfConditionIsConstantValueRule(),                     
            "void m(){int a;a=\n0x112&&a==1;}",
            0, 2, 1, 2, 11, "A part of conditional expression is constant in '0x112&&a==1'.");
}

TEST(PartOfConditionIsConstantValueRuleTest, Test5)
{
    testRuleOnCXXCode(new PartOfConditionIsConstantValueRule(),                     
            "int m(){int a;return \na==0x12 || 0x123 || 0x124;}",
            0, 2, 1, 2, 21, "A part of conditional expression is constant in 'a==0x12 || 0x123 || 0x124'.");
}
