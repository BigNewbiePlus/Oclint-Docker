#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"
using namespace std;
using namespace clang;
using namespace oclint;

class OwnerlessExpressionRule : public AbstractASTVisitorRule<OwnerlessExpressionRule>
{
public:
    virtual const string name() const override
    {
        return "ownerless expression";
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

    bool isOwnlessExpression(Stmt* stmt){
        if(!stmt)return false;
        if(isa<MemberExpr>(stmt))return true;
        if(isa<UnaryOperator>(stmt)){
            UnaryOperator* uo = dyn_cast_or_null<UnaryOperator>(stmt);
            UnaryOperatorKind uok = uo->getOpcode();
            if(uok==UO_Deref)return true;
        }
        return false;
    }
    /* Visit CompoundStmt */
    bool VisitCompoundStmt(CompoundStmt* cs)
    {
        for(CompoundStmt::body_iterator it=cs->body_begin(); it!=cs->body_end();it++){
            if(isOwnlessExpression(*it)){
                string message = "Ownerless expression '"+stmt2str(*it)+"'.";
                addViolation(*it, this, message);
            }
        }
        return true;
    }
    
    string stmt2str(Stmt* stmt){
        // (T, U) => "T,,"
        string text = clang::Lexer::getSourceText(
            CharSourceRange::getTokenRange(stmt->getSourceRange()), *sm, LangOptions(), 0);
        if (text.size()>0&&text.at(text.size()-1) == ',')
            return clang::Lexer::getSourceText(CharSourceRange::getCharRange(stmt->getSourceRange()), *sm, LangOptions(), 0);
        return text; 
    }

private:
    SourceManager* sm;
};

static RuleSet rules(new OwnerlessExpressionRule());
