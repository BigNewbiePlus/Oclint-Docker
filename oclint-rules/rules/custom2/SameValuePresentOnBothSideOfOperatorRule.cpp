#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"

using namespace std;
using namespace clang;
using namespace oclint;

class SameValuePresentOnBothSideOfOperatorRule : public AbstractASTVisitorRule<SameValuePresentOnBothSideOfOperatorRule>
{
public:
    virtual const string name() const override
    {
        return "same value present on both side of operator";
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
    
    void getOperandName(Expr* expr, vector<string>& operandNames){
        if(isa<BinaryOperator>(expr)){
            BinaryOperator* binaryOperator = dyn_cast_or_null<BinaryOperator>(expr);
            BinaryOperatorKind bok = binaryOperator->getOpcode();
            if(bok==BO_Add){
                getOperandName(binaryOperator->getLHS(), operandNames);
                getOperandName(binaryOperator->getRHS(), operandNames);
                return;
            }
        }    

        operandNames.push_back(expr2str(expr));
    }

    /* Visit IfStmt */
    bool VisitIfStmt(IfStmt *ifStmt)
    {
        Expr* expr = ifStmt->getCond();
        if(isa<BinaryOperator>(expr)){
            BinaryOperator* binaryOperator = dyn_cast_or_null<BinaryOperator>(expr);
            BinaryOperatorKind bok = binaryOperator->getOpcode();
            if(bok==BO_LT || bok==BO_GT || bok==BO_LE || bok==BO_GE || bok==BO_EQ || bok==BO_NE){
                vector<string> lhss, rhss;
                getOperandName(binaryOperator->getLHS(), lhss);
                getOperandName(binaryOperator->getRHS(), rhss);
                if(lhss.size()+rhss.size()>2){
                    for(auto lhs: lhss)
                        for(auto rhs: rhss){
                            if(lhs==rhs){
                                string message = "The '"+lhs+"' value is present on both sides of the '"+BinaryOperator::getOpcodeStr(bok).str()+"' operator. The expression is incorrect or it can be simplified.";
                                addViolation(ifStmt, this, message);
                                return true;
                            }
                        }
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

static RuleSet rules(new SameValuePresentOnBothSideOfOperatorRule());
