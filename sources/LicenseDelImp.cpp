#include "LicenseDelImp.h"
#include "Exception.h"

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

void LicenseDelImp::SetOldLicenseFile(const string oldLicenseFile) throw() {
    throw Exception("LicenseInsImp::SetOldLicenseFile",
                    "Invalid argument in the DELETE operation [" + oldLicenseFile + "]");
}

void LicenseDelImp::MakeLicense() const throw() {
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

        int licensePosInDestination = findToStream(destinationFile, licenseFile);
        licenseFile.clear();
        destinationFile.clear();

        if(licensePosInDestination == -1) {
            cout << "[" << LicenseFile() <<  "] isn't found in [" << fileName << "]\n";
            backupFile.close();
            destinationFile.close();
            continue;
        }

        licenseFile.seekg(0, ios_base::end);
        int licenseCapacity = licenseFile.tellg();

        destinationFile.seekg(0, ios_base::end);
        int destinationCapacity = destinationFile.tellg();

        writeToStream(backupFile, destinationFile, 0, licensePosInDestination);
        writeToStream(backupFile, destinationFile, licensePosInDestination + licenseCapacity, destinationCapacity);

        backupFile.close();
        destinationFile.close();

        std::remove(fileName.c_str());
        std::rename((fileName + ".tmp").c_str(), fileName.c_str());

        cout << "[" << fileName << "]"  << " - is done...\n";
    }

    licenseFile.close();
}
