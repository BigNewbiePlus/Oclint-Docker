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
    testRuleOnCXXCode(new ConstResultAccordToValueRangeRule(), "typedef unsigned int uint_t;\nvoid m(){uint_t a; if(a>0xFFFFFFFFU){}}");
    testRuleOnCXXCode(new ConstResultAccordToValueRangeRule(), "#include<stdint.h>\nvoid m(){uint32_t a; if(a<=0xFFFFFFFFU){}{}}");
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
TEST(ConstResultAccordToValueRangeRuleTest, Test4)
{
    testRuleOnCXXCode(new ConstResultAccordToValueRangeRule(),                     
                      "typedef unsigned char uchar_t;void foo(){uchar_t a;if(\na>255) {}}",
            0, 2, 1, 2, 3, "Expression 'a>255' is always false. The value range of unsigned char type: [0, 255].");
}
TEST(ConstResultAccordToValueRangeRuleTest, Test5)
{
    testRuleOnCXXCode(new ConstResultAccordToValueRangeRule(),                     
            "#include<stdint.h>\n"          
            "void foo(){uint32_t a;if(\na>-10) {}}",
            0, 3, 1, 3, 4, "Expression 'a>-10' is always true. Unsigned type value is always >= 0.");
}
TEST(ConstResultAccordToValueRangeRuleTest, Test6)
{
    testRuleOnCXXCode(new ConstResultAccordToValueRangeRule(),                     
            "#include<stdint.h>\n"          
            "void foo(){uint32_t a;if(\na>0xffffffffU) {}}",
            0, 3, 1, 3, 4, "Expression 'a>-10' is always true. Unsigned type value is always >= 0.");
}
