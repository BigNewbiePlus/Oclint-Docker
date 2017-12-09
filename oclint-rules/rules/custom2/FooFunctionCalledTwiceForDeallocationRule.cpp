#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include<set>
using namespace std;
using namespace clang;
using namespace oclint;

class FooFunctionCalledTwiceForDeallocationRule : public AbstractASTVisitorRule<FooFunctionCalledTwiceForDeallocationRule>
{
public:
    virtual const string name() const override
    {
        return "foo function called twice for deallocation";
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
    }
    virtual void tearDown() override {}

    /* Visit CompoundStmt */
    bool VisitCompoundStmt(CompoundStmt * cs)
    {
        if(cs->size()<2)return true;
        set<string> baseNames;
        for(CompoundStmt::body_iterator it=cs->body_begin(); it!=cs->body_end(); it++){
            if(isa<CXXMemberCallExpr>(*it)){
                CXXMemberCallExpr* callExpr = dyn_cast_or_null<CXXMemberCallExpr>(*it);
                string funcName = callExpr->getDirectCallee()->getNameInfo().getAsString();
                if(funcName=="clear"){
                    Expr* base = callExpr->getImplicitObjectArgument();
                    if(base && isa<DeclRefExpr>(base)){
                        DeclRefExpr* dre = dyn_cast_or_null<DeclRefExpr>(base);
                        string baseName = dre->getNameInfo().getAsString();
                        if(baseNames.find(baseName)!=baseNames.end()){
                            string message = "The 'clear' function is called twice for deallocation of the same resource.";
                            addViolation(*it, this, message);
                            break;
                        }
                        baseNames.insert(baseName);
                    }
                }
            }
        }
        return true;
    }
};

static RuleSet rules(new FooFunctionCalledTwiceForDeallocationRule()); 
