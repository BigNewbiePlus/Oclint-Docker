#include "TestRuleOnCode.h"
#include "rules/custom2/StringsWereConcatenatedButNotUtilizedRule.cpp"

TEST(StringsWereConcatenatedButNotUtilizedRuleTest, PropertyTest)
{
    StringsWereConcatenatedButNotUtilizedRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("strings were concatenated but not utilized", rule.name());
    EXPECT_EQ("custom2", rule.category());
}


TEST(StringsWereConcatenatedButNotUtilizedRuleTest, NoViolationInstance)
{
    testRuleOnCXXCode(new StringsWereConcatenatedButNotUtilizedRule(), 
            "#include<string>\n"
            "using namespace std;"
            "void m(){string a;while(a.size()){a+=\"skdljsld\";}}");
    testRuleOnCXXCode(new StringsWereConcatenatedButNotUtilizedRule(),
            "#include<string>\n"
            "using namespace std;"
            "void m(){string a,b;a=a+\"*****\";a+=b;}");
}

TEST(StringsWereConcatenatedButNotUtilizedRuleTest, test1)
{
         
    testRuleOnCXXCode(new StringsWereConcatenatedButNotUtilizedRule(), 
            "#include<string>\n"
            "using namespace std;"
            "void m(){string a;\na+\"bigcat\";"
            "}",0, 3, 1, 3, 3, "The strings were concatenated but are not utilized. Consider inspecting the expression.");
}

TEST(StringsWereConcatenatedButNotUtilizedRuleTest, test2)
{
         
    testRuleOnCXXCode(new StringsWereConcatenatedButNotUtilizedRule(), 
            "#include<string>\n"
            "using namespace std;"
            "void m(){string a,b;\nwhile(a.size()){\na+\"12\"+b+\"2323\";}"
            "}",0, 4, 1, 4, 10, "The strings were concatenated but are not utilized. Consider inspecting the expression.");
}
TEST(StringsWereConcatenatedButNotUtilizedRuleTest, test3)
{
         
    testRuleOnCXXCode(new StringsWereConcatenatedButNotUtilizedRule(), 
            "#include<string>\n"
            "using namespace std;"
            "void m(){string a,b;\nif(a.size()){\na+b;}"
            "}",0, 4, 1, 4, 3, "The strings were concatenated but are not utilized. Consider inspecting the expression.");
}
