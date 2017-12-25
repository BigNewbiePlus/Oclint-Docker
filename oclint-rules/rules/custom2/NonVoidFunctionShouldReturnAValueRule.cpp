#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class NonVoidFunctionShouldReturnAValueRule : public AbstractASTVisitorRule<NonVoidFunctionShouldReturnAValueRule>
{
public:
    virtual const string name() const override
    {
        return "non void function should return a value";
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

    bool hasReturnInCompound(Stmt* stmt){
        if(isa<CompoundStmt>(stmt)){
            CompoundStmt* cs = dyn_cast_or_null<CompoundStmt>(stmt);
            for(CompoundStmt::body_iterator it=cs->body_begin(); it!=cs->body_end(); it++){
                if(isa<ReturnStmt>(*it))return true;
            }
        }
        return false;
    }
    bool hasReturnInEachBranch(Stmt* stmt)
    {
        if(isa<IfStmt>(stmt)){
            IfStmt* is = dyn_cast_or_null<IfStmt>(stmt);
            while(is){
                Stmt* then = is->getThen();
                if(!then)return false;
                Stmt* els = is->getElse();
                if(!els)return false;
                
                if(isa<CompoundStmt>(then)){
                    if(!hasReturnInCompound(then))return false;
                }else if(!isa<ReturnStmt>(then))return false;
                
                if(isa<CompoundStmt>(els)){
                    return hasReturnInCompound(els);
                }else if(isa<IfStmt>(els)){
                    is = dyn_cast_or_null<IfStmt>(els);
                }else{
                    return isa<ReturnStmt>(els);
                }
            }
            return true;
        }
        return false;
    }
    bool hasReturnStmt(Stmt* stmt){
        if(stmt && isa<CompoundStmt>(stmt)){
            CompoundStmt* compoundStmt = dyn_cast_or_null<CompoundStmt>(stmt);
            for(CompoundStmt::body_iterator it=compoundStmt->body_begin(); it!=compoundStmt->body_end(); it++){
                if(isa<IfStmt>(*it) && hasReturnInEachBranch(*it))return true;
                if(isa<ReturnStmt>(*it))return true;
            }    
        }
        return false;
    }
    /* Visit FunctionDecl */
    bool VisitFunctionDecl(FunctionDecl *fd)
    {
        //是定义处且有返回值
        if(fd->hasBody() &&  fd->isThisDeclarationADefinition() && fd->getReturnType()->isVoidType()==false){
            Stmt* stmt = fd->getBody();
            if(stmt && !hasReturnStmt(stmt)){
                string message = "Non-void function should return a value.";
                addViolation(fd, this, message);
            }
        }
        return true;
    }
};

static RuleSet rules(new NonVoidFunctionShouldReturnAValueRule());
