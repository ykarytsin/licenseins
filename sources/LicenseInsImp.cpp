#include "LicenseInsImp.h"
#include "Exception.h"

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

void LicenseInsImp::SetOldLicenseFile(const string oldLicenseFile) throw() {
    throw Exception("LicenseInsImp::SetOldLicenseFile",
                    "Invalid argument in the INSERT operation [" + oldLicenseFile + "]");
}

void LicenseInsImp::MakeLicense() const throw() {
    ifstream licenseFile;
    ifstream destinationFile;
    ofstream backupFile;

    licenseFile.open(LicenseFile().c_str());
    if(!licenseFile.is_open())
        throw Exception("LicenseImp::MakeLicense()",
                        "License file cann't open [" + LicenseFile() + "]");

    for(vector<string>::const_iterator it = DestinationFiles().begin(); it != DestinationFiles().end(); ++it) {
        string fileName = (*it);

        destinationFile.open(fileName.c_str());
        if(!destinationFile.is_open()) {
            licenseFile.close();
            throw Exception("LicenseImp::MakeLicense()",
                            "Destination file cann't open [" + fileName + "]");
        }

        backupFile.open((fileName + ".tmp").c_str(), ios_base::trunc);
        if(!backupFile.is_open()) {
            licenseFile.close();
            destinationFile.close();
            throw Exception("LicenseImp::MakeLicense()",
                            "Backup file isn't created [" + (fileName + ".tmp") + "]");
        }

        licenseFile.clear();

        writeToStream(backupFile, licenseFile);
        writeToStream(backupFile, destinationFile);

        backupFile.close();
        destinationFile.close();

        std::remove(fileName.c_str());
        std::rename((fileName + ".tmp").c_str(), fileName.c_str());

        cout.flush();
        cout << "[" << fileName << "]"  << " - is done...\n";
    }

    licenseFile.close();
}
