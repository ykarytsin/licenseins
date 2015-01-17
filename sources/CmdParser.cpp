#include "CmdParser.h"
#include "CmdParameter.h"
#include "Exception.h"

#include <cstring>
#include <iostream>
#include <algorithm>

void CmdParser::AddParameter(CmdParameter parameter) throw() {
    _limitParameters.push_back(parameter);
}

list<CmdParameter> CmdParser::Parameters() const throw() {
    return _limitParameters;
}

list<CmdParameter> CmdParser::Parse(int argc, char* argv[]) const throw() {
    list<CmdParameter> listParameter;
    for(int index = 1; index < argc; ++index) {
        if(isParameter(argv[index])) {
            list<CmdParameter>::const_iterator it = seekToLimitParameters(argv[index]);
            if(it != _limitParameters.end()) {
                CmdParameter cmdParameter = *it;
                cmdParameter.AddArgument(argv[++index]);
                listParameter.push_back(cmdParameter);
            }
            else throw Exception("CmdParser::Parse()", "Invalid parameter [" + string(argv[index]) + "]");
        }
        else throw Exception("CmdParser::Parse()", "Invalid number of arguments [" + string(argv[index]) + "]");
    }

    return listParameter;
}

list<CmdParameter>::const_iterator CmdParser::seekToLimitParameters(char* arg) const throw() {
    char* parameterName = deleteSpecSymbol(arg);
    bool isLong = isLongParameter(arg);
    bool isShort = isShortParameter(arg);
    list<CmdParameter>::const_iterator it;
    for(it = _limitParameters.begin(); it != _limitParameters.end(); ++it) {
        if((isLong && (*it).LongName() == parameterName) || (isShort && (*it).ShortName() == parameterName)) {
          return it;
        }
    }
    return it;
}

bool CmdParser::isLongParameter(const char* arg) const throw() {
    if(strncmp(arg, "--", 2) == 0)
        return true;
    else return false;
}

bool CmdParser::isShortParameter(const char* arg) const  throw() {
    if(arg[0] == '-' && arg[1] != '-')
        return true;
    else return false;
}

bool CmdParser::isParameter(const char* arg) const throw() {
    if(isLongParameter(arg) || isShortParameter(arg))
        return true;
    else return false;
}

char* CmdParser::deleteSpecSymbol(char *arg) const throw() {
    for(int index = 0; index < 2; ++index)
        if(*arg == '-') ++arg;
    return arg;
}

void CmdParser::Help() const throw() {
    for(list<CmdParameter>::const_iterator it = _limitParameters.begin(); it != _limitParameters.end(); ++it) {
        cout << (*it).ShortName() << "\n";
    }
}
