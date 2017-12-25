#include "TestRuleOnCode.h"
#include "rules/custom2/ElseBlockWasPossibleForgottenOrCommentOutRule.cpp"

TEST(ElseBlockWasPossibleForgottenOrCommentOutRuleTest, PropertyTest)
{
    ElseBlockWasPossibleForgottenOrCommentOutRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("else block was possible forgotten or comment out", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(ElseBlockWasPossibleForgottenOrCommentOutRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new ElseBlockWasPossibleForgottenOrCommentOutRule(),
            "void m(){int a;if(a>0){}else{}}");
    testRuleOnCXXCode(new ElseBlockWasPossibleForgottenOrCommentOutRule(),
            "void m(){int a;if(a>0)\na=10;\nelse\na=11;}");
    testRuleOnCXXCode(new ElseBlockWasPossibleForgottenOrCommentOutRule(),
            "void m(){int a;if(a>0)\na=10;\nelse\n\na=11;}");
}

TEST(ElseBlockWasPossibleForgottenOrCommentOutRuleTest, Test1)
{
         
    testRuleOnCXXCode(new ElseBlockWasPossibleForgottenOrCommentOutRule(), 
            "void m(){"
            "int a,b; \nif(a>0)\n{}else\n\nif(b>0){}}",0, 2, 1, 5, 9, "It is possible that 'else' block was forgotten or commented out, thus altering the program's operation logics.");
}
