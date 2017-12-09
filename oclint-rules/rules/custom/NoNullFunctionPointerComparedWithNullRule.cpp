#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"

using namespace std;
using namespace clang;
using namespace oclint;

class NoNullFunctionPointerComparedWithNullRule : public AbstractASTVisitorRule<NoNullFunctionPointerComparedWithNullRule>
{
public:
    virtual const string name() const override
    {
        return "no null function pointer compared with null";
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

    /* Visit IfStmt */
    bool VisitIfStmt(IfStmt *node)
    {
        funcPointerComparedWithNull(node->getCond());
        return true;
    }
    
private:
    bool isFuncPointer(Expr* expr){
        while(expr){
            if(isa<ImplicitCastExpr>(expr)){
                ImplicitCastExpr* implicitCastExpr = dyn_cast_or_null<ImplicitCastExpr>(expr);
                expr = implicitCastExpr->getSubExpr();
            }else if(isa<DeclRefExpr>(expr)){
                DeclRefExpr* declRefExpr = dyn_cast_or_null<DeclRefExpr>(expr);
                return declRefExpr->getType()->isFunctionType();//是函数
            }else
                break;
        }
        return false;
        
    }
    
    bool isNull(Expr* expr){
        if(expr){ 
            string str = expr2str(expr);
            if(str=="0" || str=="NULL"){
                return true;
            }
        }
        return false;
    }

    std::string expr2str(Expr *expr) {
        // (T, U) => "T,,"
        string text = clang::Lexer::getSourceText(CharSourceRange::getTokenRange(expr->getSourceRange()), *sm, LangOptions(), 0);
        if (text.size()>0&&text.at(text.size()-1) == ',')
            return clang::Lexer::getSourceText(CharSourceRange::getCharRange(expr->getSourceRange()), *sm, LangOptions(), 0);
        return text;
    }
    void funcPointerComparedWithNull(Expr* expr){
        while(expr){
            
            if(expr && isa<BinaryOperator>(expr)){
                BinaryOperator* bo = dyn_cast_or_null<BinaryOperator>(expr);
                BinaryOperatorKind bok = bo->getOpcode();
                Expr* lhs = bo->getLHS();
                Expr* rhs = bo->getRHS();
                if(bok==BO_EQ || bok==BO_NE){//"==" 或 "!="
                    if((isFuncPointer(lhs)&&isNull(rhs)) || (isNull(lhs)&&isFuncPointer(rhs))){
                        string exprStr = expr2str(expr);
                        string message = "Consider inspecting an odd expression. Non-null function pointer is compared to null: '"+exprStr+"'";
                         addViolation(expr, this, message);
                    }
                }else{
                    funcPointerComparedWithNull(lhs);
                    funcPointerComparedWithNull(rhs);
                }
                break;
            }else if(isa<ParenExpr>(expr)){
                ParenExpr* parenExpr = dyn_cast_or_null<ParenExpr>(expr);
                expr = parenExpr->getSubExpr();
            }else if(isa<UnaryOperator>(expr)){
                UnaryOperator* unaryOperator = dyn_cast_or_null<UnaryOperator>(expr);
                expr = unaryOperator->getSubExpr();
            }else if(isa<ImplicitCastExpr>(expr)){
                ImplicitCastExpr* ice = dyn_cast_or_null<ImplicitCastExpr>(expr);
                expr = ice->getSubExpr();
            }else if(isa<DeclRefExpr>(expr)){
                DeclRefExpr* dre = dyn_cast_or_null<DeclRefExpr>(expr);
                if(dre && dre->getType()->isFunctionType()){//是函数
                    string exprStr = expr2str(expr);
                    string message = "Consider inspecting an odd expression. Non-null function pointer is compared to null: '"+exprStr+"'";
                    addViolation(expr, this, message);
                }
                break;
            }else
                break;
    
        }
    }
private:
    SourceManager* sm;
};

static RuleSet rules(new NoNullFunctionPointerComparedWithNullRule());
