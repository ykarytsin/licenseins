#if !defined (LICENSEINSIMP)
#define LICENSEINSIMP

#include "LicenseImp.h"

class LicenseInsImp: public LicenseImp {
public:
    LicenseInsImp() throw() {}
    LicenseInsImp(string licenseFile) throw():
        LicenseImp(licenseFile) {}
    LicenseInsImp(string licenseFile, string oldLicenseFile) throw():
        LicenseImp(licenseFile, oldLicenseFile) {}
    ~LicenseInsImp() throw() {}
    void SetOldLicenseFile(const string oldLicenseFile) throw();
    void MakeLicense() const throw();
};

#endif // LICENSEINSIMP

