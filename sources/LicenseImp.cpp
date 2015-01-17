#include "LicenseImp.h"
#include "Exception.h"


void LicenseImp::SetLicenseFile(const string licenseFile) throw() {
    _licenseFile = licenseFile;
}

string LicenseImp::LicenseFile() const throw() {
    return _licenseFile;
}

void LicenseImp::SetOldLicenseFile(const string oldLicenseFile) throw() {
    _oldLicenseFile = oldLicenseFile;
}

string LicenseImp::OldLicenseFile() const throw(){
    return _oldLicenseFile;
}

void LicenseImp::SetDestinationFiles(const vector<string> &destinationFiles) throw() {
    if(destinationFiles.empty()) return;

    _destinationFiles.clear();
    _destinationFiles.assign(destinationFiles.begin(), destinationFiles.end());
}

void LicenseImp::AddDestinationFile(const string &destinationFile) throw() {
    _destinationFiles.push_back(destinationFile);
}

const vector<string>& LicenseImp::DestinationFiles() const throw() {
    return _destinationFiles;
}

void LicenseImp::writeToStream(ostream &os, istream &is) const throw() {
    is.seekg(0, ios_base::beg);
    while(true) {
        char ch = is.get();
        if(is.eof()) break;
        os.put(ch);
    }

    if(is.bad()) {
        throw Exception("LicenseImp::writeToStream()", "Stream error");
    }
}

void LicenseImp::writeToStream(ostream &os, istream &is, int fromByte, int toByte) const throw() {
    is.seekg(fromByte, ios_base::beg);
    while(is.tellg() < toByte) {
        char ch = is.get();
        if(is.eof()) break;
        os.put(ch);
    }

    if(is.bad()) {
        throw Exception("LicenseImp::writeToStream()", "Stream error");
    }
}

int LicenseImp::findToStream(istream &is, istream &search) const throw() {
    bool isEqual = false;
    int posInDestination = -1;
    string searchString;

    is.seekg(0, ios_base::beg);
    search.seekg(0, ios_base::beg);

    if(!search.eof()) getline(search, searchString);

    while(!is.eof()) {
        string compareString;

        if(search.eof() && searchString.empty())
            break;

        if(posInDestination == -1)
            posInDestination = is.tellg();

        getline(is, compareString);

        if(compareString == searchString) {
            isEqual = true;
            if(!search.eof())
                getline(search, searchString);
            else return posInDestination;
        }
        else if(isEqual){
            isEqual = false;
            posInDestination = 0;
            search.seekg(0, ios_base::beg);
        }
    }

    if(isEqual) return posInDestination;
    else return -1;
}
