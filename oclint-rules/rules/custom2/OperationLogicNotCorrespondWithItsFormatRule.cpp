#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
using namespace std;
using namespace clang;
using namespace oclint;

class OperationLogicNotCorrespondWithItsFormatRule : public AbstractASTVisitorRule<OperationLogicNotCorrespondWithItsFormatRule>
{
public:
    virtual const string name() const override
    {
        return "operation logic not correspond with its format";
    }

    virtual int priority() const override
    {
        return 3;
    }

    virtual const string category() const override
    {
        return "custom2";
    }

#ifdef DOCGEN
    virtual const std::string since() const override
    {
        return "0.12";
    }

    virtual const std::string description() const override
    {
        return ""; // TODO: fill in the description of the rule.
    }

    virtual const std::string example() const override
    {
        return R"rst(
.. code-block:: cpp

    void example()
    {
        // TODO: modify the example for this rule.
    }
        )rst";
    }

    /* fill in the file name only when it does not match the rule identifier
    virtual const std::string fileName() const override
    {
        return "";
    }
    */

    /* add each threshold's key, description, and its default value to the map.
    virtual const std::map<std::string, std::string> thresholds() const override
    {
        std::map<std::string, std::string> thresholdMapping;
        return thresholdMapping;
    }
    */

    /* add additional document for the rule, like references, notes, etc.
    virtual const std::string additionalDocument() const override
    {
        return "";
    }
    */

    /* uncomment this method when the rule is enabled to be suppressed.
    virtual bool enableSuppress() const override
    {
        return true;
    }
    */
#endif

    virtual void setUp() override {
        sm=&_carrier->getSourceManager();
    }
    virtual void tearDown() override {}

    bool isLoseCurly(IfStmt* is, Stmt* stmt1, Stmt* stmt2){
        
        SourceLocation s1SSL = is->getLocStart(); //if起始语句
        
        SourceLocation s2SSL = stmt1->getLocStart();//if后第一个语句起始位置
        SourceLocation s2ESL = stmt1->getLocEnd();//终止位置

        SourceLocation s3SSL = stmt2->getLocStart();//if后第二个语句起始位置
        SourceLocation s3ESL = stmt2->getLocEnd();//终止位置
        
        unsigned s1SRow = sm->getSpellingLineNumber(s1SSL); //if的行列
        unsigned s1SCol = sm->getSpellingColumnNumber(s1SSL);

        unsigned s2SRow = sm->getSpellingLineNumber(s2SSL); //第一个语句起始行
        unsigned s2SCol = sm->getSpellingColumnNumber(s2SSL);//起始列
        unsigned s2ERow = sm->getSpellingLineNumber(s2ESL); //第一个语句终止行
        unsigned s2ECol = sm->getSpellingColumnNumber(s2ESL);//终止列
        
        unsigned s3SRow = sm->getSpellingLineNumber(s3SSL); //第一个语句起始行
        unsigned s3SCol = sm->getSpellingColumnNumber(s3SSL);//起始列
        unsigned s3ERow = sm->getSpellingLineNumber(s3ESL); //第一个语句终止行
        unsigned s3ECol = sm->getSpellingColumnNumber(s3ESL);//终止列

        if(s2SRow==s2ERow && s3SRow==s3ERow){//第二条和第三条语句起始和终止都在同一行
            if(s2SRow==s3SRow)return true;
            if(s1SRow+1==s2SRow && s2SRow+1==s3SRow && s2SCol==s3SCol && s1SCol<s2SCol)return true;
        }
        return false;
    }
    /* Visit CompoundStmt */
    bool VisitCompoundStmt(CompoundStmt *cs)
    {
        if(cs->size()<2)return true;
        
        for(CompoundStmt::body_iterator it=cs->body_begin(); it!=cs->body_end();it++){
            if(isa<IfStmt>(*it)){
                IfStmt* is = dyn_cast_or_null<IfStmt>(*it);
                Stmt* then = is->getThen();
                if(then && !isa<CompoundStmt>(then) && !is->getElse() && (it+1!=cs->body_end())){//if语句没else分支且then无括号
                    Stmt* nextStmt = *(it+1);
                    if(is && then && nextStmt && isLoseCurly(is, then, nextStmt)){
                        string message= "The code's operational logic does not correspond with its formatting. The statement is indented to the right, but it is always executed. It is possible that curly brackets are missing.";
                        addViolation(is, this, message);
                    }
                }
            }
        }
        return true;
    }
private:
    SourceManager* sm;
};

static RuleSet rules(new OperationLogicNotCorrespondWithItsFormatRule());
