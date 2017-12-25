#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class AddSemiAfterIfForWhileConditionRule : public AbstractASTVisitorRule<AddSemiAfterIfForWhileConditionRule>
{
public:
    virtual const string name() const override
    {
        return "add semi after if for while condition";
    }

    virtual int priority() const override
    {
        return 3;
    }

    virtual const string category() const override
    {
        return "custom";
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
        sm = &_carrier->getSourceManager();
    }
    virtual void tearDown() override {}
    
    /* Visit CompoundStmt */
    bool VisitCompoundStmt(CompoundStmt* cs)
    {
        if(cs->size()>=2){
            for(CompoundStmt::body_iterator it=cs->body_begin(); it!=cs->body_end(); it++){
                if((isa<IfStmt>(*it) || isa<WhileStmt>(*it) || isa<ForStmt>(*it)) && it+1!=cs->body_end()){
                    Stmt* body = NULL;
                    string stmtType="";
                    if(isa<IfStmt>(*it)){
                        IfStmt* is = dyn_cast_or_null<IfStmt>(*it);
                        body = is->getThen();
                        stmtType="if";
                    }else if(isa<WhileStmt>(*it)){
                        WhileStmt* ws = dyn_cast_or_null<WhileStmt>(*it);
                        body = ws->getBody();
                        stmtType="while";
                    }else if(isa<ForStmt>(*it)){
                        ForStmt* fs = dyn_cast_or_null<ForStmt>(*it);
                        body = fs->getBody();
                        stmtType="for";
                    }
                    if(body && isa<NullStmt>(body)){
                        SourceLocation sl1 = (*it)->getLocStart();
                        SourceLocation sl2 = (*(it+1))->getLocStart();
                        
                        unsigned row1 = sm->getSpellingLineNumber(sl1);
                        unsigned col1 = sm->getSpellingColumnNumber(sl1);
                        
                        unsigned row2 = sm->getSpellingLineNumber(sl2);
                        unsigned col2 = sm->getSpellingColumnNumber(sl2);

                        if(isa<CompoundStmt>(*(it+1)) || (row1+1==row2 && col1<col2)){
                            
                            string message = "Odd semicolon ';' after '"+stmtType+"' operator.";
                            addViolation(*it,this,message);
                        }
                    }
                    
                }
            }
        }
        return true;
    }

private:
    SourceManager* sm;
     
};

static RuleSet rules(new AddSemiAfterIfForWhileConditionRule());
