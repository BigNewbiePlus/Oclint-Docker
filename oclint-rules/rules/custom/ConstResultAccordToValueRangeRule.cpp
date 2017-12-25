#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"
    
using namespace std;
using namespace clang;
using namespace oclint;

class ConstResultAccordToValueRangeRule : public AbstractASTVisitorRule<ConstResultAccordToValueRangeRule>
{
public:
    virtual const string name() const override
    {
        return "const result accord to value range";
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
    bool VisitBinaryOperator(BinaryOperator *bo)
    {
        BinaryOperatorKind bok = bo->getOpcode();
        if(bok==BO_LT || bok==BO_GT || bok==BO_LE || bok==BO_GE|| bok==BO_EQ || bok==BO_NE){
            Expr* lhs = bo->getLHS();
            Expr* rhs = bo->getRHS();

            if(lhs && rhs){
                int type1=-1, type2=-1;//0:char,1:unsigned int,2:int,3:unsigned char,-1:其他
                int value1=0, value2=0;//type=2,
                
            
                if(isRangeValue(lhs, type1, value1) && isRangeValue(rhs, type2, value2)){
                    if(type1==2 && type2!=2){
                        swap(type1, type2);
                        value2 = value1;
                        if(bok==BO_LT)bok=BO_GT;
                        else if(bok==BO_GT)bok=BO_LT;
                        else if(bok==BO_LE)bok=BO_GE;
                        else if(bok==BO_GE)bok=BO_LE;
                    }
                    if(type1!=2 && type2==2){
                        string str, result;
                        if(getViolation(type1, value2, bok, str, result)){
                            string exprStr = expr2str(bo);    
                            string message = "Expression '"+exprStr+"' is always "+result+". "+str;    
                            addViolation(bo, this, message);
                        }
                    }
                }
            }
        }
        return true;
    }
private:
    bool isRangeValue(Expr* expr,int& type,int& value)//0:char,1:unsigned,2:int,-1:其他
    {
        //ImplicitCastExpr
        if(isa<ImplicitCastExpr>(expr)){
            ImplicitCastExpr* ice = dyn_cast_or_null<ImplicitCastExpr>(expr);
            expr= ice->getSubExpr();
        }
        
        if(isa<IntegerLiteral>(expr)){
            IntegerLiteral* il = dyn_cast_or_null<IntegerLiteral>(expr);
            type=2;
            value = il->getValue().getSExtValue();
            return true;
        }else if(expr->getType()->isCharType()){
            string typeStr = expr->getType().getAsString();
            if(typeStr=="char")type=0;
            else if(typeStr=="unsigned char")type=3;
            else
                return false;
            return true;
        }else if(expr->getType()->isUnsignedIntegerType()){    
            type=1;     
            return true;
        }
        return false;
    }
    
    bool getViolation(int type, int value, BinaryOperatorKind bok, string& str, string& result)
    {
        //0:char,1:unsigned int,2:int,3:unsigned char, -1:其他
        if(type==0){
            switch(bok){
                case BO_LT:
                    if(value<=-128)result="false";
                    else if(value>127)result="true";
                    else return false;
                    break;
                case BO_GT:
                    if(value<-128)result="true";
                    else if(value>=127)result="false";
                    else return false;
                    break;
                case BO_LE:
                    if(value<-128)result="false";
                    else if(value>=127)result="true";
                    else return false;
                    break;
                case BO_GE:
                    if(value<=-128)result="true";
                    else if(value>127)result="false";
                    else return false;
                    break;
                case BO_EQ:
                    if(value<-128||value>127)result="false";
                    else return false;
                    break;
                case BO_NE:
                    if(value<-128||value>127)result="true";
                    else return false;
                    break;
                default:
                    break;
            }
            str = "The value range of signed char type: [-128, 127].";
        }else if(type==1){ 
             switch(bok){
                case BO_LT:
                    if(value<=0)result="false";
                    else return false;
                    break;
                case BO_GT:
                    if(value<0)result="true";
                    else return false;
                    break;
                case BO_LE:
                    if(value<0)result="false";
                    else return false;
                    break;
                case BO_GE:
                    if(value<=0)result="true";
                    else return false;
                    break;
                case BO_EQ:
                    if(value<0)result="false";
                    else return false;
                    break;
                case BO_NE:
                    if(value<0)result="true";
                    else return false;
                    break;
                default:
                    break;
            }
            str = "Unsigned type value is always >= 0.";           
        }else if(type==3){ //[0, 255]
            switch(bok){
                case BO_LT:
                    if(value<=0)result="false";
                    else if(value>255)result="true";
                    else return false;
                    break;
                case BO_GT:
                    if(value<0)result="true";
                    else if(value>=255)result="false";
                    else return false;
                    break;
                case BO_LE:
                    if(value<0)result="false";
                    else if(value>=255)result="true";
                    else return false;
                    break;
                case BO_GE:
                    if(value<=0)result="true";
                    else if(value>255)result="false";
                    else return false;
                    break;
                case BO_EQ:
                    if(value<0||value>255)result="false";
                    else return false;
                    break;
                case BO_NE:
                    if(value<0||value>255)result="true";
                    else return false;
                    break;
                default:
                    break;
            }
            str = "The value range of unsigned char type: [0, 255].";
        } 
        return true;
    }
    
    string expr2str(Expr* expr){
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

static RuleSet rules(new ConstResultAccordToValueRangeRule());  
