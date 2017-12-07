#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"

using namespace std;
using namespace clang;
using namespace oclint;

class MisprintsCommaForSemicolonRule : public AbstractASTVisitorRule<MisprintsCommaForSemicolonRule>
{
public:
    virtual const string name() const override
    {
        return "misprints comma for semicolon";
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

    void checkCommaExpr(Stmt* stmt){
        
        BinaryOperator* bo=NULL;
        if(stmt && isa<ReturnStmt>(stmt)){
            ReturnStmt* rs = dyn_cast_or_null<ReturnStmt>(stmt);
            Expr* expr = rs->getRetValue();
            if(expr&&isa<ImplicitCastExpr>(expr)){
                ImplicitCastExpr* ice = dyn_cast_or_null<ImplicitCastExpr>(expr);
                expr = ice->getSubExpr();
            }
            if(expr&&isa<BinaryOperator>(expr)){
                bo = dyn_cast_or_null<BinaryOperator>(expr);
            }
        }else if(stmt&&isa<BinaryOperator>(stmt)){
            bo = dyn_cast_or_null<BinaryOperator>(stmt);
        }
            
        if(bo && bo->getOpcode()==BO_Comma){
            Expr* lhs = bo->getLHS();
            Expr* rhs = bo->getRHS();
            SourceLocation lsl = lhs->getLocStart();
            SourceLocation rsl = rhs->getLocStart();
            unsigned int lrow = sm->getSpellingLineNumber(lsl, 0);
            unsigned int lcol = sm->getSpellingColumnNumber(lsl, 0);
            unsigned int rrow = sm->getSpellingLineNumber(rsl, 0);
            unsigned int rcol = sm->getSpellingColumnNumber(rsl, 0);
            if(rrow>lrow && rcol<lcol){
                string message = "Consider checking for misprints. It's possible that ',' should be replaced by ';'.";
                addViolation(stmt, this, message);
            }
        }
    }
    
    /* Visit IfStmt */
    bool VisitIfStmt(IfStmt *ifStmt)
    {
        Stmt* then = ifStmt->getThen();
        if(then && !isa<CompoundStmt>(then))checkCommaExpr(then);
        
        Stmt* els  = ifStmt->getElse();
        if(els && !isa<CompoundStmt>(els))checkCommaExpr(els);
        return true;
    }
private:
    SourceManager* sm;
};

static RuleSet rules(new MisprintsCommaForSemicolonRule());
