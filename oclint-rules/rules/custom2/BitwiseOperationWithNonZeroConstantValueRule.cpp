#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"

using namespace std;
using namespace clang;
using namespace oclint;

class BitwiseOperationWithNonZeroConstantValueRule : public AbstractASTVisitorRule<BitwiseOperationWithNonZeroConstantValueRule>
{
public:
    virtual const string name() const override
    {
        return "bitwise operation with non zero constant value";
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

    bool isNonZeroValue(Expr* expr){
        if(expr && isa<IntegerLiteral>(expr)){
            IntegerLiteral* il=dyn_cast_or_null<IntegerLiteral>(expr);
            return il->getValue().getSExtValue()!=0;
        }
        return false;
    }
    /* Visit IfStmt */
    bool VisitIfStmt(IfStmt* is)
    {
        checkCond(is->getCond());
        return true;
    }

    /* Visit WhileStmt */
    bool VisitWhileStmt(WhileStmt* ws)
    {
        checkCond(ws->getCond());
        return true;
    }

    /* Visit DoStmt */
    bool VisitDoStmt(DoStmt* ds)
    {
        checkCond(ds->getCond());
        return true;
    }

    inline void checkCond(Expr* expr){
       if(isa<ImplicitCastExpr>(expr)){
           ImplicitCastExpr* ice = dyn_cast_or_null<ImplicitCastExpr>(expr);
           expr = ice->getSubExpr();
       } 
       if(isa<ParenExpr>(expr)){
           ParenExpr* pe = dyn_cast_or_null<ParenExpr>(expr);
           expr = pe->getSubExpr();
       }
       if(isa<BinaryOperator>(expr)){
           BinaryOperator* bo = dyn_cast_or_null<BinaryOperator>(expr);
           BinaryOperatorKind bok = bo->getOpcode();
           if(bok==BO_LAnd || bok==BO_LOr){
               checkCond(bo->getLHS());
               checkCond(bo->getRHS());
           }else if(bok==BO_Or){
                if(isNonZeroValue(bo->getLHS())){
                    string message= "Consider inspecting the condition. The '"+expr2str(bo->getLHS())+"' argument of the '|' bitwise operation contains a non-zero value.";
                    addViolation(bo, this, message);
                }else if(isNonZeroValue(bo->getRHS())){
                    string message = "Consider inspecting the condition. The '"+expr2str(bo->getRHS())+"' argument of the '|' bitwise operation contains a non-zero value.";
                    addViolation(bo, this, message);
                }
           }
       }
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

static RuleSet rules(new BitwiseOperationWithNonZeroConstantValueRule());
