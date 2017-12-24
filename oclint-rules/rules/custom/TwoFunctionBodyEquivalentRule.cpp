#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"
#include<sstream>

using namespace std;
using namespace clang;
using namespace oclint;

class TwoFunctionBodyEquivalentRule : public AbstractASTVisitorRule<TwoFunctionBodyEquivalentRule>
{
public:
    virtual const string name() const override
    {
        return "two function body equivalent";
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
        maxLineNum = 5;
    }
    virtual void tearDown() override {
    }

    /* Visit FunctionDecl */
    bool VisitFunctionDecl(FunctionDecl *fd)
    {
        if(fd->hasBody()){
            Stmt* body = fd->getBody();
            if(body && isa<CompoundStmt>(body)){
                CompoundStmt* cs = dyn_cast_or_null<CompoundStmt>(body);
                unsigned line1 = sm->getPresumedLineNumber(body->getLocStart());
                unsigned line2 = sm->getPresumedLineNumber(body->getLocEnd()); 

                if(cs->size()>0 && line2-line1<=maxLineNum){
                    string bodyStr = stmt2str(body);
                    string funName = fd->getNameInfo().getAsString();
                    stringstream ss;
                    ss<<funName<<"(line:"<<line1<<"-"<<line2<<")";
                    string curFunInfo = ss.str();
                    map<string, string>::iterator it = funBody.find(bodyStr);
                    if(it!=funBody.end() && it->second != funName){

                        string message = "It is odd that the body of '"+funInfo[it->second]+"' function is fully equivalent to the body of '"+curFunInfo+"' function.";
                        addViolation(fd, this, message);
                        return true;
                    }else{
                        funBody[bodyStr] = funName;
                        funInfo[funName]=curFunInfo;
                    }
                }
            }
        }
        return true;
    }
     
private:

    std::string stmt2str(Stmt *stmt) {
        // (T, U) => "T,,"
        string text = clang::Lexer::getSourceText(CharSourceRange::getTokenRange(stmt->getSourceRange()), *sm, LangOptions(), 0);
        if (text.size()>0&&text.at(text.size()-1) == ',')
            return clang::Lexer::getSourceText(CharSourceRange::getCharRange(stmt->getSourceRange()), *sm, LangOptions(), 0);
        return text;
    }
    

private:
    map<string, string> funBody;
    map<string, string> funInfo;
    SourceManager* sm;
    unsigned maxLineNum;
};

static RuleSet rules(new TwoFunctionBodyEquivalentRule());  
