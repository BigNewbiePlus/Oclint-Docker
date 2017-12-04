#include "TestRuleOnCode.h"
#include "rules/custom2/StringOfTwoPartsUsedForArrayInitializationRule.cpp"


TEST(StringOfTwoPartsUsedForArrayInitializationRuleTest, PropertyTest)
{
    StringOfTwoPartsUsedForArrayInitializationRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("string of two parts used for array initialization", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(StringOfTwoPartsUsedForArrayInitializationRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new StringOfTwoPartsUsedForArrayInitializationRule(), 
            "void m(){char* a[]={\"12\",\"23\",\"34\"};}");
    testRuleOnCXXCode(new StringOfTwoPartsUsedForArrayInitializationRule(),
            "void m(){char* a[3]={\"123\",\"23\",\"34\"};}");
}

TEST(StringOfTwoPartsUsedForArrayInitializationRuleTest, test1)
{
         
    testRuleOnCXXCode(new StringOfTwoPartsUsedForArrayInitializationRule(), 
            "void m(){char* a[]=\n{\"12\",\"23\"\"34\"};"
            "}",0, 2, 1, 2, 15, "It is possible that ',' comma is missing at the end of the string.");
}

TEST(StringOfTwoPartsUsedForArrayInitializationRuleTest, test2)
{
    testRuleOnCXXCode(new StringOfTwoPartsUsedForArrayInitializationRule(), 
             "void m(){char* a[3]=\n{\"12\",\"23\"\"34\"};}",0, 2, 1, 2, 15, "It is possible that ',' comma is missing at the end of the string.");
}
