#if !defined (LICENSEDELIMP)
#define LICENSEDELIMP

#include "LicenseImp.h"

class LicenseDelImp: public LicenseImp {
public:
    LicenseDelImp() throw() {}
    LicenseDelImp(string licenseFile) throw():
        LicenseImp(licenseFile) {}
    LicenseDelImp(string licenseFile, string oldLicenseFile) throw():
        LicenseImp(licenseFile, oldLicenseFile) {}
    ~LicenseDelImp() throw() {}

    void SetOldLicenseFile(const string oldLicenseFile) throw();
    void MakeLicense() const throw();
};

#endif // LICENSEDELIMP

