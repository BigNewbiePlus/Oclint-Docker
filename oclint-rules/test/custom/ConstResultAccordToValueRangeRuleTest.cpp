#include "TestRuleOnCode.h"
#include "rules/custom/ConstResultAccordToValueRangeRule.cpp"

TEST(ConstResultAccordToValueRangeRuleTest, PropertyTest)
{
    ConstResultAccordToValueRangeRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("const result accord to value range", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(ConstResultAccordToValueRangeRuleTest, NoViolationInstance)    
{    
    testRuleOnCXXCode(new ConstResultAccordToValueRangeRule(), "void m(){char* p;if(*p==012){}}");
    testRuleOnCXXCode(new ConstResultAccordToValueRangeRule(), "void m(){char p[1024];if(p[0]<96){}}");
    testRuleOnCXXCode(new ConstResultAccordToValueRangeRule(), "void m(){char* cursor_;if(static_cast<unsigned char>(*cursor_) != 0xef){}}");
}

TEST(ConstResultAccordToValueRangeRuleTest, Test1)
{
    testRuleOnCXXCode(new ConstResultAccordToValueRangeRule(),                     
                      "void foo(){char* s;if(\n*s>127) *s = '~';}",
            0, 2, 1, 2, 4, "Expression '*s>127' is always false. The value range of signed char type: [-128, 127].");
}

TEST(ConstResultAccordToValueRangeRuleTest, Test2)
{
    testRuleOnCXXCode(new ConstResultAccordToValueRangeRule(),                     
                      "void foo(){unsigned int  a;if(\na>=0) {}}",
            0, 2, 1, 2, 4, "Expression 'a>=0' is always true. Unsigned type value is always >= 0.");
}
TEST(ConstResultAccordToValueRangeRuleTest, Test3)
{
    testRuleOnCXXCode(new ConstResultAccordToValueRangeRule(),                     
                      "void foo(){unsigned char  a;if(\na>255) {}}",
            0, 2, 1, 2, 3, "Expression 'a>255' is always false. The value range of unsigned char type: [0, 255].");
}
