#include "CmdParameter.h"
#include "Exception.h"

CmdParameter::CmdParameter(const CmdParameter &cmdParameter) throw() {
    _shortName = cmdParameter.ShortName();
    _longName = cmdParameter.LongName();
    _description = cmdParameter.Description();
    SetArguments(cmdParameter.Arguments());
    SetLimitArguments(cmdParameter.LimitArguments());
}

CmdParameter::CmdParameter(string shortName, string longName, string description) throw() {
    _shortName = shortName;
    _longName = longName;
    _description = description;
}

CmdParameter::~CmdParameter() throw() {
    _shortName.clear();
    _longName.clear();
    _description.clear();
    _args.clear();
    _limitArgs.clear();
}

void CmdParameter::SetShortName(const string &shortName)  throw() {
    _shortName = shortName;
}

string CmdParameter::ShortName() const throw() {
    return _shortName;
}

void CmdParameter::SetLongName(const string &longName) throw() {
    _longName = longName;
}

string CmdParameter::LongName() const throw() {
    return _longName;
}

void CmdParameter::SetDescription(const string &description) throw() {
    _description = description;
}

string CmdParameter::Description() const throw() {
    return _description;
}

void CmdParameter::SetArguments(const string &args) throw() {
    if(args.empty()) return;

    _args.clear();
    _args.assign(args.begin(), args.end());
}

void CmdParameter::AddArgument(const string &arg)  throw() {
    bool flag = seekToLimitArguments(arg);
    if(_args.empty() && flag) _args = arg;
}

string CmdParameter::Arguments() const throw() {
    return _args;
}

void CmdParameter::SetLimitArguments(const list<string> &args) throw() {
    if(args.empty()) return;

    _limitArgs.clear();
    _limitArgs.assign(args.begin(), args.end());
}

void CmdParameter::AddLimitArgument(const string &arg) throw() {
    _limitArgs.push_back(arg);
}

list<string> CmdParameter::LimitArguments() const throw() {
    return _limitArgs;
}

bool CmdParameter::seekToLimitArguments(const string &arg) throw() {
    if (_limitArgs.empty()) return true;
    bool flag = false;
    for(list<string>::const_iterator it = _limitArgs.begin(); it != _limitArgs.end() && !flag; ++it) {
        if(*it == arg) flag = true;
    }
    if(!flag) throw Exception("CmdParameter::seekToLimitArguments()", "Invalid argument [" + arg + "]");

    return flag;
}
