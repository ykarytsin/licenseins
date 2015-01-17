#include <iostream>
#include <string>
#include <stdlib.h>

#include "CmdParameter.h"
#include "CmdParser.h"
#include "LicenseImp.h"
#include "LicenseInsImp.h"
#include "LicenseDelImp.h"
#include "LicenseChangeImp.h"
#include "Exception.h"

using namespace std;

int main(/*int argc, char *argv[]*/)
{
    int argc = 11;
    char* argv[] = { "licenseins",
                     "--file",
                     "../interface.cpp",
                     "--file",
                     "../interface.hpp",
                     "--license",
                     "../copying2012",
                     "--old",
                     "../copying2003",
                     "-m",
                     "change"
    };

    try{
        CmdParameter mode("m", "mode", "Processing modes license files");
        mode.AddLimitArgument("ins");
        mode.AddLimitArgument("del");
        mode.AddLimitArgument("change");

        CmdParameter license("l", "license", "License source");
        CmdParameter oldLicense("o", "old", "Old license source");
        CmdParameter file("f", "file", "Destination file");

        CmdParser parser;
        parser.AddParameter(mode);
        parser.AddParameter(license);
        parser.AddParameter(oldLicense);
        parser.AddParameter(file);

        list<CmdParameter> listParameters = parser.Parse(argc, argv);

        LicenseImp *licenseins = 0;
        string oldLicenseFile;
        string licenseFile;
        vector<string> destinationFiles;

        for(list<CmdParameter>::const_iterator it = listParameters.begin(); it != listParameters.end(); ++it) {
            switch((*it).ShortName()[0]) {
                case 'm':
                    if((*it).Arguments() == "ins") licenseins = new LicenseInsImp();
                    else if((*it).Arguments() == "del") licenseins = new LicenseDelImp();
                    else if((*it).Arguments() == "change") licenseins = new LicenseChangeImp();
                    break;
                case 'l': licenseFile = (*it).Arguments();
                    break;
                case 'o': oldLicenseFile = (*it).Arguments();
                    break;
                case 'f': destinationFiles.push_back((*it).Arguments());
                    break;
            }
        }
        if(licenseins == 0) throw Exception("Main", "Mode isn't setup");
        licenseins->SetLicenseFile(licenseFile);
        if(!oldLicenseFile.empty())
            licenseins->SetOldLicenseFile(oldLicenseFile);
        licenseins->SetDestinationFiles(destinationFiles);
        licenseins->MakeLicense();
    }
    catch(exception &e) {
        cerr << e.what() << endl;
        exit(1);
    }
    catch(...) {
        cerr << "Undefined behavior" << endl;
        exit(2);
    }

    return 0;
}
