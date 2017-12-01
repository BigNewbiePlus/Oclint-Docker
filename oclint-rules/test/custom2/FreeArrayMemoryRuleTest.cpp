#include "TestRuleOnCode.h"
#include "rules/custom2/FreeArrayMemoryRule.cpp"

TEST(FreeArrayMemoryRuleTest, PropertyTest)
{
    FreeArrayMemoryRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("free array memory", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(FreeArrayMemoryRuleTest, NoViolationInstance)
{
    testRuleOnCode(new FreeArrayMemoryRule(), 
            "void m(){int* a,b;free(a);}");
}

TEST(FreeArrayMemoryRuleTest, Test1)
{
         
    testRuleOnCode(new FreeArrayMemoryRule(), 
            "void m(){\n"
            "int a[10];\nfree(a);}",0, 3, 1, 3, 7, "An attempt to free memory containing the 'int A[10]' array by using the 'free(A)' function.");
}

