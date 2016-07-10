#ifndef IMEBRADICOMPATIENT_H
#define IMEBRADICOMPATIENT_H

#include <string>

#include <dicompatient.h>
#include <imebraobject.h>

class ImebraDICOMPatient : public DICOMPatient, ImebraObject
{
protected:
    puntoexe::ptr<puntoexe::imebra::directoryRecord> pRecord;
public:
    ImebraDICOMPatient(puntoexe::ptr<puntoexe::imebra::directoryRecord> pRecord);
    virtual void parse();
private:
    void scanChildren(puntoexe::ptr<puntoexe::imebra::directoryRecord> pRecord);
};

#endif // IMEBRADICOMPATIENT_H
