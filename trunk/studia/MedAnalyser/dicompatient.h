#ifndef DICOMPATIENT_H
#define DICOMPATIENT_H

#include <string>
#include <vector>

#include <QMetaType>

#include <dicomstudy.h>

class DICOMPatient
{
public:
    DICOMPatient();
    virtual ~DICOMPatient();
    std::string getName();
    std::vector<DICOMStudy*> getStudies() { return studies; }
    virtual void parse() = 0;
protected:
    std::string name;
    std::vector<DICOMStudy*> studies;
};

Q_DECLARE_METATYPE(DICOMPatient*)

#endif // DICOMPATIENT_H
