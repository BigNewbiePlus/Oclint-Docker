#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"

using namespace std;
using namespace clang;
using namespace oclint;

class ImplicitlyCastFromIntegerToRealTypeRule : public AbstractASTVisitorRule<ImplicitlyCastFromIntegerToRealTypeRule>
{
public:
    virtual const string name() const override
    {
        return "implicitly cast from integer to real type";
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
        sm=&_carrier->getSourceManager();
    }
    virtual void tearDown() override {}

    /* Visit ImplicitCastExpr */
    bool VisitImplicitCastExpr(ImplicitCastExpr *ice)
    {
        if(ice && ice->getType()->isFloatingType()){
            Expr* expr = ice->getSubExpr();
            if(expr && !expr->getType()->isIntegerType())return true;
            if(expr && isa<ParenExpr>(expr)){
                ParenExpr* pe = dyn_cast_or_null<ParenExpr>(expr);
                expr = pe->getSubExpr();
            }
            if(expr && isa<BinaryOperator>(expr)){
                BinaryOperator* bo = dyn_cast_or_null<BinaryOperator>(expr);
                if(bo->getOpcode()==BO_Div){    
                    string message = "The '"+expr2str(expr)+"' expression was implicitly cast from 'int' type to 'double' type. Consider utilizing an explicit type cast to avoid the loss of a fractional part. An example: double A = (double)(X) / Y;";
                    addViolation(ice, this, message);
                }
            }

        }
        return true;
    }

    
    string expr2str(Expr* expr){
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

static RuleSet rules(new ImplicitlyCastFromIntegerToRealTypeRule());
