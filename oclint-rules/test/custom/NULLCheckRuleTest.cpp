#include "TestRuleOnCode.h"
#include "rules/custom/NULLCheckRule.cpp"

TEST(NULLCheckRuleTest, PropertyTest)
{
    NULLCheckRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("n u l l check", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(NULLCheckRuleTest, NoViolationInstance)
 {
     testRuleOnCXXCode(new NULLCheckRule(),
             "#include<cstddef>\n"
             "void m(){int *a;if(a==NULL){}}");
 }

