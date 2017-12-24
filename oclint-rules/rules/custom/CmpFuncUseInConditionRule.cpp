#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include <set>
using namespace std;
using namespace clang;
using namespace oclint;

class CmpFuncUseInConditionRule : public AbstractASTVisitorRule<CmpFuncUseInConditionRule>
{
public:
    virtual const string name() const override
    {
        return "cmp func use in condition";
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
        string names[] = {"strcmp", "memcmp"};
        cmpFun.insert(names, names+2);
    }
    virtual void tearDown() override {}
    /* Visit IfStmt */
    bool VisitIfStmt(IfStmt *ifStmt)
    {
        Expr* expr = ifStmt->getCond();
        CallExpr* callExpr = getCmpExpr(expr);
        if(callExpr){
            string name = callExpr->getDirectCallee()->getNameInfo().getAsString();
            string message = "The '"+name+"' function returns 0 if corresponding strings are equal. Consider examining the condition for mistakes.";
            addViolation(callExpr, this, message);
        }  
        return true;
    }
    
private:
    CallExpr* getCmpExpr(Expr* expr){
        while(expr){
            if(isa<BinaryOperator>(expr)){           
                BinaryOperator* bo = dyn_cast_or_null<BinaryOperator>(expr);
                BinaryOperatorKind bok = bo->getOpcode();
            
                if(bok==BO_LAnd||bok==BO_LOr){
                    CallExpr* callExpr = getCmpExpr(bo->getLHS());
                    if(!callExpr) callExpr = getCmpExpr(bo->getRHS());
                    return callExpr;
                }
                break;
        
            }else if(isa<ImplicitCastExpr>(expr)){
                ImplicitCastExpr* implicitCastExpr = dyn_cast_or_null<ImplicitCastExpr>(expr);
                expr = implicitCastExpr->getSubExpr();
            }else if(isa<ParenExpr>(expr)){
                ParenExpr* parenExpr = dyn_cast_or_null<ParenExpr>(expr);
                expr = parenExpr->getSubExpr();
            }else if(isa<CallExpr>(expr)){
                CallExpr* callExpr = dyn_cast_or_null<CallExpr>(expr);
                FunctionDecl* fd = callExpr->getDirectCallee();
                if(fd){
                    string funName = fd->getNameInfo().getAsString();
                    if(cmpFun.find(funName)!=cmpFun.end()){
                        return callExpr;
                    }
                }
                break;
            }else
                break;
        }
        return NULL;
    }
private:
    set<string> cmpFun;
};

static RuleSet rules(new CmpFuncUseInConditionRule()); 
