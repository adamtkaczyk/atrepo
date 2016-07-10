#include "dicomdirfile.h"

DICOMDIRFile::DICOMDIRFile(std::string path) : path(path)
{
}

DICOMDIRFile::~DICOMDIRFile()
{
    for(DICOMPatient* p : patients)
        delete p;
}
