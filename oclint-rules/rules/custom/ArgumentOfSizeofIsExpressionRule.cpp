#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"
    
using namespace std;
using namespace clang;
using namespace oclint;

class ArgumentOfSizeofIsExpressionRule : public AbstractASTVisitorRule<ArgumentOfSizeofIsExpressionRule>
{
public:
    virtual const string name() const override
    {
        return "argument of sizeof is expression";
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
    /* Visit UnaryExprOrTypeTraitExpr */
    bool VisitUnaryExprOrTypeTraitExpr(UnaryExprOrTypeTraitExpr *node)
    {
        if(node->getKind() != UETT_SizeOf)return true;
        Expr * expr = node->getArgumentExpr();
        if(expr && isa<ParenExpr>(expr)){
            ParenExpr* parenExpr = dyn_cast<ParenExpr>(expr);
            expr = parenExpr->getSubExpr();
        }
        bool violation = false;
        if(expr&&isa<BinaryOperator>(expr)){
            violation = true;
        }else if(expr&&isa<UnaryOperator>(expr)){
            UnaryOperator* unaryOperator = dyn_cast<UnaryOperator>(expr);
            UnaryOperatorKind uok= unaryOperator->getOpcode();
            if(uok!=UO_Deref){ 
                violation = true;
            }
        }else if(expr && isa<DeclRefExpr>(expr)){
            DeclRefExpr* declRefExpr = dyn_cast<DeclRefExpr>(expr);
            if(declRefExpr->getType()->isPointerType()){
                violation = true;
            }
        }else if(expr && isa<CXXThisExpr>(expr)){
            violation=true;
        }
        if(violation){
            string exprStr = expr2str(expr);
            string message = "It's odd that the argument of sizeof() operator is the '"+exprStr+"' expression.";
            addViolation(node,this,message);
        }
        
        return true;
    }
private:
    std::string expr2str(Expr* expr) {
        // (T, U) => "T,,"
        string text = clang::Lexer::getSourceText(
            CharSourceRange::getTokenRange(expr->getSourceRange()), *sm, LangOptions(), 0);
        if (text.size()>0 && text.at(text.size()-1) == ',')
            return clang::Lexer::getSourceText(CharSourceRange::getCharRange(expr->getSourceRange()), *sm, LangOptions(), 0);
        return text;
    }
private:
    SourceManager* sm;    
     
};

static RuleSet rules(new ArgumentOfSizeofIsExpressionRule());
