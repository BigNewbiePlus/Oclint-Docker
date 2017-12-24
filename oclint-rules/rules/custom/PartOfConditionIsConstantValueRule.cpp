#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"
    
using namespace std;
using namespace clang;
using namespace oclint;

class PartOfConditionIsConstantValueRule : public AbstractASTVisitorRule<PartOfConditionIsConstantValueRule>
{
public:
    virtual const string name() const override
    {
        return "part of condition is constant value";
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
    
    /* Visit BinaryOperator */
    bool VisitBinaryOperator(BinaryOperator* bo)
    {
        BinaryOperatorKind bok = bo->getOpcode();
        //如果是逻辑运算&&或在||
        if(bok==BO_LAnd || bok==BO_LOr){
            Expr* lhs = bo->getLHS();
            Expr* rhs = bo->getRHS();
            if(isIntegerOrEnum(lhs) || isIntegerOrEnum(rhs)){
                string message = "A part of conditional expression is constant in '"+expr2str(bo)+"'."; 
                addViolation(bo, this, message);
            }
        }
        
    }
    
private:

    bool isIntegerOrEnum(Expr* expr){
        if(isa<ImplicitCastExpr>(expr)){    
            ImplicitCastExpr* implicitCastExpr = dyn_cast<ImplicitCastExpr>(expr);
            expr = implicitCastExpr->getSubExpr();
        }
        if(isa<ParenExpr>(expr)){
            ParenExpr* parenExpr = dyn_cast<ParenExpr>(expr);
            expr = parenExpr->getSubExpr();
        }
        if(isa<IntegerLiteral>(expr)){
            return true;
        }else if(isa<DeclRefExpr>(expr)){
            DeclRefExpr* dre = dyn_cast_or_null<DeclRefExpr>(expr);
            return dre->getType()->isEnumeralType();
        }
        return false;

    }
    
    std::string expr2str(Expr *expr) {
        // (T, U) => "T,,"
        string text = clang::Lexer::getSourceText(
            CharSourceRange::getTokenRange(expr->getSourceRange()), *sm, LangOptions(), 0);
        if (text.size()>0&&text.at(text.size()-1) == ',')
            return clang::Lexer::getSourceText(CharSourceRange::getCharRange(expr->getSourceRange()), *sm, LangOptions(), 0);
        return text;
    }
private:
    SourceManager* sm;
};

static RuleSet rules(new PartOfConditionIsConstantValueRule()); 
