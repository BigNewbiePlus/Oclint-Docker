#include "TestRuleOnCode.h"
#include "rules/custom2/PointerPlusConstantConditionIsFalseRule.cpp"

TEST(PointerPlusConstantConditionIsFalseRuleTest, PropertyTest)
{
    PointerPlusConstantConditionIsFalseRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("pointer plus constant condition is false", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(PointerPlusConstantConditionIsFalseRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new PointerPlusConstantConditionIsFalseRule(),
            "#include<cstdio>\n"
            "void m(){int* ptr,*ptr2;if(ptr){}if(ptr!=NULL){}if(ptr==NULL){}if(ptr!=ptr2){}}");
}

TEST(PointerPlusConstantConditionIsFalseRuleTest, Test1)
{
         
    testRuleOnCXXCode(new PointerPlusConstantConditionIsFalseRule(), 
            "void m(){\n"
            "int* ptr; if(\nptr+1){}}",0, 3, 1, 3, 5, "The condition ptr+1 is only false if there is pointer overflow which is undefined behaviour anyway.");
}

TEST(PointerPlusConstantConditionIsFalseRuleTest, Test2)
{
    testRuleOnCXXCode(new PointerPlusConstantConditionIsFalseRule(), 
            "#include<cstdio>\n"
            "void m(){"
            "int* ptr; if(\nptr+1!=NULL){}}",0, 3, 1, 3, 8, "The condition ptr+1!=NULL is only false if there is pointer overflow which is undefined behaviour anyway.");
}

TEST(PointerPlusConstantConditionIsFalseRuleTest, Test3)
{
    testRuleOnCXXCode(new PointerPlusConstantConditionIsFalseRule(), 
            "#include<cstdio>\n"
            "void m(){"
            "int* ptr; if(\nptr+1==0){}}",0, 3, 1, 3, 8, "The condition ptr+1==0 is only false if there is pointer overflow which is undefined behaviour anyway.");
}
