#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class AllocaInLoopRule : public AbstractASTVisitorRule<AllocaInLoopRule>
{
public:
    virtual const string name() const override
    {
        return "alloca in loop";
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
        return "Aolloca In Loop Rule"; // TODO: fill in the description of the rule.
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

     /* Visit WhileStmt */
    bool VisitWhileStmt(WhileStmt *node)
    {
        VisitLoopBody(node->getBody());
        return true;
    }
     

    /* Visit DoStmt */
    bool VisitDoStmt(DoStmt *node)
    {
        VisitLoopBody(node->getBody());
        return true;
    }
     

    /* Visit ForStmt */
    bool VisitForStmt(ForStmt *node)
    {
        VisitLoopBody(node->getBody());
        return true;
    }
    
    inline void VisitLoopBody(Stmt* body){
        if(!body)return;

        if(isa<CompoundStmt>(body)){//如果是复合语句
            CompoundStmt* compoundStmt = dyn_cast_or_null<CompoundStmt>(body);
            for(clang::CompoundStmt::body_iterator it = compoundStmt->body_begin(); it!=compoundStmt->body_end();it++){
                VisitDeclOrExpr(*it);
            }
        }else
            VisitDeclOrExpr(body);
    }
    
    void VisitDeclOrExpr(Stmt* stmt){
        Expr* rhs = NULL;
        if(stmt && isa<DeclStmt>(stmt)){
            DeclStmt* ds = dyn_cast_or_null<DeclStmt>(stmt);
            if(ds->isSingleDecl()){
                Decl* decl = ds->getSingleDecl();
                if(decl && isa<VarDecl>(decl)){
                    VarDecl* vd = dyn_cast_or_null<VarDecl>(decl);
                    if(vd->hasInit())rhs = vd->getInit();
                }
            }
        }else if(stmt && isa<BinaryOperator>(stmt)){
            BinaryOperator* bo = dyn_cast_or_null<BinaryOperator>(stmt);
            if(bo->getOpcode()==BO_Assign){
                rhs = bo->getRHS();
            }
        }
        if(rhs && isa<CStyleCastExpr>(rhs)){
            CStyleCastExpr* csce = dyn_cast_or_null<CStyleCastExpr>(rhs);
            rhs = csce->getSubExpr();
            if(rhs&&isa<CallExpr>(rhs)){
                CallExpr* ce = dyn_cast_or_null<CStyleCastExpr>(rhs);
                string funName = ce->getDirectCallee()->getNameInfo().getAsString();
                if(funName == "__builtin_alloca"){
                    string message = "The 'alloca' function is used inside the loop. This can quickly overflow stack."
                    addViolation(stmt, this, message);
                }
            }
        }
    }
    

};

static RuleSet rules(new AllocaInLoopRule());
