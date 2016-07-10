#ifndef IMEBRADICOMSERIES_H
#define IMEBRADICOMSERIES_H

#include <imebraobject.h>
#include <dicomseries.h>

class ImebraDICOMSeries : public DICOMSeries, ImebraObject
{
public:
    ImebraDICOMSeries(puntoexe::ptr<puntoexe::imebra::directoryRecord> pRecord);
    virtual void parse();
protected:
    puntoexe::ptr<puntoexe::imebra::directoryRecord> pRecord;
private:
    void scanChildren(puntoexe::ptr<puntoexe::imebra::directoryRecord> pRecord);
};

#endif // IMEBRADICOMSERIES_H
