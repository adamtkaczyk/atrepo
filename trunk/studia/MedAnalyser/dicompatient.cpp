#include "dicompatient.h"

DICOMPatient::DICOMPatient()
{
}

DICOMPatient::~DICOMPatient()
{
    for(DICOMStudy* s : studies)
        delete s;
}

std::string DICOMPatient::getName()
{
    return name;
}

