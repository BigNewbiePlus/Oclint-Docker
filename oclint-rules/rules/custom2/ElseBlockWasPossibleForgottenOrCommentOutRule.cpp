#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class ElseBlockWasPossibleForgottenOrCommentOutRule : public AbstractASTVisitorRule<ElseBlockWasPossibleForgottenOrCommentOutRule>
{
public:
    virtual const string name() const override
    {
        return "else block was possible forgotten or comment out";
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
        sm = &_carrier->getSourceManager();
    }
    virtual void tearDown() override {}

    /* Visit IfStmt */
    bool VisitIfStmt(IfStmt *is)
    {
        Stmt* then = is->getThen();
        Stmt* els = is->getElse();

        if(then && els && isa<IfStmt>(els)){
            SourceLocation thenEnd   = then->getLocEnd();
            SourceLocation elsStart  = els->getLocStart();
            unsigned row1 = sm->getPresumedLineNumber(thenEnd);
            unsigned row2 = sm->getPresumedLineNumber(elsStart);
            if(row2-row1>=2){
                string message = "It is possible that 'else' block was forgotten or commented out, thus altering the program's operation logics.";
                addViolation(is, this, message);
            }
        }
        return true;
    }

private:
    SourceManager* sm;
};

static RuleSet rules(new ElseBlockWasPossibleForgottenOrCommentOutRule());
