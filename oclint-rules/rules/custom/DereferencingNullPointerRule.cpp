#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
using namespace std;
using namespace clang;
using namespace oclint;

struct PointerState{
    bool isPointer; //标记是否是指针
    string name;//指针名
    bool isNull;//是否为空
    bool deref;//是否引用指针内容
};

class DereferencingNullPointerRule : public AbstractASTVisitorRule<DereferencingNullPointerRule>
{
public:
    virtual const string name() const override
    {
        return "dereferencing null pointer";
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
    }
    virtual void tearDown() override {
        
    }

    /* Visit IfStmt */
    bool VisitIfStmt(IfStmt *node)
    {
        Expr* cond = node->getCond();
        if(cond && isa<BinaryOperator>(cond)){
            BinaryOperator* binaryOperator = dyn_cast_or_null<BinaryOperator>(cond);
            Expr* lhs = binaryOperator->getLHS();
            Expr* rhs = binaryOperator->getRHS();
            BinaryOperatorKind bok = binaryOperator->getOpcode();
           
            if(bok==BO_LAnd || bok==BO_LOr){
                PointerState ps1 = getLPointerState(lhs);
                if(!ps1.isPointer)return true;
                PointerState ps2 = getRPointerState(rhs);
                if(ps1.isPointer && ps2.isPointer && ps2.deref && ps1.name==ps2.name){
                    bool violation=false;
                    if(bok==BO_LAnd && ps1.isNull)violation=true;
                    else if(bok==BO_LOr && !ps1.isNull)violation=true;
                    if(violation){
                        string message = "Dereferencing of the null pointer '"+ps1.name+"' might take place. Check the logical condition.";
                        addViolation(cond,this, message);
                    }           
                }
                
            }
        }
        return true;
    }
    
    
private:
    /*********************************************getLPointerState***********************************************************/
    void getType(const Expr* expr, int& type, string& name){
        type=-1;
        while(expr){
            if(isa<ImplicitCastExpr>(expr)){
                auto implicitCastExpr = dyn_cast_or_null<ImplicitCastExpr>(expr);
                expr = implicitCastExpr->getSubExpr();
            }else if(isa<IntegerLiteral>(expr)){
                auto integerLiteral = dyn_cast_or_null<IntegerLiteral>(expr);
                if(integerLiteral->getValue().getSExtValue()==0)type=0;
                break;
            }else if(isa<DeclRefExpr>(expr)){
                auto declRefExpr = dyn_cast_or_null<DeclRefExpr>(expr);
                auto vd = declRefExpr->getDecl();
                
                if(vd && (vd->getType()->isPointerType() || vd->getType()->isArrayType())){
                    type=1;
                    name = vd->getNameAsString();
                }
                break;
            }else
                break;
        }
    }
    PointerState getLPointerState(Expr* expr){
        PointerState ps;
        ps.isPointer=false;
        
        bool unary = false;
        
        if(expr && isa<BinaryOperator>(expr)){
            BinaryOperator* bo = dyn_cast_or_null<BinaryOperator>(expr);
            BinaryOperatorKind bok = bo->getOpcode();
            if(bok!=BO_EQ && bok!=BO_NE)return ps;
            
            Expr* lhs = bo->getLHS();
            Expr* rhs = bo->getRHS();
            
            int ltype, rtype;
            string lname, rname;
            getType(lhs, ltype, lname);//type:0空，1:指针,-1:其他
            getType(rhs, rtype, rname);//name:若为指针，返回指针名
            
            ps.isPointer=true;
            if(bok==BO_EQ)ps.isNull=true;    
            else ps.isNull=false;
            
            if(ltype==1 && rtype==0) ps.name=lname;
            else if(ltype==0 && rtype==1)ps.name=rname;
            else ps.isPointer=false;
            return ps;
            
        }else if(expr && isa<UnaryOperator>(expr)){
            auto unaryOperator = dyn_cast_or_null<UnaryOperator>(expr);
            expr = unaryOperator->getSubExpr();
            if(unaryOperator->getOpcode()==UO_LNot)unary=true; 
        }
        
        int type;
        string name;
        getType(expr, type, name);//type:0空，1:指针,-1:其他
        if(type==1){//指针
            ps.isPointer=true;
            ps.name=name;
            ps.isNull=false;
            if(unary)ps.isNull=true;
        }
        return ps;
    }
    
    /*********************************************getRPointerState***********************************************************/
    PointerState getRPointerState(Expr* expr){
        PointerState ps;
        ps.isPointer = false;
        bool deref = false;
        
        while(expr){
            if(isa<ImplicitCastExpr>(expr)){
                ImplicitCastExpr* implicitCastExpr = dyn_cast_or_null<ImplicitCastExpr>(expr);
                expr = implicitCastExpr->getSubExpr();
            }else if(isa<UnaryOperator>(expr)){
                UnaryOperator* unaryOperator = dyn_cast_or_null<UnaryOperator>(expr);
                if(unaryOperator->getOpcode()==UO_Deref)deref=true;
                expr = unaryOperator->getSubExpr();
            }else if(isa<ArraySubscriptExpr>(expr)){
                ArraySubscriptExpr* arraySubscriptExpr = dyn_cast_or_null<ArraySubscriptExpr>(expr);
                expr = arraySubscriptExpr->getBase();
                deref = true;
            }else if(isa<CXXMemberCallExpr>(expr)){
                CXXMemberCallExpr* cxxMemberCallExpr = dyn_cast_or_null<CXXMemberCallExpr>(expr);
                expr = cxxMemberCallExpr->getImplicitObjectArgument();
                deref = true;
            }else if(isa<MemberExpr>(expr)){
                MemberExpr* memberExpr = dyn_cast_or_null<MemberExpr>(expr);
                expr = memberExpr->getBase();
                deref = true;
            }else if(isa<DeclRefExpr>(expr)){
                DeclRefExpr* declRefExpr = dyn_cast_or_null<DeclRefExpr>(expr);
                ValueDecl* vd = declRefExpr->getDecl();
                if(vd && (vd->getType()->isPointerType() || vd->getType()->isArrayType())){
                    ps.isPointer = true;
                    ps.name = vd->getNameAsString();
                    ps.deref = deref;
                }
                break;
            }else
                break;
        }
        return ps;
    }
};

static RuleSet rules(new DereferencingNullPointerRule()); 
