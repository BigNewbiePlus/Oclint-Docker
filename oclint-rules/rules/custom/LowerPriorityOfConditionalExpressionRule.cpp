#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"

using namespace std;
using namespace clang;
using namespace oclint;

class LowerPriorityOfConditionalExpressionRule : public AbstractASTVisitorRule<LowerPriorityOfConditionalExpressionRule>
{
public:
    virtual const string name() const override
    {
        return "lower priority of conditional expression";
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
    virtual void tearDown() override {
        
    }

   /* Visit ConditionalOperator */
    bool VisitConditionalOperator(ConditionalOperator *co)
    {
        Expr* cond = co->getCond();
        if(cond && isa<ImplicitCastExpr>(cond)){
            ImplicitCastExpr* ice = dyn_cast_or_null<ImplicitCastExpr>(cond);
            cond = ice->getSubExpr();
            if(cond && isa<BinaryOperator>(cond)){
                BinaryOperator* bo = dyn_cast_or_null<BinaryOperator>(cond);
                Expr* rhs = bo->getRHS();
                if(rhs && isa<ImplicitCastExpr>(rhs)){
                    ImplicitCastExpr* ice2 = dyn_cast_or_null<ImplicitCastExpr>(rhs);
                    rhs = ice2->getSubExpr();
                }
                // 是二元运算符，且rhs为bool型，说明存在优先级问题
                if(rhs->getType()->isBooleanType()){
                    string ops = bo->getOpcodeStr().str();
                    string message = "Check priority in conditional expression '"+expr2str(co)+"', the operator '"+ops+"' has more priority than '?:'!";
                    addViolation(co, this, message);
                }
                    
            }
        }
        return true;
    }

private:
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

static RuleSet rules(new LowerPriorityOfConditionalExpressionRule());
