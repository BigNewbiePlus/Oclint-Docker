#include "TestRuleOnCode.h"
#include "rules/custom2/AbsolutePathToFileAndDirUsedRule.cpp"

TEST(AbsolutePathToFileAndDirUsedRuleTest, PropertyTest)
{
    AbsolutePathToFileAndDirUsedRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("absolute path to file and dir used", rule.name());
    EXPECT_EQ("custom2", rule.category());
}

TEST(AbsolutePathToFileAndDirUsedRuleTest, NoViolationInstance)
{
    testRuleOnCode(new AbsolutePathToFileAndDirUsedRule(), 
            "#include<stdio.h>\n"
            "void m(){int a,b;FILE* fp = fopen(\"./test.cpp\", \"w\");}");
}

TEST(AbsolutePathToFileAndDirUsedRuleTest, Test1)
{
         
    testRuleOnCode(new AbsolutePathToFileAndDirUsedRule(), 
            "#include<stdio.h>\n"
            "void m(){\n"
            "int a;FILE* fp=\nfopen(\"c://myfile/file.dat\", \"r+\");}",0, 4, 1, 4, 34, "Consider inspecting the 'fopen' function call. Defining an absolute path to the file or directory is considered a poor style.");
}

