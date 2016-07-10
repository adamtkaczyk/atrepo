#ifndef IMEBRADICOMSTUDY_H
#define IMEBRADICOMSTUDY_H

#include <dicomstudy.h>
#include <imebraobject.h>

class ImebraDICOMStudy : public DICOMStudy, ImebraObject
{
public:
    ImebraDICOMStudy(puntoexe::ptr<puntoexe::imebra::directoryRecord> pRecord);
    virtual void parse();
private:
    puntoexe::ptr<puntoexe::imebra::directoryRecord> pRecord;
    void scanChildren(puntoexe::ptr<puntoexe::imebra::directoryRecord> pRecord);
};

#endif // IMEBRADICOMSTUDY_H
