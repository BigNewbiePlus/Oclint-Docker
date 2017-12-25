#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"

using namespace std;
using namespace clang;
using namespace oclint;

class IdenticalSubExprsRule : public AbstractASTVisitorRule<IdenticalSubExprsRule>
{
public:
    virtual const string name() const override
    {
        return "identical sub exprs";
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
    
    //Visit Expr
    bool VisitBinaryOperator(BinaryOperator *bo)
    {
        BinaryOperatorKind bok = bo->getOpcode();
        if(bok!=BO_PtrMemD && bok!=BO_PtrMemI && bok!=BO_Comma && bok!=BO_Mul){
            Expr* lhs = bo->getLHS();    
            Expr* rhs = bo->getRHS();
        
            if(lhs && rhs){

                string expr1 = expr2str(lhs);
                string expr2 = expr2str(rhs);
                if(expr1.size() && expr2.size() && expr1==expr2){
                    string ops = (bo->getOpcodeStr()).str();
                    string message = "'"+expr1+"' repeated in expression '"+expr1+ops+expr2+"' !";
                    addViolation(bo, this, message);
                }
            }
        }
        return true;
    }
private:
    std::string expr2str(Expr *expr) {
        // (T, U) => "T,,"
        string text = clang::Lexer::getSourceText(CharSourceRange::getTokenRange(expr->getSourceRange()), *sm, LangOptions(), 0);
        if (text.size()>0 && text.at(text.size()-1) == ',')
            return clang::Lexer::getSourceText(CharSourceRange::getCharRange(expr->getSourceRange()), *sm, LangOptions(), 0);
        return text;
    }
private:
    clang::SourceManager* sm;

};

static RuleSet rules(new IdenticalSubExprsRule());
