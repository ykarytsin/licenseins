#if !defined (EXCEPTION)
#define EXCEPTION

#include <string>
#include <exception>

using namespace std;

class Exception: public exception {
private:
    string _where;
    string _value;
public:
    Exception(string where, string value) throw() {
        _where = where;
        _value = value;
    }

    Exception () throw() {}
    Exception (const Exception &e) throw() {
        _where = e.where();
        _value = e.value();
    }

    Exception& operator= (const Exception &e) throw() {
        _where = e.where();
        _value = e.value();
        return *this;
    }

    virtual ~Exception() throw() { }

    virtual const char* what() const throw() {
        string result = _where + ": " + _value;
        return result.c_str();
    }

    virtual const char* where() const throw() {
        return _where.c_str();
    }

    virtual const char* value() const throw() {
        return _value.c_str();
    }

    void rethrow() { throw *this; }
};

#endif // EXCEPTION

