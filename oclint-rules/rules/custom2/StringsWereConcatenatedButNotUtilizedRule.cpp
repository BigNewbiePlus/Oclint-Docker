#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class StringsWereConcatenatedButNotUtilizedRule : public AbstractASTVisitorRule<StringsWereConcatenatedButNotUtilizedRule>
{
public:
    virtual const string name() const override
    {
        return "strings were concatenated but not utilized";
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

    virtual void setUp() override {}
    virtual void tearDown() override {}

    bool isConcateOperator(ExprWithCleanups* ewc){
        Expr* expr = ewc->getSubExpr();
        if(isa<CXXBindTemporaryExpr>(expr)){
            CXXBindTemporaryExpr* cbte = dyn_cast_or_null<CXXBindTemporaryExpr>(expr);
            expr = cbte->getSubExpr();
        }
        if(isa<CXXOperatorCallExpr>(expr)){
            CXXOperatorCallExpr* cxxCallExpr = dyn_cast_or_null<CXXOperatorCallExpr>(expr);
            string operType = cxxCallExpr->getDirectCallee()->getNameInfo().getAsString();
            if(operType=="operator+")return true;
        }
        return false;
    }
    /* Visit CompoundStmt */
    bool VisitCompoundStmt(CompoundStmt *cs)
    {
        for(CompoundStmt::body_iterator it=cs->body_begin();it!=cs->body_end(); it++){
            if(isa<ExprWithCleanups>(*it)){
                ExprWithCleanups* ewc = dyn_cast_or_null<ExprWithCleanups>(*it);
                string type = ewc->getType().getAsString();
                string strType = "basic_string<char, struct std::char_traits<char>, class std::allocator<char> >";
                if(type==strType && isConcateOperator(ewc)){//string类型
                    string message = "The strings were concatenated but are not utilized. Consider inspecting the expression.";
                    addViolation(*it, this, message);
                    break;
                }
            }
        }
        return true;
    }

};

static RuleSet rules(new StringsWereConcatenatedButNotUtilizedRule());
