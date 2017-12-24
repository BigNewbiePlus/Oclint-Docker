#include "TestRuleOnCode.h"
#include "rules/custom/LowerPriorityOfConditionalExpressionRule.cpp"

TEST(LowerPriorityOfConditionalExpressionRuleTest, PropertyTest)
{
    LowerPriorityOfConditionalExpressionRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("lower priority of conditional expression", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(LowerPriorityOfConditionalExpressionRuleTest, NoViolationInstance)    
{
    
    testRuleOnCXXCode(new LowerPriorityOfConditionalExpressionRule(), "void m(){int a,b,c;a=a?a:b;}");
    testRuleOnCXXCode(new LowerPriorityOfConditionalExpressionRule(), "void m(){int a=0,b,c;a=(a-b)?a:b;}");
    testRuleOnCXXCode(new LowerPriorityOfConditionalExpressionRule(), "void m(){int a=0,b,c;a=a>b?a:b;}");
    testRuleOnCXXCode(new LowerPriorityOfConditionalExpressionRule(), "void m(){int a=0,b,c;a=a+b?a:b;}");
}

TEST(LowerPriorityOfConditionalExpressionRuleTest, Test1)
{
         
    testRuleOnCXXCode(new LowerPriorityOfConditionalExpressionRule(), "void m(){int a, b; bool flag;a=\na+flag?a:b;}",
            0, 2, 1, 2, 10, 
                      "Check priority in conditional expression 'a+flag?a:b', the operator '+' has more priority than '?:'!");
}

TEST(LowerPriorityOfConditionalExpressionRuleTest, Test2) 
{

    testRuleOnCXXCode(new LowerPriorityOfConditionalExpressionRule(), 
            "void m(){int a,b,c;a=\na|(b==c)?a:b;}",
            0, 2, 1, 2, 12, 
            "Check priority in conditional expression 'a|(b==c)?a:b', the operator '|' has more priority than '?:'!"
            );
    
}

TEST(LowerPriorityOfConditionalExpressionRuleTest, Test3) 
{

    testRuleOnCXXCode(new LowerPriorityOfConditionalExpressionRule(), 
            "void m(){int a,b; bool flag; a=\na*(b>0)?a:b;}",
            0, 2, 1, 2, 11,
            "Check priority in conditional expression 'a*(b>0)?a:b', the operator '*' has more priority than '?:'!"); 
}
TEST(LowerPriorityOfConditionalExpressionRuleTest, Test4) 
{

    testRuleOnCXXCode(new LowerPriorityOfConditionalExpressionRule(), 
            "void m(){int a,b; bool flag; a=\na+(b>a)?a:b;}",
            0, 2, 1, 2, 11,
            "Check priority in conditional expression 'a+(b>a)?a:b', the operator '+' has more priority than '?:'!"); 
}

