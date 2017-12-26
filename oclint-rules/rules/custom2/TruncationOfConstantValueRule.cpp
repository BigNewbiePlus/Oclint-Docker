#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
using namespace std;
using namespace clang;
using namespace oclint;
#include<sstream>

class TruncationOfConstantValueRule : public AbstractASTVisitorRule<TruncationOfConstantValueRule>
{
public:
    virtual const string name() const override
    {
        return "truncation of constant value";
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

    virtual void setUp() override {}
    virtual void tearDown() override {}

    
    inline bool isUnsignedCharType(Expr* expr){
        if(expr){
                return true;
        }
        return false;
    }

    bool isOutOfUnsignedCharValue(Expr* expr, int& value){
        int flag=1;
        if(!expr)return true;
        if(isa<ImplicitCastExpr>(expr)){
            ImplicitCastExpr* implicitCastExpr = dyn_cast_or_null<ImplicitCastExpr>(expr);
            expr = implicitCastExpr->getSubExpr();
        }
        if(isa<UnaryOperator>(expr)){
            UnaryOperator* unaryOperator = dyn_cast_or_null<UnaryOperator>(expr);
            UnaryOperatorKind uok = unaryOperator->getOpcode();
            
            if(uok==UO_Minus)flag=-1;
            else if(uok!=UO_Plus)return false;
            
            expr = unaryOperator->getSubExpr();
        }
        
        if(isa<IntegerLiteral>(expr)){
            IntegerLiteral*  integerLiteral = dyn_cast_or_null<IntegerLiteral>(expr);
            value = integerLiteral->getValue().getSExtValue()*flag;
            if(value<0|| value>255)return true;
        }
        return false;
    }
    /* Visit BinaryOperator */
    bool VisitBinaryOperator(BinaryOperator *bo)
    {
        //当二元操作符是赋值符时‘=’
        if(bo->getOpcode()==BO_Assign){
            Expr* lhs = bo->getLHS();
            Expr* rhs = bo->getRHS();
            int value; 
            string typeStr = lhs->getType().getCanonicalType().getAsString();
            if(typeStr.find("unsigned char")!=string::npos && isOutOfUnsignedCharValue(rhs, value)){
                stringstream ss;
                ss<<value;
                string message = "Truncation of constant value "+ss.str()+". The value range of unsigned char type: [0, 255].";
                addViolation(bo, this, message);
            }
        }
        return true;
    }

    /* Visit VarDecl */
    bool VisitVarDecl(VarDecl* vd)
    {
        if(vd->hasInit()){
            string typeStr = vd->getType().getCanonicalType().getAsString();
            if(typeStr.find("unsigned char")!=string::npos){
                Expr* init = vd->getInit();
                int value;
                if(isOutOfUnsignedCharValue(init, value)){
                    stringstream ss; ss<<value;
                    string message = "Truncation of constant value "+ss.str()+". The value range of unsigned char type: [0, 255].";
                    addViolation(vd, this, message);
                }
            }
        }
        return true;
    }
    
};

static RuleSet rules(new TruncationOfConstantValueRule());
