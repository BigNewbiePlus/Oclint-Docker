#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"

using namespace std;
using namespace clang;
using namespace oclint;

class ThenAndElseBodyEquivalentRule : public AbstractASTVisitorRule<ThenAndElseBodyEquivalentRule>
{
public:
    virtual const string name() const override
    {
        return "then and else body equivalent";
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
    /* Visit IfStmt */
    bool VisitIfStmt(IfStmt *ifStmt)
    {
        Stmt* then = ifStmt->getThen();
        Stmt* els  = ifStmt->getElse();
        if(then && els){
            string str1 = stmt2str(then);
            string str2 = stmt2str(els);
            if(str1.size() && str2.size() && str1==str2){
                addViolation(ifStmt, this, "The 'then' statement is equivalent to the 'else' statement.");
            }
        }
        
        return true;
    }
    
    std::string stmt2str(Stmt *stmt) {
        // (T, U) => "T,,"
        string text = clang::Lexer::getSourceText(CharSourceRange::getTokenRange(stmt->getSourceRange()), *sm, LangOptions(), 0);
        if (text.size()>0&&text.at(text.size()-1) == ',')
            return clang::Lexer::getSourceText(CharSourceRange::getCharRange(stmt->getSourceRange()), *sm, LangOptions(), 0);
        return text;
    } 
private:
    SourceManager* sm;
};

static RuleSet rules(new ThenAndElseBodyEquivalentRule());
