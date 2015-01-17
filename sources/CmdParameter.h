#if !defined (CMDPARAMETER)
#define CMDPARAMETER

#include <string>
#include <list>

using namespace std;

class CmdParameter{
private:
    string _shortName;
    string _longName;
    string _description;
    string _args;
    list<string> _limitArgs;
public:
    CmdParameter() throw() {}
    CmdParameter(const CmdParameter &cmdParameter) throw();
    CmdParameter(string shortName, string longName, string description) throw();
    virtual ~CmdParameter() throw();

    void SetShortName(const string &shortName) throw();
    string ShortName() const throw();

    void SetLongName(const string &longName) throw();
    string LongName() const throw();

    void SetDescription(const string &description) throw();
    string Description() const throw();

    void SetArguments(const string &args) throw();
    void AddArgument(const string &arg) throw();
    string Arguments() const throw();

    void SetLimitArguments(const list<string> &args) throw();
    void AddLimitArgument(const string &arg) throw();
    list<string> LimitArguments() const throw();

private:
    bool seekToLimitArguments(const string &arg) throw();
};

#endif // CMDPARAMETER

