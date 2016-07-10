#ifndef DICOMSTUDY_H
#define DICOMSTUDY_H

#include <string>
#include <vector>

#include <dicomseries.h>

#include <QMetaType>

class DICOMStudy
{
public:
    DICOMStudy();
    virtual ~DICOMStudy();
    virtual void parse() = 0;
    std::vector<DICOMSeries*> getSeries() { return series; }
    std::string getName() { return name; }
protected:
    std::string name;
    std::vector<DICOMSeries*> series;
};

Q_DECLARE_METATYPE(DICOMStudy*)

#endif // DICOMSTUDY_H
