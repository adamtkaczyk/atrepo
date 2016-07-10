#ifndef DICOMDIRFILE_H
#define DICOMDIRFILE_H

#include <vector>
#include <string>

#include <dicompatient.h>

class DICOMDIRFile
{
protected:
    std::vector<DICOMPatient*> patients;
    std::string path;
public:
    DICOMDIRFile(std::string path);
    virtual ~DICOMDIRFile();

    std::vector<DICOMPatient*> getPatients() { return patients; }
    virtual void parseDICOMDIR() = 0;
};

#endif // DICOMDIRFILE_H
