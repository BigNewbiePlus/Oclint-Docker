#include "TestRuleOnCode.h"
#include "rules/custom/IdenticalSubExprsRule.cpp"

TEST(IdenticalSubExprsRuleTest, PropertyTest)
{
    IdenticalSubExprsRule rule;
    EXPECT_EQ(3, rule.priority());
    EXPECT_EQ("identical sub exprs", rule.name());
    EXPECT_EQ("custom", rule.category());
}

TEST(IdenticalSubExprsRuleTest, NoViolationInstance)    
{
    
    testRuleOnCXXCode(new IdenticalSubExprsRule(), "void m(){int a,b,c;if(a&&b||c){}}");
    testRuleOnCXXCode(new IdenticalSubExprsRule(), "void m(){int a=0,b,c; if(a||b||c){}}");
              
}

TEST(IdenticalSubExprsRuleTest, Test1)
{
         
    testRuleOnCXXCode(new IdenticalSubExprsRule(), "void m(){int a;if(a||a){}}",
            0, 1, 19, 1, 22, "'a' repeated in expression 'a||a' !");
}


TEST(IdenticalSubExprsRuleTest, Test2) 
{

    testRuleOnCXXCode(new IdenticalSubExprsRule(), 
            "#define MIN(a,b) a>b?b:a\n"
            "#define MACRO1 1024\n"
            "void foo(){int a,b; if(a==MACRO1||a==MACRO1){}}",
            0, 3, 24, 3, 38, "'a==MACRO1' repeated in expression 'a==MACRO1||a==MACRO1' !");  
}

TEST(IdenticalSubExprsRuleTest, Test3) 
{

    testRuleOnCXXCode(new IdenticalSubExprsRule(), 
            "#define MIN(a,b) a>b?b:a\n"
            "#define MACRO1 1024\n"
            "void foo(){int a,b;b=MIN(a,a);}",
            0, 3, 26, 3, 28, "'a' repeated in expression 'a>a' !");  
}
