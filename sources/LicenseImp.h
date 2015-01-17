#if !defined (LICENSEIMP)
#define LICENSEIMP

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class LicenseImp {
    vector<string> _destinationFiles;
    string _licenseFile;
    string _oldLicenseFile;

public:
    LicenseImp() throw() {}
    LicenseImp(string licenseFile) throw():
        _licenseFile(licenseFile) {}
    LicenseImp(string licenseFile, string oldLicenseFile) throw():
        _licenseFile(licenseFile), _oldLicenseFile(oldLicenseFile) {}
    virtual ~LicenseImp() throw() {}

    void SetLicenseFile(const string licenseFile) throw();
    string LicenseFile() const throw();

    virtual void SetOldLicenseFile(const string oldLicenseFile) throw();
    virtual string OldLicenseFile() const throw();

    void SetDestinationFiles(const vector<string> &destinationFiles) throw();
    void AddDestinationFile(const string &destinationFile) throw();
    const vector<string>& DestinationFiles() const throw();

    virtual void MakeLicense() const throw() {}

protected:
    void writeToStream(ostream &os, istream &is) const throw();
    void writeToStream(ostream &os, istream &is, int fromByte, int toByte) const throw();
    int findToStream(istream &is, istream &search) const throw();
};

#endif // LICENSEIMP

