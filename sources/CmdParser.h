#if !defined (CMDPARSER)
#define CMDPARSER

#include "CmdParameter.h"
#include <string>
#include <list>

class CmdParser {
private:
    list<CmdParameter> _limitParameters;
public:
    CmdParser() throw() {}
    virtual ~CmdParser() throw() {
       _limitParameters.clear();
    }

    void AddParameter(const CmdParameter parameter) throw();
    list<CmdParameter> Parameters() const throw();

    list<CmdParameter> Parse(int argc, char *argv[]) const throw();
    void Help() const throw();
private:
    list<CmdParameter>::const_iterator seekToLimitParameters(char* arg) const throw();
    bool isLongParameter(const char* arg) const throw();
    bool isShortParameter(const char* arg) const throw();
    bool isParameter(const char* arg) const throw();
    char* deleteSpecSymbol(char* arg) const throw();
};

#endif // CMDPARSER

