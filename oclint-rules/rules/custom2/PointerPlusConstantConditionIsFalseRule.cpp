#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"

using namespace std;
using namespace clang;
using namespace oclint;

class PointerPlusConstantConditionIsFalseRule : public AbstractASTVisitorRule<PointerPlusConstantConditionIsFalseRule>
{
public:
    virtual const string name() const override
    {
        return "pointer plus constant condition is false";
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

    inline bool isZeroLiteral(Expr* expr){
        if(isa<ImplicitCastExpr>(expr)){
            ImplicitCastExpr* ice = dyn_cast_or_null<ImplicitCastExpr>(expr);
            expr = ice->getSubExpr();
        }
        return isa<GNUNullExpr>(expr) || isa<IntegerLiteral>(expr);
        
    }
    /* Visit Cond */
    void VisitCondExpr(Expr* cond){
        Expr* rawCond = cond;
        if(isa<BinaryOperator>(cond)){
            BinaryOperator* bo = dyn_cast_or_null<BinaryOperator>(cond);
            BinaryOperatorKind bok = bo->getOpcode();
            Expr* lhs = bo->getLHS();
            Expr* rhs = bo->getRHS();
            if((bok==BO_EQ || bok==BO_NE) && lhs->getType()->isPointerType() && isZeroLiteral(rhs)){
                cond = lhs;
            }else
                return;
        }
        if(isa<ImplicitCastExpr>(cond)){
            ImplicitCastExpr* ice = dyn_cast_or_null<ImplicitCastExpr>(cond);
            cond = ice->getSubExpr();
        }
        if(isa<BinaryOperator>(cond)){
            BinaryOperator* bo = dyn_cast_or_null<BinaryOperator>(cond);
            BinaryOperatorKind bok = bo->getOpcode();
            Expr* lhs = bo->getLHS();
            Expr* rhs = bo->getRHS();
            if(bok==BO_Add && lhs->getType()->isPointerType() && isa<IntegerLiteral>(rhs)){
                string message = "The condition "+expr2str(rawCond)+" is only false if there is pointer overflow which is undefined behaviour anyway.";
                addViolation(rawCond, this, message);
            }
        }
    }
    /* Visit IfStmt */
    bool VisitIfStmt(IfStmt *node)
    {
        VisitCondExpr(node->getCond());
        return true;
    }

    /* Visit WhileStmt */
    bool VisitWhileStmt(WhileStmt *node)
    {
        VisitCondExpr(node->getCond());
        return true;
    }
     

    /* Visit DoStmt */
    bool VisitDoStmt(DoStmt *node)
    {
        VisitCondExpr(node->getCond());
        return true;
    }
    string expr2str(Expr* expr){
        // (T, U) => "T,,"
        string text = clang::Lexer::getSourceText(
            CharSourceRange::getTokenRange(expr->getSourceRange()), *sm, LangOptions(), 0);
        if (text.at(text.size()-1) == ',')
            return clang::Lexer::getSourceText(CharSourceRange::getCharRange(expr->getSourceRange()), *sm, LangOptions(), 0);
        return text; 
    }


private:
    SourceManager* sm;
     
};

static RuleSet rules(new PointerPlusConstantConditionIsFalseRule());
